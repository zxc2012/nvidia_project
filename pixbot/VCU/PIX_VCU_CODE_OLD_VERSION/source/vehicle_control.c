/************************************************************
function:Vehicle control rules
date:2019.09.23
last trange: 2019.10.17
author:dowson_tseng
email:dowson.tseng@gmail.com
readme:
*************************************************************/

#include "MAIN.h"
#include "vehicle_control.h"
#include "steering.h"
#include "speed_control.h"
#include "remote.h"
#include "pid_controler.h"
#include "breaking_control.h"
#include "differential_control.h"


extern ubyte ST[8]; 
extern struct remote_receive remote_re;	
struct error_code vehicle_ec;
struct vehicle vehicle_rcv;
struct self_driving auto_cmd;
 
struct pid_struct pid;
struct pid_struct pidlf;
struct pid_struct pidlb;
struct pid_struct pidrf;
struct pid_struct pidrb;

int send_cmd_enable=-1;
int hand_break_mark=0,time_hand_break=0,time_auto_hand_break=0; //��ɲ��־λ����ɲ��ʱ
int breaking_size_record,torque_size_record,autohold_mark=0;


int vehicle_init(void)
{
	ubyte i=0;
	//init error code 
	vehicle_ec.ess_status=0; //emergency stop switch
	vehicle_ec.lfw_status=0;
	vehicle_ec.lbw_status=0;
	vehicle_ec.rfw_status=0;
	vehicle_ec.rbw_status=0;
	vehicle_ec.fs_status=0;
	vehicle_ec.bs_status=0;
	vehicle_ec.break_status=0;
	vehicle_ec.bp_status=0;  //battery power
	vehicle_ec.bms_status=0;
	vehicle_ec.mode_s_error=0;
	vehicle_ec.gear_s_error=0;
	vehicle_ec.remote_error=0;
	for(i=0;i<8;i++)
		vehicle_ec.msg_data[i]=0;

	auto_cmd.steering = 0; 	

	//wait some time to wait anthore mode init ok 
	delay(1000); //1S
	//get msg frome remote ,determine which mode you are in.
	return 0;
}

int vehicle_control(void)
{	//int temp_steering;
	int conversion_steering=0,auto_conversion_steering=0,conversion_throttle=0;
	//system init
	//����״̬���
	//debug 
	  ST[1]=0;
	send_cmd_enable = 0;
	vehicle_ec.ess_status=0;
	//��ͣ��ť������ң�����źŶ�ʧ����ֹ�����ź�
	if(ST[1]==TRUE||remote_re.t_em_stop==TRUE||remote_re.key==TRUE) 
	{
		vehicle_ec.ess_status=1;
		send_cmd_enable = -1;
		//ģʽ�ı�Ϊ��ֹ����ģʽ��ͬʱɲ���ƶ�
		return -1;
	//��ɲδ�ɣ�����δ�أ���ֹ�����ٶ���Ϣ
	}else if(remote_re.hand_break==TRUE){ //�˴���Ҫ���ڱ����������֪���Զ���ʻģʽ����������¿����Զ���ʻ�����¹�����
		vehicle_ec.ess_status=1;							  //����ÿ�����Զ���ʻʱ��ͣ���֮����Ҫ���������Զ���ʻģʽ����ʧЧ
		send_cmd_enable = -1;

		//�ƹ���˸��ʾ
		if(remote_re.t_steering_vle>1||remote_re.t_throttle_vle>1||auto_cmd.steering>1||auto_cmd.speed>1)//�ж���ʱ�ͻ�������ʾ��פ��δ��	 
			{P7_OUT_P3 = 0;P1_OUT_P0 =0;}
		else {P7_OUT_P3 = 1;P1_OUT_P0 =1;}
		//��ֹ�����ٶ���Ϣ
		//auto_cmd.speed=0;
		//remote_re.t_throttle_vle=0;
		return -1;
	}else {send_cmd_enable = 0;vehicle_ec.ess_status=0;}

	if(remote_re.t_way_trl==0)	//�жϿ���ģʽ,ң����ģʽ
	{
		//�ж��Ƿ�Ϊ����ģʽ
		if(remote_re.t_backup3 == 2){  //����ģʽ
			//ת���㣬+-1000 to 0-240
			send_steering((int)(remote_re.t_steering_vle)*0.12,remote_re.t_steering_mod,0x1 );
	
			//ת��ֵת��
			conversion_throttle = (int)(remote_re.t_throttle_vle*0.42);	
	
			if(remote_re.t_breaking_vle>10)   //�����ֵ��˵���Ǽ��٣���Ϊ���ٺ�ɲ������һ����ֵ
				send_break(remote_re.t_breaking_vle,0x10);	  //break max size is 0x1000 
				//send_servo_break(remote_re.t_breaking_vle,0x10);  
			else {
				//send_break(BREAKING_FREE,0x10);
				send_servo_break(SERVO_FREE_TORQUE,0x10);
				send_speed((sword)get_vehicle2whell_speed((uword)((float)conversion_throttle*0.1)),remote_re.t_gear,remote_re.low_speed_mod);	 //max well speed :0x0241
			}					
		}else {  //����ģʽ
			//ת���㣬+-1000 to 0-240
			remote_re.t_steering_vle+= 1220; //+-1000 to 0-2000,��ԭ��Ӧ����+1024   ���Ǵ���һ����е�ϵ����Ϊ���ֲ���Ϊ1220
			conversion_steering = (int)((float)remote_re.t_steering_vle * 0.12)-146;
			send_steering(conversion_steering,remote_re.t_steering_mod,0x1 );	

			conversion_throttle = (int)(remote_re.t_throttle_vle*0.42);	
			if(remote_re.t_breaking_vle>10)   //�����ֵ��˵���Ǽ��٣���Ϊ���ٺ�ɲ������һ����ֵ
				send_break(remote_re.t_breaking_vle,0x10);	  //break max size is 0x1000 
				//send_servo_break(remote_re.t_breaking_vle,0x10);  
			else {
				send_break(BREAKING_FREE,0x10);
				//send_servo_break(SERVO_FREE_TORQUE,0x10);
				//send_speed((sword)get_vehicle2whell_speed((uword)((float)conversion_throttle*0.1)),remote_re.t_gear,remote_re.low_speed_mod);	 //max well speed :0x0241
				differential_control((sword)get_vehicle2whell_speed((uword)((float)conversion_throttle*0.1)),1,remote_re.t_backup3,remote_re.t_gear);	
				}								
		}	
	}else if(remote_re.t_way_trl==1){  //��ȡ�Զ���ʻ���ݲ�����
		
		//ת��ֵ���㣬ת����������-146 to 146�� �ĽǶ�
	    auto_conversion_steering =(int)((float)(auto_cmd.steering+1220) * 0.12)-146;		
		if(auto_cmd.breaking>10)   //�����ֵ��˵���Ǽ��٣���Ϊɲ��ֵ�������ٶ�ֵ
			send_break(auto_cmd.breaking,0x10);	  //break max size is 0x1000 
		else {
			send_break(BREAKING_FREE,0x10);
			send_speed((sword)get_vehicle2whell_speed((uword)((float)auto_cmd.speed)),auto_cmd.gear,auto_cmd.low_speed_mod);	 //max well speed :0x0241
		}
		send_steering(auto_conversion_steering,auto_cmd.steering_mod,0x1);
		
	}
 
	return 0;
}




void send_break(uword breaking,ubyte enable)   //��Чֵffc0 to 4096
{
	int i=0;
	int excursion = 0;
	ubyte Data[8];
	breaking_size_record=breaking;
	for(i=0;i<=7;i++)
		Data[i]=0; //clear
	if (breaking > BREAKING_MAX && breaking < 0xff00)	 //BREAKING_MAX
		breaking = BREAKING_FREE;//(~(breaking)+1);   remote sizt : real break size
	//�����ƶ���
	if(breaking>100&&breaking<0xff00)
		P10_OUT_P11 = 0;
	else P10_OUT_P11 = 1;
	excursion =breaking*4;
	Data[0] = excursion&0xff;
	Data[1] = excursion>>8;
	Data[2] = enable;	 //enable bit
	Data[3] = 0x00;
	Data[4] = 0x00;
	Data[5] = 0x00;
	Data[6] = 0x00;
	Data[7] = 0x00;		
	CAN_vLoadData(BS_430,Data);	 //310-340  8-11   
	CAN_vTransmit(BS_430);	
	delay(50);		
}


//calculate the average whell speed
uword average_whell_speed(struct vehicle v_state)
{

		
	//return (v_state.lfw.rpm+v_state.lbw.rpm+v_state.rfw.rpm+v_state.rbw.rpm)/4;
		return (v_state.lfw.rpm);
}

ubyte get_whell2vehicle_speed(struct vehicle v_state)  //KM/H
{
	//Calculate the average wheel speed
	float vehicle_speed = 0.0,average_wheel_speed=0.0;
	average_wheel_speed =(v_state.lfw.rpm+v_state.lbw.rpm+v_state.rfw.rpm+v_state.rbw.rpm)/4;
	vehicle_speed = (average_wheel_speed*3.14*590)/(60*278);
	return (ubyte)vehicle_speed; 
}

//import vehicle speed transfrom average whell speed

uword get_vehicle2whell_speed(uword vehicle_speed)  
{
	float target_whell_speed=0.0;
	target_whell_speed = ((vehicle_speed*1000.0*60.0)/(3600*0.59*3.14));//(vehicle_speed*60*278)/(3.14*354);
	return target_whell_speed;
}



//vehicle_control

//pid



float data_pct(int input_size,int max_size)
{
	float pct;
	pct = (float)input_size/(float)max_size;
	return pct;
}

//������ɲ����
//����: TRUE��1�� ��ʹ��  FALSE��0����ʧ��
//����ֵ��0 ���Ƴɹ�   -1��������ɲ���� -2��������ɲ���ڹ���״̬

int autohold (int status)
{
	if(status == TRUE&&P7_OUT_P4 == 1) //��ʾ��ǰ��ɲ���ڿ���״̬
	{	
		if(hand_break_mark == FALSE){
			time_hand_break = 0;
			hand_break_mark = TRUE; //�н�״̬			 
		}	
		if(time_hand_break<15){
			P1_OUT_P2 = 0;  //����ɲ���ͨ��
		}else {P1_OUT_P2 = 1;}		 
		return 0;
		
	}else if(status == FALSE&&P1_OUT_P2 == 1)
	{
		if(hand_break_mark == TRUE){
			time_hand_break = 0;
			hand_break_mark = FALSE; //����״̬
		}
		if(time_hand_break<13){
			P7_OUT_P4 = 0;  //����ɲ���ͨ��
		}else {P7_OUT_P4 = 1; SPI_Control();}
		
		return 0;			
	}else if(time_hand_break>15&&P1_OUT_P2==0)
		P1_OUT_P2=1;
	else if(time_hand_break>13&&P7_OUT_P4==0)
		P7_OUT_P4=0;
	if(time_hand_break>15) {
		P7_OUT_P4=1;
		P1_OUT_P2=1;
		}
	return -2;		
}

//���������������ú���ֻҪ������ʱ���ƶ���һ���Զ�������ʩ������ʱ�����ƶ��������
//�ƶ�����ʱ��ʱ�����������ƶ�������ؿ��ܳ��ֹ��ϣ����Ե�ʹ���ƶ�ɲ����ʱ�䳬��10S
//֮��ϵͳ���Զ�������ɲ��ͬʱǿ���ͷ�ɲ�����ù��ܽ����ƶ�ֵ�����ҳ���ֹ10S֮������������
int auto_autohold(void)
{
  
  if(breaking_size_record>0x100&&(vehicle_rcv.lfw.rpm+vehicle_rcv.lbw.rpm+vehicle_rcv.rfw.rpm\
  	+vehicle_rcv.rbw.rpm==0)&&hand_break_mark==FALSE){
					
		if(time_auto_hand_break>100) //10S
		{
			autohold(TRUE);
			send_break(BREAKING_FREE,0x10);
			autohold_mark=1;
		}
	}else if(torque_size_record>2&&hand_break_mark==TRUE){
		autohold(FALSE);
		autohold_mark=0;
	} else time_auto_hand_break=0;

	return 0;	
}








