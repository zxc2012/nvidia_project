
/***********************************************************************
@name: vehicle_speed_control.c
@version: v0.1
@function: thie flie is used code vehicle torque control to vehicle speed control
@coder: dowson Tseng
@time: 2019 04 26 pm
***********************************************************************/

#include "vehicle_speed_control.h" 


// extern uint16_t vel_steering;
// extern uint8_t vel_speed,vel_shift;
// extern struct WheelRotateSpeed Current_Wrs;
static struct pid_struct pid;  // TODO  check static vs extern

unsigned int init_can(){

	TPCANStatus Status;

#ifndef NO_RT
	mlockall(MCL_CURRENT | MCL_FUTURE);

#ifdef RTAI
	// Initialize LXRT
	RT_TASK *mainr = rt_task_init_schmod(nam2num("MAINW"), 0, 0, 0,
					     SCHED_FIFO, 0xF);
	if (!mainr) {
		printf("pcanwrite(%xh): unable to setup main RT task\n",
			PCAN_DEVICE);
		return -1;
	}
	rt_make_hard_real_time();
#endif
#endif

	Status = CAN_Initialize(pcan_device, PCAN_BAUD_500K, 0, 0, 0);
	ROS_INFO("CAN_Initialize(%xh): Status=0x%x\n", pcan_device, (int )Status);
	if (Status){
		ROS_INFO("can init error!!!!");
		return pcan_device;
	}
	ROS_INFO("finish init can!!!!!");
	return pcan_device;
}

//remake and send speed
TPCANStatus send_speed(uint8_t shift,uint8_t old_speed)
{
	TPCANMsg Message;
	TPCANStatus Status;
	return Status;
	// CanTxMsg TxSpeed;
	// uint16_t new_speed =0;
	// new_speed = 4*old_speed;
	
	// TxSpeed.StdId = CAN_SPEED_ID;//SET the ID of the CAN1 Message
	// TxSpeed.RTR=CAN_RTR_DATA;		
	// TxSpeed.IDE=CAN_ID_STD;//Standard or Extended		
	// TxSpeed.DLC = 8;//Length of Data
	// int i=0;
	// for(i=0;i<=7;i++)
	// 	TxSpeed.Data[i]=0; //clear
		
	// switch(shift)
	// {
	// 	case 1: //D
	// 		TxSpeed.Data[0] = (~(new_speed)+1)>>8;
	// 		TxSpeed.Data[1] = (~(new_speed)+1)&0xff;
	// 		TxSpeed.Data[2] = (~(new_speed)+1)>>8;
	// 		TxSpeed.Data[3] = (~(new_speed)+1)&0xff;
	// 		TxSpeed.Data[4] = (~(new_speed)+1)>>8;
	// 		TxSpeed.Data[5] = (~(new_speed)+1)&0xff;
	// 		TxSpeed.Data[6] = (~(new_speed)+1)>>8;
	// 		TxSpeed.Data[7] = (~(new_speed)+1)&0xff;		
	// 		break;
	// 	case 2:  //N
	// 		TxSpeed.Data[0] = 0;
	// 		TxSpeed.Data[1] = 0;
	// 		TxSpeed.Data[2] = 0;
	// 		TxSpeed.Data[3] = 0;
	// 		break;
	// 	case 3: //R
	// 		TxSpeed.Data[0] = new_speed>>8;
	// 		TxSpeed.Data[1] = new_speed&0xff;
	// 		TxSpeed.Data[2] = new_speed>>8;
	// 		TxSpeed.Data[3] = new_speed&0xff;	
	// 		TxSpeed.Data[4] = new_speed>>8;
	// 		TxSpeed.Data[5] = new_speed&0xff;
	// 		TxSpeed.Data[6] = new_speed>>8;
	// 		TxSpeed.Data[7] = new_speed&0xff;		
	// 		break;
	// }
	// CAN_Transmit(CAN1, &TxSpeed);
	// return TxSpeed;

}

//remake and send agle 
TPCANStatus send_steering(uint16_t new_agle,uint16_t break_size)
{
	//break_size=0xffce; // TODO for can test. remember to delete!!!!

	TPCANMsg Message;
	TPCANStatus Status;
	 
	memset(Message.DATA, '\0', sizeof(Message.DATA));
	ROS_INFO("start send message steer!!!!!");
	// TODO set message according to vehicle_msg
	// reset DATA to 0 first
	// Message.DATA[0] = ....
	
	//int16_t new_agle=0;
	Message.ID = CAN_AGLE_ID;//SET the ID of the CAN1 Message		
	Message.LEN = 8;//Length of Data
	Message.MSGTYPE = PCAN_MESSAGE_STANDARD; // TODO check it
	// int i=0;
	// for(i=0;i<=7;i++)
	// 	TxSteering.Data[i]=0; //clear
	//new_agle = (int16_t)((float)old_agle * (120.0/21));
	// new_agle = (int16_t)(((float)old_agle*0.0154)-0x78);//((float)old_agle*0.0037)-0x78; //sub bias 
//	if(0x100<break_size&&break_size<0x4b0)//0x4b0 if max break size
//		break_size = 0x100;
	Message.DATA[0] = ((~new_agle)+1)>>8;
	Message.DATA[1] = (~new_agle)+1;
	Message.DATA[2] = new_agle>>8;
	Message.DATA[3] = 	new_agle;			
	Message.DATA[4] = break_size >> 8;
	Message.DATA[5] = break_size&0xff;

	ROS_INFO(" steer - R ID:%4x LEN:%1x DATA:%02x %02x %02x %02x %02x %02x %02x %02x\n",
		(int)Message.ID, (int)Message.LEN,
		(int)Message.DATA[0], (int)Message.DATA[1],
		(int)Message.DATA[2], (int)Message.DATA[3],
		(int)Message.DATA[4], (int)Message.DATA[5],
		(int)Message.DATA[6], (int)Message.DATA[7]);

	Status = CAN_Write(pcan_device, &Message);
	return Status;
	//return 0x00000U;

}


//calculate the average whell speed
uint16_t average_whell_speed(struct WheelRotateSpeed Wrs)
{
	return (Wrs.la+Wrs.lb+Wrs.ra+Wrs.rb)/4;
}


//get vehicle speed by 4 whells speed
//formula: ((r*pai*D)/60)/(1000*1000/3600) (km/h)
//r:whell speed (rpm) D = 450
uint8_t get_whell2vehicle_speed(struct WheelRotateSpeed Wrs)  //KM/H
{
	//Calculate the average wheel speed
	float vehicle_speed = 0.0,average_wheel_speed=0.0;
	average_wheel_speed =(Wrs.la+Wrs.lb+Wrs.ra+Wrs.rb)/4;
	vehicle_speed = (average_wheel_speed*3.14*450)/(60*278);
	return (uint8_t)vehicle_speed; 
}
//import vehicle speed transfrom average whell speed
uint16_t get_vehicle2whell_speed(uint8_t vehicle_speed)  
{
	float target_whell_speed=0.0;
	target_whell_speed = (int)((vehicle_speed*1000*60)/(3600*0.45*3.14));//(vehicle_speed*60*278)/(3.14*354);
	return target_whell_speed;
}


//vehicle speed closed-loop control , torgue is adjusted by speed
//formula: 
//Assume constant torque T = 0x96
uint8_t vehicle_control(uint16_t vel_steering,uint16_t current__wheel_speed,uint16_t target_wheel_speed,uint8_t shift)
{
	
	TPCANStatus steer_status;
	TPCANStatus torque_status;
	uint16_t break_size = 0x0190,break_free=0xffce;
		//get curuent speed
	ROS_INFO("export:vel_steering:%d,current__wheel_speed:%d, target_wheel_speed:%d, shift:%d",vel_steering,current__wheel_speed, target_wheel_speed,shift);
	if(target_wheel_speed-current__wheel_speed > 1) //need speed up
	{
		steer_status = send_steering(vel_steering,break_free);	
		//sent_break_control(break_free);
		torque_status = send_torque_control(shift,pid_calculate(current__wheel_speed,target_wheel_speed,2,0.95,0.1));		//0.8
	}
	else if(target_wheel_speed-current__wheel_speed < -5)
	{
		steer_status = send_steering(vel_steering,pid_calculate(target_wheel_speed,current__wheel_speed,1.2,0.95,0.1));	
		torque_status = send_torque_control(shift,0);		
	}
	else if(target_wheel_speed == 0&& current__wheel_speed==0 ){
		steer_status = send_steering(vel_steering,0x140);	
		torque_status = send_torque_control(shift,0);		
	}else{
		return 0;
	}

	if (steer_status == PCAN_ERROR_OK){
		ROS_INFO("CAN_Write(%xh):steer OK 0x%x\n", pcan_device,(int)steer_status);
		//usleep(1000000); // TODO modify
	}else{
		ROS_INFO("CAN_Write(%xh): steer Error 0x%x\n", pcan_device,(int)steer_status);
		if (steer_status != PCAN_ERROR_QXMTFULL) {
			ROS_INFO("CAN_Write(%xh): Error (not full) 0x%x\n", pcan_device,
				(int)steer_status);
			return 1;
		}
		// Tx queue is full: must wait a bit instad of forever 
		// looping. Handle ^C here too.
		ROS_INFO("Queue Full, Sleep for a while!!!");
		if (usleep(100)){
			ROS_INFO("end this!!!");
			return 2;
		}
	}

	if (torque_status == PCAN_ERROR_OK){
		ROS_INFO("CAN_Write(%xh):torque_status OK 0x%x\n", pcan_device,(int)torque_status);
		//usleep(1000000); // TODO modify
	}else{
		ROS_INFO("CAN_Write(%xh): torque_status Error 0x%x\n", pcan_device,(int)torque_status);
		if (torque_status != PCAN_ERROR_QXMTFULL) {
			ROS_INFO("CAN_Write(%xh): Error (not full) 0x%x\n", pcan_device,
				(int)torque_status);
			return 1;
		}
		// Tx queue is full: must wait a bit instad of forever 
		// looping. Handle ^C here too.
		ROS_INFO("Queue Full, Sleep for a while!!!");
		if (usleep(100)){
			ROS_INFO("end this!!!");
			return 2;
		}
	}
	return 0;
}

void pid_init(float kp,float ki,float kd)
{
	pid.current_speed = 0;
	pid.target_speed = 0;
	pid.pre_err = 0;
	pid.pre_pre_err = 0;
	pid.err = 0;
	pid.Kp = kp;//0.2*0.4;
	pid.Ki = ki;//0.95;
	pid.Kd = kd;//0.1; //size * speed tf T size
}

float pid_calculate(float current_speed,float target_speed,float kp,float ki,float kd)
{
	float pid_output=0;
	pid_init(kp,ki,kd);
	pid.current_speed = current_speed;
	pid.target_speed = target_speed;
	pid.err = target_speed - current_speed;
	pid_output = pid.Kp*(pid.err-pid.pre_err) + \
	pid.Ki*pid.err+pid.Kd*(pid.err-2*pid.pre_err+pid.pre_pre_err);
	
	pid.pre_err = pid.err;
	pid.pre_pre_err = pid.pre_err;
	return pid_output;  //out put the T
}


TPCANStatus send_torque_control(uint8_t shift,uint16_t torque)
{
	TPCANMsg Message;
	TPCANStatus Status;

	ROS_INFO("start send message torque_control!!!!!");
	Message.ID = CAN_SPEED_ID; // TODO change this 
	Message.LEN = 8;
	Message.MSGTYPE = PCAN_MESSAGE_STANDARD; // TODO check it 
	memset(Message.DATA, '\0', sizeof(Message.DATA));
	switch(shift)
	{
		case 1: //D
			Message.DATA[0] = (~(torque)+1)>>8;
			Message.DATA[1] = (~(torque)+1)&0xff;
			Message.DATA[2] = (~(torque)+1)>>8;
			Message.DATA[3] = (~(torque)+1)&0xff;
			Message.DATA[4] = (~(torque)+1)>>8;
			Message.DATA[5] = (~(torque)+1)&0xff;
			Message.DATA[6] = (~(torque)+1)>>8;
			Message.DATA[7] = (~(torque)+1)&0xff;		
			break;
		case 2:  //N
			Message.DATA[0] = 0;
			Message.DATA[1] = 0;
			Message.DATA[2] = 0;
			Message.DATA[3] = 0;
			break;
		case 3: //R
			Message.DATA[0] = torque>>8;
			Message.DATA[1] = torque&0xff;
			Message.DATA[2] = torque>>8;
			Message.DATA[3] = torque&0xff;	
			Message.DATA[4] = torque>>8;
			Message.DATA[5] = torque&0xff;
			Message.DATA[6] = torque>>8;
			Message.DATA[7] = torque&0xff;		
			break;
	}
	ROS_INFO("send_torque_control  - R ID:%4x LEN:%1x DATA:%02x %02x %02x %02x %02x %02x %02x %02x\n",
		(int)Message.ID, (int)Message.LEN,
		(int)Message.DATA[0], (int)Message.DATA[1],
		(int)Message.DATA[2], (int)Message.DATA[3],
		(int)Message.DATA[4], (int)Message.DATA[5],
		(int)Message.DATA[6], (int)Message.DATA[7]);
	Status = CAN_Write(pcan_device, &Message);
	return Status;
	//return 0x00000U;
	
}

TPCANStatus sent_break_control(uint16_t break_size)
{
	TPCANMsg Message;
	TPCANStatus Status;
	return Status;
	// CanTxMsg TxSpeed;
	
	// TxSpeed.StdId = CAN_SPEED_ID;//SET the ID of the CAN1 Message
	// TxSpeed.RTR=CAN_RTR_DATA;		
	// TxSpeed.IDE=CAN_ID_STD;//Standard or Extended		
	// TxSpeed.DLC = 8;//Length of Data
	// int i=0;
	// for(i=0;i<=7;i++)
	// 	TxSpeed.Data[i]=0; //clear
		
	// 		TxSpeed.Data[0] = 0;
	// 		TxSpeed.Data[1] = 0;
	// 		TxSpeed.Data[2] = 0;
	// 		TxSpeed.Data[3] = 0;
	// 		TxSpeed.Data[4] = break_size >> 8;
	// 		TxSpeed.Data[5] = break_size&0xff;
	// 		TxSpeed.Data[6] = 0;
	// 		TxSpeed.Data[7] = 0;		
	// CAN_Transmit(CAN1, &TxSpeed);
}









