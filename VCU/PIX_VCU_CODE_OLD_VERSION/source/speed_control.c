/************************************************************
function:vehicle speed close control ,insluce breaking
			 value seting and throttle value seting 
date:2019.09.23
author:dowson_tseng
email:dowson.tseng@gmail.com
*************************************************************/
#include "MAIN.H"
#include "speed_control.h"
#include "vehicle_control.h"
#include "pid_controler.h"


extern struct remote_receive remote_re;
extern struct pid_struct pid;
extern struct pid_struct pidlf;
extern struct pid_struct pidlb;
extern struct pid_struct pidrf;
extern struct pid_struct pidrb;
extern struct vehicle vehicle_rcv;
extern int torque_size_record;


//制作速度数据KM/H
void send_speed(sword target_wheel_speed,ubyte gear,char low_speed_mode)
{
	sword target_temp =0;
//	uword id;
	//d_target_wheel_speed=target_wheel_speed;
	//if(target_wheel_speed>0xde)
	
	if(gear==3)
		target_temp =(~(target_wheel_speed)+1);
	else if(gear==1) target_temp =  target_wheel_speed;
	else target_temp = 0;

	pid_init(&pidlf,target_temp,(sword)vehicle_rcv.lfw.rpm,0.6f,0.01f,0.1f,LFC_310,0.01f);
    pid_init(&pidrf,target_temp,(sword)vehicle_rcv.rfw.rpm,0.6f,0.01f,0.1f,RFC_330,0.01f);
    pid_init(&pidlb,target_temp,(sword)vehicle_rcv.lbw.rpm,0.6f,0.01f,0.1f,LBC_320,0.01f);
    pid_init(&pidrb,target_temp,(sword)vehicle_rcv.rbw.rpm,0.6f,0.01f,0.1f,RBC_340,0.01f);   //0.6 ，0.0 ，0.1   

//		Data3[0] = (uword)target_wheel_speed>>8;
//		Data3[1] = (uword)target_wheel_speed;

		send_break(BREAKING_FREE,0x1);
		//____________________________________________________

/*		Data3[0] = (uword)pidlf.current_speed>>8;
		Data3[1] = (uword)pidlf.current_speed;
		Data3[2] = (uword)pidlf.target_speed>>8;
		Data3[3] = (uword)pidlf.target_speed;	
		CAN_vLoadData(DBO_77,Data3);	 //310-340  8-11   
		CAN_vTransmit(DBO_77);
*/		
		//-----------------------------------------------------

		//send_torque_control(gear,pid_calculate(current_wheel_speed,target_temp,0.8f,0,0),0x1,id);		//0.8
		  send_torque_control(gear,pid_calculate(&pidlf),0x1,pidlf.can_id,low_speed_mode);
		  send_torque_control(gear,pid_calculate(&pidrf),0x1,pidrf.can_id,low_speed_mode);
		  send_torque_control(gear,pid_calculate(&pidlb),0x1,pidlb.can_id,low_speed_mode);
		  send_torque_control(gear,pid_calculate(&pidrb),0x1,pidrb.can_id,low_speed_mode);	
	 

}
 sword d_excursion =0; 
//发送电机扭矩控制
void send_torque_control(ubyte gear,sword torque,ubyte enable,uword id,char low_speed_mode)
{	

	int i=0;
	sword excursion=625,ex=0;	  //偏移
	ubyte DataL[8],DataR[8],Data[8];
	for(i=0;i<=7;i++){
		DataL[i]=0; //clear
		DataR[i]=0;
	}
	torque_size_record =  torque;

			if(torque>0){
				Data[4] = 0x1;	 //enable bit
				excursion=625;	
				excursion+=torque;
				d_excursion = excursion;
				Data[0] = excursion&0xff;
				Data[1] = excursion>>8;
				Data[2] = 0x00;
				Data[3] = 0x00;
				if(low_speed_mode==1)
					Data[5] = 0x01;
				else Data[5] = 0x00;
				Data[6] = 0x00;
				Data[7] = 0x00;


			}else if(torque<0)
			 {
			 	Data[4] = 0x3;
				excursion=625;	
				excursion+=torque;	

				Data[0] = excursion&0xff;
				Data[1] = excursion>>8;
				Data[2] = 0x00;
				Data[3] = 0x00;
				if(low_speed_mode==1)
					Data[5] = 0x01;
				else Data[5] = 0x00;
				Data[6] = 0xa0;
				Data[7] = 0x80;


			}else {
			
			 	Data[4] = 0x0;
				excursion=625;	
				excursion+=torque;	

				Data[0] = excursion&0xff;
				Data[1] = excursion>>8;
				Data[2] = 0x00;
				Data[3] = 0x00;
		
				if(low_speed_mode==1)
					Data[5] = 0x01;
				else Data[5] = 0x00;
				Data[6] = 0x00;
				Data[7] = 0x00;		
			}

	switch(id)
	{
		case LFC_310:
		CAN_vLoadData(LFC_310,Data);	 //310-340  8-11   
		CAN_vTransmit(LFC_310);	
		delay(500);
		break;

	   	case  LBC_320:
		CAN_vLoadData(LBC_320,Data);	 //310-340  8-11    
		CAN_vTransmit(LBC_320);
		delay(500);
		break;

		case RFC_330:    //左边轮和右边轮转向方向相反，需要对数据进行处理
		CAN_vLoadData(RFC_330,Data);	 //310-340  8-11   
		CAN_vTransmit(RFC_330);
		delay(500);
		break;

		case RBC_340:
		CAN_vLoadData(RBC_340,Data);	 //310-340  8-11 RBC_340   
		CAN_vTransmit(RBC_340);
		delay(500);	
		break;

		default:
		CAN_vLoadData(LFC_310,Data);	 //310-340  8-11   
		CAN_vTransmit(LFC_310);	
		delay(500);

		CAN_vLoadData(LBC_320,Data);	 //310-340  8-11    
		CAN_vTransmit(LBC_320);
		delay(500);

		CAN_vLoadData(RFC_330,Data);	 //310-340  8-11   
		CAN_vTransmit(RFC_330);
		delay(500);

		CAN_vLoadData(RBC_340,Data);	 //310-340  8-11 RBC_340   
		CAN_vTransmit(RBC_340);
		delay(500);	
		break;
	}
		
}






