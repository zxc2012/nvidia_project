/************************************************************
function:vehicle speed close control ,insluce breaking
			 value seting and throttle value seting 
date:2019.09.23
author:dowson_tseng
email:dowson.tseng@gmail.com
*************************************************************/

#ifndef __SPEED_TRL_H
#define __SPEED_TRL_H



void send_speed(sword target_wheel_speed,ubyte gear,char low_speed_mode);
void send_torque_control(ubyte gear,sword torque,ubyte enable,uword id,char low_speed_mode);


















#endif


