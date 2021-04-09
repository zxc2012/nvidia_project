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

//����ת�����ݣ�����ע����ת���г���-750 to 750  ����ת���ֻ��-136 to 136   ������ֵӦ��λ 750��136
void send_steering(int steering_size,char steering_mod,char enable)
{
	int i=0;
	ubyte DataF[8],DataB[8];
	for(i=0;i<=7;i++){
		DataF[i]=0; //clear
		DataB[i]=0;
	}
	//��ת�����ݽ��л���
	//ת���г�����
	if(steering_size>100)
		steering_size=100;
	else if (steering_size<-100)
		steering_size=-100;
	//����һ��ֵ����ת���
	if(steering_size>20)
		P1_OUT_P0 = 0;
	else if(steering_size<-20)
		P7_OUT_P3 = 0;
	else {
		P7_OUT_P3 = 1;
		P1_OUT_P0 = 1;
	}
	//�ж�������ת��ģʽ,Ĭ����ͨģʽ

	switch(steering_mod){
		case 1:  //����ģʽ
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
		case 2:	 //����ģʽ
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
		case 3:  //ͬ��ģʽ
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












