

/********************************************************************
author: dowson
date:20191205
part name: pid controler 
part function descreption: about the pid controlling code , main 
	function is Calculate the torque value to be sent 
********************************************************************/
#include "vehicle_control.h"
#include "pid_controler.h"
#include "stdlib.h"
#include "speed_control.h"


struct fuzzypid torque_fpid;   //实例化一个用于控制转矩的模糊pid结构
extern struct pid_struct pid;
extern struct pid_struct pidlf;
extern struct pid_struct pidlb;
extern struct pid_struct pidrf;
extern struct pid_struct pidrb;


float debug_pid_c,debug_pid_t,debug_pid_err ;
//P,I,D的模糊推理规则库


//输入线性量化函数


//输入隶属度函数 


//模糊推理函数


//输出隶属度函数 

//PID控制函数
void pid_init(struct pid_struct *pidx,float target_speed, float current_speed,float kp,float ki,float kd,uword can_id,float maga)
{
	pidx->can_id = can_id;
	pidx->current_speed = current_speed;
	pidx->target_speed = target_speed;
	
	pidx->Kp = kp;//0.2*0.4;
	pidx->Ki = ki;//0.95;
	pidx->Kd = kd;//0.1; //size * speed tf T size
		
}
sword pid_calculate(struct pid_struct *pidx)
{
	pid_output = 0；
	if(pid_output <-172)   //-172
		pid_output = -172;
	else if(pid_output>172) //最大油门（215）的80%
		pid_output = 172;
//如果力矩方向与挡位方向相反说明是反转制动，此时不应给过大力拒，造成急性换向损坏电机
	return (sword)pid_output;  //out put the T
}
  


































