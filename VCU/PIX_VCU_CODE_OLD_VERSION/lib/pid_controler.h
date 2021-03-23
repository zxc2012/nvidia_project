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

/*����ע��
e�Ļ�������Ϊ��
de�Ļ�������Ϊ��
kp��������Ϊ��
ki��������Ϊ��
kd��������Ϊ��
���ϱ�����ģ����Ϊ��E EC AKP AKI AKD
�����Ϊ��[-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6]
������e��de��������Ϊ��ke =  ,ked=

*/
//�̶���������
/*#define ERR_MAX 0	//ƫ��ֵֵ������	 ֵ�ɼ���������ֵ��Χ  ʵ���вɼ���Ϊ����ֵ��Χ
#define ERR_MIN 0	
#define ERRC_MAX 0	//ƫ��仯��������	 ʵ�����ٲ�ֵ��΢������Χ
#define ERRC_MIN 0

#define KP_MAX 0  //ģ��PID���������P,I,Dֵ��Χ���������ʱ����ת��
#define KP_MIN 0

#define KI_MAX 0
#define KI_MIN 0

#define KD_MAX 0
#define KD_MIN 0
*/
//���Ա���,������ֵ�ֱ𻮷�Ϊ8������
#define NB -3
#define NM -2
#define NS -1
#define ZO 0
#define PS 1
#define PM 2
#define PB 3




//����ģ������PID���ݽṹ
struct fuzzypid{
	float target_speed;	  //target wheel speed
	float current_speed;  //current wheel speed 
	float kp; 	  //����ϵ��
	float ki;	  //����ϵ��
	float kd;	  //΢��ϵ��
	float err; 	  //ϵͳ���
	float pre_err;	//ǰһ�����
	float pre_pre_err;	//ǰ�������
	float derr;   //���仯��
	float output;    //���ֵ

	float err_max;  //ƫ����������	 ֵ�ɼ���������ֵ��Χ  ʵ���вɼ��������٣��������ֵΪ
	float err_min;  //ƫ����������
	float derr_max;	//ƫ��仯����������
	float derr_min;	//ƫ��仯����������

	float kp_scale;  //kp �ı������� 
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





