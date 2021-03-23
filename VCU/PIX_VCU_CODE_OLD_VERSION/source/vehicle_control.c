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
int hand_break_mark=0,time_hand_break=0,time_auto_hand_break=0; //手刹标志位和手刹计时
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
	//车辆状态检查
	//debug 
	  ST[1]=0;
	send_cmd_enable = 0;
	vehicle_ec.ess_status=0;
	//急停按钮触发，遥控器信号丢失，禁止发送信号
	if(ST[1]==TRUE||remote_re.t_em_stop==TRUE||remote_re.key==TRUE) 
	{
		vehicle_ec.ess_status=1;
		send_cmd_enable = -1;
		//模式改变为禁止控制模式，同时刹车制动
		return -1;
	//手刹未松，舱门未关，禁止发送速度信息
	}else if(remote_re.hand_break==TRUE){ //此处主要用于保护在无意或不知道自动驾驶模式已启动情况下开启自动驾驶导致事故问题
		vehicle_ec.ess_status=1;							  //所以每次在自动驾驶时急停解除之后需要重新启动自动驾驶模式否则失效
		send_cmd_enable = -1;

		//灯光闪烁提示
		if(remote_re.t_steering_vle>1||remote_re.t_throttle_vle>1||auto_cmd.steering>1||auto_cmd.speed>1)//有动作时就会闪灯提示，驻车未放	 
			{P7_OUT_P3 = 0;P1_OUT_P0 =0;}
		else {P7_OUT_P3 = 1;P1_OUT_P0 =1;}
		//禁止发送速度信息
		//auto_cmd.speed=0;
		//remote_re.t_throttle_vle=0;
		return -1;
	}else {send_cmd_enable = 0;vehicle_ec.ess_status=0;}

	if(remote_re.t_way_trl==0)	//判断控制模式,遥控器模式
	{
		//判断是否为差速模式
		if(remote_re.t_backup3 == 2){  //正常模式
			//转向换算，+-1000 to 0-240
			send_steering((int)(remote_re.t_steering_vle)*0.12,remote_re.t_steering_mod,0x1 );
	
			//转矩值转换
			conversion_throttle = (int)(remote_re.t_throttle_vle*0.42);	
	
			if(remote_re.t_breaking_vle>10)   //如果有值，说明是减速，因为加速和刹车共用一个数值
				send_break(remote_re.t_breaking_vle,0x10);	  //break max size is 0x1000 
				//send_servo_break(remote_re.t_breaking_vle,0x10);  
			else {
				//send_break(BREAKING_FREE,0x10);
				send_servo_break(SERVO_FREE_TORQUE,0x10);
				send_speed((sword)get_vehicle2whell_speed((uword)((float)conversion_throttle*0.1)),remote_re.t_gear,remote_re.low_speed_mod);	 //max well speed :0x0241
			}					
		}else {  //差速模式
			//转向换算，+-1000 to 0-240
			remote_re.t_steering_vle+= 1220; //+-1000 to 0-2000,把原本应该是+1024   但是存在一定机械上的误差为了弥补而为1220
			conversion_steering = (int)((float)remote_re.t_steering_vle * 0.12)-146;
			send_steering(conversion_steering,remote_re.t_steering_mod,0x1 );	

			conversion_throttle = (int)(remote_re.t_throttle_vle*0.42);	
			if(remote_re.t_breaking_vle>10)   //如果有值，说明是减速，因为加速和刹车共用一个数值
				send_break(remote_re.t_breaking_vle,0x10);	  //break max size is 0x1000 
				//send_servo_break(remote_re.t_breaking_vle,0x10);  
			else {
				send_break(BREAKING_FREE,0x10);
				//send_servo_break(SERVO_FREE_TORQUE,0x10);
				//send_speed((sword)get_vehicle2whell_speed((uword)((float)conversion_throttle*0.1)),remote_re.t_gear,remote_re.low_speed_mod);	 //max well speed :0x0241
				differential_control((sword)get_vehicle2whell_speed((uword)((float)conversion_throttle*0.1)),1,remote_re.t_backup3,remote_re.t_gear);	
				}								
		}	
	}else if(remote_re.t_way_trl==1){  //获取自动驾驶数据并发送
		
		//转向值换算，转向机最大允许-146 to 146° 的角度
	    auto_conversion_steering =(int)((float)(auto_cmd.steering+1220) * 0.12)-146;		
		if(auto_cmd.breaking>10)   //如果有值，说明是减速，因为刹车值优先于速度值
			send_break(auto_cmd.breaking,0x10);	  //break max size is 0x1000 
		else {
			send_break(BREAKING_FREE,0x10);
			send_speed((sword)get_vehicle2whell_speed((uword)((float)auto_cmd.speed)),auto_cmd.gear,auto_cmd.low_speed_mod);	 //max well speed :0x0241
		}
		send_steering(auto_conversion_steering,auto_cmd.steering_mod,0x1);
		
	}
 
	return 0;
}




void send_break(uword breaking,ubyte enable)   //有效值ffc0 to 4096
{
	int i=0;
	int excursion = 0;
	ubyte Data[8];
	breaking_size_record=breaking;
	for(i=0;i<=7;i++)
		Data[i]=0; //clear
	if (breaking > BREAKING_MAX && breaking < 0xff00)	 //BREAKING_MAX
		breaking = BREAKING_FREE;//(~(breaking)+1);   remote sizt : real break size
	//开启制动灯
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

//电子手刹控制
//输入: TRUE（1） ：使能  FALSE（0）：失能
//返回值：0 控制成功   -1：电子手刹错误 -2：电子手刹处于工作状态

int autohold (int status)
{
	if(status == TRUE&&P7_OUT_P4 == 1) //表示当前手刹处于空闲状态
	{	
		if(hand_break_mark == FALSE){
			time_hand_break = 0;
			hand_break_mark = TRUE; //夹紧状态			 
		}	
		if(time_hand_break<15){
			P1_OUT_P2 = 0;  //拉手刹电机通电
		}else {P1_OUT_P2 = 1;}		 
		return 0;
		
	}else if(status == FALSE&&P1_OUT_P2 == 1)
	{
		if(hand_break_mark == TRUE){
			time_hand_break = 0;
			hand_break_mark = FALSE; //放松状态
		}
		if(time_hand_break<13){
			P7_OUT_P4 = 0;  //放手刹电机通电
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

//函数功能描述：该函数只要用作长时间制动的一致自动保护措施，当长时间用制动电机进行
//制动保持时如时间过长会造成制动电机过载可能出现故障，所以当使用制动刹车且时间超过10S
//之后系统会自动启动手刹，同时强制释放刹车。该功能仅当制动值产生且车身静止10S之后主动触发。
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








