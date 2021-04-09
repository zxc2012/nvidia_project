/*************************************/
//****function:steering.c's heard flie 
//****date:2019.09.20
//****author:dowson_tseng
//****email:dowson.tseng@gmail.com
/*************************************/


#ifndef	__STEERING_H
#define __STEERING_H

#include "MAIN.H"

//TODO: Create a structure for saving steering related data
struct steering{
	uword steering_velaus;
	ubyte steering_status;
};

void send_steering(int steering_size,char steering_mod,char enable);


















#endif


