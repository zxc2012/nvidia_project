/********************************************************************
author: dowson
date:20200114
part name: breaking controler 
part function descreption: this file to use code the breaking control,
	We use two different schemes for the brake actuator. One is the same
	 brushed motor as the steering gear. The latest scheme uses a servo 
	 control system. Here, the servo control system is mainly coded.  
********************************************************************/
#include "breaking_control.h"
#include "MAIN.h"
#include "vehicle_control.h"
#include "steering.h"
#include "remote.h"
#include "pid_controler.h"

//60 80 100	   14 14 50
ubyte send_breaking_array[8];

struct servo_breaking s_breaking;


int servo_breaking_init(void)
{
  //使能伺服刹车控制器
	send_breaking_array[0] = 0x00;
	send_breaking_array[1] = 0x1e;
	send_breaking_array[2] = 0x00;	 
	send_breaking_array[3] = 0x10;  //发送制定寄存器
	send_breaking_array[4] = 0x00;
	send_breaking_array[5] = 0x01; //向该值寄存器写入值
	send_breaking_array[6] = 0x00;
	send_breaking_array[7] = 0x00;		
	CAN_vLoadData(SERVO_BREAK_TX_101,send_breaking_array);	   
	CAN_vTransmit(SERVO_BREAK_TX_101);	
	delay(500);
	//获取当前制动器的状态
	if(s_breaking.servo_rx_data[1]==0x1f&&s_breaking.servo_rx_data[5]==0x01) //正确应答
		return 0;
	//设置制动电机速度

   return -1;

}


int send_servo_break(uword breaking,ubyte enable)
{
	int excursion = 0;

	excursion = breaking*1;
	//判断是制动还是释放制动
	if(excursion>SERVO_TORQUE_MAX&&excursion<SERVO_FREE_TORQUE)
		excursion = SERVO_TORQUE_MAX;
	//开启制动灯
	if(excursion>50&&excursion<SERVO_FREE_TORQUE)
		P10_OUT_P11 = 0;
	else P10_OUT_P11 = 1;
	
	//判断刹车值是否重复
	if(s_breaking.last_breaking_size == excursion)	
		return -5;
  //使能伺服刹车控制器
  if(enable == 0x10){
	send_breaking_array[0] = 0x00;	 
	send_breaking_array[1] = 0x24;
	send_breaking_array[2] = 0x00;	 
	send_breaking_array[3] = 0x10;  //发送制定寄存器
	send_breaking_array[4] = 0x00;
	send_breaking_array[5] = 0x00; //向该值寄存器写入值
	send_breaking_array[6] = 0x00;
	send_breaking_array[7] = 0x01;	 //使能	
	CAN_vLoadData(SERVO_BREAK_TX_101,send_breaking_array);	   
	CAN_vTransmit(SERVO_BREAK_TX_101);	
	delay(500);	
	}else {
	send_breaking_array[0] = 0x00;
	send_breaking_array[1] = 0x24;
	send_breaking_array[2] = 0x00;	 
	send_breaking_array[3] = 0x10;  //发送制定寄存器
	send_breaking_array[4] = 0x00;
	send_breaking_array[5] = 0x00; //向该值寄存器写入值
	send_breaking_array[6] = 0x00;
	send_breaking_array[7] = 0x00;	//失能	
	CAN_vLoadData(SERVO_BREAK_TX_101,send_breaking_array);	   
	CAN_vTransmit(SERVO_BREAK_TX_101);	
	delay(500);
	}		
	 //发送电机速度和转矩
	 if(excursion>5&&excursion<SERVO_FREE_TORQUE){				   // 0x09c4
		send_breaking_array[0] = 0x00;
		send_breaking_array[1] = 0x28;
		send_breaking_array[2] = 0x00;	 
		send_breaking_array[3] = 0x00;  //
		send_breaking_array[4] = 0x09;
		send_breaking_array[5] = 0xc4; //
		send_breaking_array[6] = 0x00;
		send_breaking_array[7] = 0x00;		
		CAN_vLoadData(SERVO_BREAK_TX_101,send_breaking_array);	   
		CAN_vTransmit(SERVO_BREAK_TX_101);	
		delay(500);

		send_breaking_array[0] = 0x00;
		send_breaking_array[1] = 0x28;
		send_breaking_array[2] = 0x00;	 
		send_breaking_array[3] = 0x01;  //发送制定寄存器
		send_breaking_array[4] = excursion>>8;
		send_breaking_array[5] = excursion&0xff; //向该值寄存器写入值
		send_breaking_array[6] = 0x00;
		send_breaking_array[7] = 0x00;		
		CAN_vLoadData(SERVO_BREAK_TX_101,send_breaking_array);	   
		CAN_vTransmit(SERVO_BREAK_TX_101);	
		delay(500);

	 }else if(excursion>=SERVO_FREE_TORQUE&&excursion<0xffff) //说明是在释放刹车
	 {
		send_breaking_array[0] = 0x00;
		send_breaking_array[1] = 0x28;
		send_breaking_array[2] = 0x00;	 
		send_breaking_array[3] = 0x00;  //
		send_breaking_array[4] = 0x03;
		send_breaking_array[5] = 0xe8; //
		send_breaking_array[6] = 0x00;
		send_breaking_array[7] = 0x00;		
		CAN_vLoadData(SERVO_BREAK_TX_101,send_breaking_array);	   
		CAN_vTransmit(SERVO_BREAK_TX_101);	
		delay(500);

		send_breaking_array[0] = 0x00;
		send_breaking_array[1] = 0x28;
		send_breaking_array[2] = 0x00;	 
		send_breaking_array[3] = 0x01;  //发送制定寄存器
		send_breaking_array[4] = excursion>>8;
		send_breaking_array[5] = excursion&0xff; //向该值寄存器写入值
		send_breaking_array[6] = 0x00;
		send_breaking_array[7] = 0x00;		
		CAN_vLoadData(SERVO_BREAK_TX_101,send_breaking_array);	   
		CAN_vTransmit(SERVO_BREAK_TX_101);	
		delay(500);	 
	 }

	  s_breaking.last_breaking_size =  excursion;
	  return 0;
} 




























