/********************************************************************
author: dowson
date:20191205
part name: pid controler 
part function descreption: about the pid controlling code , main 
	function is Calculate the torque value to be sent 
********************************************************************/

#ifndef __PID_CONTROLER__
#define __PID_CONTROLER__ 

#include "MAIN.h"

/*论域注释
e的基本论域为：
de的基本论域为：
kp增量论域为：
ki增量论域为：
kd增量论域为：
以上变量的模糊量为：E EC AKP AKI AKD
论域均为：[-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6]
输入量e，de量化因子为：ke =  ,ked=

*/
//固定常数定义
/*#define ERR_MAX 0	//偏差值值上下限	 值采集到的数据值范围  实例中采集的为轮速值范围
#define ERR_MIN 0	
#define ERRC_MAX 0	//偏差变化率上下限	 实际轮速差值的微分量范围
#define ERRC_MIN 0

#define KP_MAX 0  //模糊PID控制输出的P,I,D值范围，输出量化时用于转换
#define KP_MIN 0

#define KI_MAX 0
#define KI_MIN 0

#define KD_MAX 0
#define KD_MIN 0
*/
//语言变量,将输入值分别划分为8个区间
#define NB -3
#define NM -2
#define NS -1
#define ZO 0
#define PS 1
#define PM 2
#define PB 3




//定义模糊控制PID数据结构
struct fuzzypid{
	float target_speed;	  //target wheel speed
	float current_speed;  //current wheel speed 
	float kp; 	  //比例系数
	float ki;	  //积分系数
	float kd;	  //微分系数
	float err; 	  //系统误差
	float pre_err;	//前一个误差
	float pre_pre_err;	//前两个误差
	float derr;   //误差变化率
	float output;    //输出值

	float err_max;  //偏差论域上限	 值采集到的数据值范围  实例中采集的是轮速，所以最大值为
	float err_min;  //偏差论域下限
	float derr_max;	//偏差变化率论域上限
	float derr_min;	//偏差变化率论域下限

	float kp_scale;  //kp 的比例因子 
	float kp_max;
	float fp_min;
	float ki_scale; 
	float ki_max;
	float fi_min;
	float kd_scale; 
	float kd_max;
	float fd_min;
	
};






void pid_init(struct pid_struct *pidx,float target_speed, float current_speed,float kp,float ki,float kd,uword can_id,float maga) ;
sword pid_calculate(struct pid_struct *pidx) ;













#endif





