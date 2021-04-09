

/***********************************************************************
@name: vehicle_speed_control.h
@version: v0.1
@function: thie flie is used code vehicle torque control to vehicle speed control
@coder: dowson Tseng
@time: 2019 04 26 pm
***********************************************************************/

#ifndef VEHICLE_SPEED_CONTROL__H
#define VEHICLE_SPEED_CONTROL__H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <asm/types.h>
#include <unistd.h>

#ifndef NO_RT
#include <sys/mman.h>

#ifdef RTAI
#include <rtai_lxrt.h>
#endif

// PCAN-Basic device used to read on
// (RT version doesn't handle USB devices)
#define PCAN_DEVICE		PCAN_USBBUS1 //PCAN_PCIBUS1 //changed by wmm 
#else

// PCAN-Basic device used to read on
#define PCAN_DEVICE		PCAN_USBBUS1
#endif

#include "PCANBasic.h"
#include <stdint.h>
#include <ros/ros.h>

/**************************************************
CAN ID , CAN GLOBAL Variables
***************************************************/
#define CAN_RX_ID 0x183
#define CAN_SPEED_ID 0x150
#define CAN_AGLE_ID 0x151
#define CAN_BREAK_ID 0x151
#define UPDATE_TIME 10   //in ms
#define LAWELL_ID 0x217  //carriage wheel id rpm/min
#define RAWELL_ID 0x227
#define LBWELL_ID 0x237
#define RBWELL_ID 0x247
#define WHEEL_STEER_ID 0x160
#define TIME_OUT 1000

static unsigned int pcan_device = PCAN_DEVICE;


struct WheelRotateSpeed{
	uint16_t la;
	uint16_t ra;
	uint16_t lb;
	uint16_t rb; 
	
};

//pid structural 
struct pid_struct{
	float target_speed;
	float current_speed;//whell
	float err; //target - current 
	float pre_err;
	float pre_pre_err;
	float Kp,Ki,Kd; //P,I,D
};



unsigned int init_can();

TPCANStatus send_speed(uint8_t shift,uint8_t old_speed);
TPCANStatus send_steering(uint16_t old_agle,uint16_t break_size);

uint16_t average_whell_speed(struct WheelRotateSpeed Wrs);
uint8_t get_whell2vehicle_speed(struct WheelRotateSpeed Wrs);  //KM/H
uint16_t get_vehicle2whell_speed(uint8_t vehicle_speed);  
uint8_t vehicle_control(uint16_t vel_steering,uint16_t current_speed,uint16_t target_speed,uint8_t shift);
TPCANStatus send_torque_control(uint8_t shift,uint16_t torque);
TPCANStatus sent_break_control(uint16_t break_size);

//add new for dowson time:20191218
TPCANStatus send_out_183(int t_speed,int t_steering);


void pid_init(float kp,float ki,float kd);
float pid_calculate(float current_speed,float target_speed,float kp,float ki,float kd);



#endif


