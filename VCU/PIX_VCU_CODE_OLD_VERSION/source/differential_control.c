/********************************************************************
author: dowson
date:20200117
part name: differential_control.c  
part function descreption:Four independent wheels for differential 
	steering and movement control.
********************************************************************/
#include "MAIN.h"
#include "vehicle_control.h"
#include "steering.h"
#include "speed_control.h"
#include "remote.h"
#include "pid_controler.h"
#include "breaking_control.h"
#include "differential_control.h"

extern struct vehicle vehicle_rcv;
extern struct pid_struct pid;
extern struct pid_struct pidlf;
extern struct pid_struct pidlb;
extern struct pid_struct pidrf;
extern struct pid_struct pidrb;

int d_wheel_speed1,d_wheel_speed2;

int differential_control(sword target_wheel_speed,int k,char mode,unsigned char gear)
{
	int wheel_speed1,wheel_speed2;

	switch(mode){
	
		case 1:    //左右差速,即左边轮子和右边轮子转速相反
			if(gear == 1) //此时表示为左轮转向为正，右轮相反 ,左轮需要乘以比例因子 
			{
				wheel_speed1 = target_wheel_speed*k;   //左轮
				wheel_speed2 = (~(target_wheel_speed)+1);  //右轮
				d_wheel_speed1=wheel_speed1;
				d_wheel_speed2=wheel_speed2;
			}
			if(gear == 3) //此时表示为左轮转向为反，右轮相反，右轮需要乘以比例因子 
			{
				wheel_speed1 =  (~(target_wheel_speed)+1);  //左轮
				wheel_speed2 =  target_wheel_speed*k; //右轮
				d_wheel_speed1=wheel_speed1;
				d_wheel_speed2=wheel_speed2;					
			}else if(gear == 2)return 0;
				//计算对应转矩值
			pid_init(&pidlf,wheel_speed1,(sword)vehicle_rcv.lfw.rpm,0.6f,0.0f,0.1f,LFC_310,0.01f);			
			pid_init(&pidrf,wheel_speed2,(sword)vehicle_rcv.rfw.rpm,0.6f,0.0f,0.1f,RFC_330,0.01f);
			pid_init(&pidlb,wheel_speed1,(sword)vehicle_rcv.lbw.rpm,0.6f,0.0f,0.1f,LBC_320,0.01f);
			pid_init(&pidrb,wheel_speed2,(sword)vehicle_rcv.rbw.rpm,0.6f,0.0f,0.1f,RBC_340,0.01f);	

			send_torque_control(gear,pid_calculate(&pidlf),0x1,pidlf.can_id,0);
			send_torque_control(gear,pid_calculate(&pidrf),0x1,pidrf.can_id,0);
			send_torque_control(gear,pid_calculate(&pidlb),0x1,pidlb.can_id,0);
			send_torque_control(gear,pid_calculate(&pidrb),0x1,pidrb.can_id,0);	
		break;
		case 3:    //前后差速，即前轮和后轮转向相反
			if(gear == 1) //此时表示为后轮转向为正，前轮相反，同速 
			{
				wheel_speed1 = target_wheel_speed*k;//后轮
				wheel_speed2 = (~(target_wheel_speed)+1);  //前轮					
			}
			if(gear == 3) //此时表示为后轮转向为反，前轮相反，同速 
			{
				wheel_speed1 =  (~(target_wheel_speed)+1);  //后轮
				wheel_speed2 =  target_wheel_speed*k; //前轮		 		
			}else if(gear == 2)return 0;
			pid_init(&pidlf,wheel_speed2,(sword)vehicle_rcv.lfw.rpm,0.6f,0.0f,0.1f,LFC_310,0.01f);
			pid_init(&pidrf,wheel_speed2,(sword)vehicle_rcv.rfw.rpm,0.6f,0.0f,0.1f,RFC_330,0.01f);
			pid_init(&pidlb,wheel_speed1,(sword)vehicle_rcv.lbw.rpm,0.6f,0.0f,0.1f,LBC_320,0.01f);
			pid_init(&pidrb,wheel_speed1,(sword)vehicle_rcv.rbw.rpm,0.6f,0.0f,0.1f,RBC_340,0.01f);	

			send_torque_control(gear,pid_calculate(&pidlf),0x1,pidlf.can_id,0);
			send_torque_control(gear,pid_calculate(&pidrf),0x1,pidrf.can_id,0);
			send_torque_control(gear,pid_calculate(&pidlb),0x1,pidlb.can_id,0);
			send_torque_control(gear,pid_calculate(&pidrb),0x1,pidrb.can_id,0);	
		break;
	}
	return 0;
}






