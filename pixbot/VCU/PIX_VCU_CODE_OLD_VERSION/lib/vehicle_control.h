
#ifndef __VEHICLE_CONTROL_H
#define __VEHICLE_CONTROL_H

#include "steering.h"
#include "MAIN.h"
//TODO:define CAN messages 
#define LFW_316 0  //left front wheel ID-0x316
#define LBW_326 1 
#define RFW_336 2
#define RBW_346 3
#define FSP_416 4 //front steering position
#define BSP_426 5
#define FSC_410 6 //front steering control
#define BSC_420 7
#define LFC_310 8 //
#define LBC_320 9
#define RFC_330 10
#define RBC_340 11

#define RCR_283 12 //remote control receive
#define ECO_190 13 //error code output 
#define DBO_77 14  //debug output
#define BS_430 17
#define BR_436 16
#define AC_183 15  //auto car mod
#define ODD_BREAK 18

#define LFW_319 19  //left front wheel additional ID-0x316
#define LBW_329 20 
#define RFW_339 21
#define RBW_349 22

#define STATUS_196 23//vehicle status about wheel speed upload 
#define STATUS_197 24//vehicle status about steering breaking etc. upload 

#define X_CONVERSION (252.0/15600.0) //15600是自动驾驶发送过来的最大行程也就是左转向到又转向的范围   253是车辆转向机的最大行程

#define GEAR_D 1   //gear mod 
#define GEAR_N 2
#define GEAR_R 3

#define S_DIFF 1   //steering mod 
#define S_NORM 2
#define S_SAME 3

#define M_REMOTE 1 //remote mod 
#define M_AUTO 2 //self driving 


#define TRUE 1
#define FALSE 0

#define BREAKING_MAX 0xe00 //the break max size 
#define BREAKING_FREE 0xfff0 

//TODO:Create a structure to save the wheel data status.
struct wheel{
	uword rpm;
	ubyte status;
};
//TODO:Create a structure to save the breaking data status.
struct breaking{
	uword break_pos;
	ubyte break_status;
};
//TODO:Create a structure to save the vehicle data status.
struct vehicle{
	struct steering front_steering;
	struct steering back_steering;
	struct wheel lfw;
	struct wheel lbw;
	struct wheel rfw;
	struct wheel rbw;
	struct breaking v_breaking;
	ubyte msg_data[8];	  //use to save CAN msg data
	ubyte vehicle_status;
};

struct self_driving{
	uword steering;
	uword speed;
	uword breaking;
	ubyte hand_break;
	ubyte low_speed_mod; //
	ubyte gear;
	ubyte steering_mod;
	ubyte trun_laft;
	ubyte turn_right;
	ubyte em_stop;
	ubyte fear_light;
	ubyte near_light;
	ubyte msg_data[8];
};


//TODO: Create a structure to save error code
struct error_code{
	ubyte ess_status; //emergency stop switch
	ubyte lfw_status;
	ubyte lbw_status;
	ubyte rfw_status;
	ubyte rbw_status;
	ubyte fs_status;
	ubyte bs_status;
	ubyte break_status;
	ubyte bp_status;  //battery power
	ubyte bms_status;
	ubyte mode_s_error;
	ubyte gear_s_error;
	ubyte remote_error;
	ubyte msg_data[8];
};

//pid structural 
struct pid_struct{
	uword can_id;
	float target_speed;
	float current_speed;//whell
	float err; //target - current 
	float pre_err;
	float pre_pre_err;
	float Kp,Ki,Kd; //P,I,D
	float integral; //积分项
	float derivative; //微分项
	float gama;  //微分先行滤波系数
	float pre_current_speed;
};


int vehicle_init(void);
int vehicle_control(void);
int vehicle_init(void);
void send_break(uword breaking,ubyte enable);   //有效值-6000 to 6000
uword average_whell_speed(struct vehicle v_state);
uword get_vehicle2whell_speed(uword vehicle_speed);
float data_pct(int input_size,int max_size);
int autohold(int status);
int auto_autohold(void);












#endif
