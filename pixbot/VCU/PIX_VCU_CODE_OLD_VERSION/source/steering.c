/************************************************************
function:Steering system control, including 
			steering mode specific values, etc.
date:2019.09.20
author:dowson_tseng
email:dowson.tseng@gmail.com
*************************************************************/

#include "MAIN.h"
#include "steering.h"
#include "vehicle_control.h"
#include "remote.h"

extern struct remote_receive remote_re;

//制作转向数据，这里注意电机转向行程是-750 to 750  但是转向机只有-136 to 136   ，发送值应该位 750±136
void send_steering(int steering_size,char steering_mod,char enable)
{
	int i=0;
	ubyte DataF[8],DataB[8];
	for(i=0;i<=7;i++){
		DataF[i]=0; //clear
		DataB[i]=0;
	}
	//对转向数据进行换算
	//转向行程软保护
	if(steering_size>100)
		steering_size=100;
	else if (steering_size<-100)
		steering_size=-100;
	//大于一定值开启转向灯
	if(steering_size>20)
		P1_OUT_P0 = 0;
	else if(steering_size<-20)
		P7_OUT_P3 = 0;
	else {
		P7_OUT_P3 = 1;
		P1_OUT_P0 = 1;
	}
	//判断是哪种转向模式,默认普通模式

	switch(steering_mod){
		case 1:  //异向模式
			DataF[0] = (steering_size+750)&0xff;
			DataF[1] = (steering_size+750)>>8;
			DataF[2] = enable;	 //enable bit
			DataF[3] = 0x00;
			DataF[4] =  0x00;	 
			DataF[5] = 0x00;
			DataF[6] = 0x00;
			DataF[7] =0x00;	

			DataB[0] = ((~steering_size+1)+750)&0xff;
			DataB[1] = ((~steering_size+1)+750)>>8;
			DataB[2] = enable;	//enable bit
			DataB[3] = 0x00;
			DataB[4] =  0x00;	 
			DataB[5] = 0x00;
			DataB[6] = 0x00;
			DataB[7] =0x00;	
		break;		
		case 2:	 //正常模式
			DataF[0] = (steering_size+750)&0xff;
			DataF[1] = (steering_size+750)>>8;
			DataF[2] = enable;	//enable bit
			DataF[3] = 0x00;
			DataF[4] =  0x00;	 
			DataF[5] = 0x00;
			DataF[6] = 0x00;
			DataF[7] =0x00;

			DataB[0] = 750&0xff;
			DataB[1] =  750>>8;
			DataB[2] = enable;   //enable bit
			DataB[3] = 0x00;
			DataB[4] =  0x00;	 
			DataB[5] = 0x00;
			DataB[6] = 0x00;
			DataB[7] =0x00;	
			break;
		case 3:  //同向模式
			DataF[0] = (steering_size+750)&0xff;
			DataF[1] = (steering_size+750)>>8;
			DataF[2] = enable;	 //enable bit
			DataF[3] = 0x00;
			DataF[4] =  0x00;	 
			DataF[5] = 0x00;
			DataF[6] = 0x00;
			DataF[7] =0x00;

			DataB[0] = (steering_size+750)&0xff;
			DataB[1] = (steering_size+750)>>8;
			DataB[2] = enable; //enable bit
			DataB[3] = 0x00;
			DataB[4] =  0x00;	 
			DataB[5] = 0x00;
			DataB[6] = 0x00;
			DataB[7] =0x00;	
			break;
	}
	CAN_vLoadData(FSC_410,DataF);	 //310-340  8-11   
	CAN_vTransmit(FSC_410);	
	delay(500);
	CAN_vLoadData(BSC_420,DataB);	 //310-340  8-11    
	CAN_vTransmit(BSC_420);
	delay(500);
}












