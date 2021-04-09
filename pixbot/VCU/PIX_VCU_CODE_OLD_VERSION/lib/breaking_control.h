




/********************************************************************
author: dowson
date:20200114
part name: breaking controler 
part function descreption: this file to use code the breaking control,
	We use two different schemes for the brake actuator. One is the same
	 brushed motor as the steering gear. The latest scheme uses a servo 
	 control system. Here, the servo control system is mainly coded. 
********************************************************************/
#ifndef __BREAKING_CONTROL_H
#define __BREAKING_CONTROL_H

#include "MAIN.h"
//about the servo_brakeing macro definition
#define SERVO_BREAK_TX_101 25
#define SERVO_BREAK_RX_700 26

#define SERVO_BREAKING_SPEED 0x09c4 
#define SERVO_FREE_TORQUE 0xfed4
#define SERVO_TORQUE_MAX 0x02bc



//伺服控制数据结构
struct servo_breaking{
	ubyte last_breaking_size;
	ubyte servo_rx_data[8];	
};


int servo_brakeing_init(void);
int send_servo_break(uword breaking,ubyte enable);












#endif












