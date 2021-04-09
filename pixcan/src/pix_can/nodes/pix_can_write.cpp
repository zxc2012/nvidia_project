/**********************************************************************
 * Date: 2019.11.4
 * Author: wmm & tao
 * 
 **********************************************************************/

#include <ros/ros.h>
#include "autoware_msgs/VehicleCmd.h"
#include <std_msgs/Int32.h>
#include <std_msgs/UInt16.h>
#include "autoware_can_msgs/CANInfo.h"
#include "vehicle_speed_control.h" 
#include "pix_can/CANTestInfo.h"

//#define SPEED_LIMIT 8

static autoware_msgs::VehicleCmd vehicle_msg;
static bool initialized = true;
static bool speed_initialized = true;
static uint16_t current_speed; // speed from chassis
static int count = 0;
static ros::Publisher testinfo_pub;
static pix_can::CANTestInfo test_info;


static void vehicleCmdCallback(const autoware_msgs::VehicleCmd& msg)
{
	vehicle_msg = msg;
	initialized = true;

}

void caninfoCallback(const std_msgs::UInt16& msg)
{
  current_speed = msg.data;
  ROS_INFO("caninfoCallback current_speed:%d",current_speed);
  speed_initialized = true;
}

void timerCallback(const ros::TimerEvent &te)
{
	TPCANStatus Status;
	if (initialized && speed_initialized)
	{
		double omega = vehicle_msg.twist_cmd.twist.angular.z;
		double speed_ms = fabs(vehicle_msg.twist_cmd.twist.linear.x);
                double steer_degree = 0;
		if (speed_ms > 1e-6)
            steer_degree = atan((-omega/speed_ms)*1.9) * 180/3.14;
		if(steer_degree > 30){
			steer_degree = 30;
		}else if(steer_degree < -30){
			steer_degree = -30;
		}
        double vs_real = steer_degree * (1024/30);
        int  vel_steering=vs_real ;
        ROS_INFO("omega: %lf, vel_steering: %d degree, steer_degree: %lf, vs_real: %lf", omega,vel_steering, steer_degree, vs_real);
		uint8_t vel_speed=(uint8_t)(speed_ms * 3600 / 1000)*10;
		//if(vel_speed > SPEED_LIMIT){
		//	vel_speed = SPEED_LIMIT;
		//}
		ROS_INFO("export: vel_speed: %d KM/H",vel_speed);
		uint16_t target_wheel_speed = get_vehicle2whell_speed(vel_speed);
		send_out_183(vel_speed,vel_steering);
	//	vehicle_control(vel_steering, current_speed, target_wheel_speed, vel_shift);
		test_info.current_wheel = current_speed;
		test_info.target_wheel = target_wheel_speed;
		testinfo_pub.publish(test_info);

	}else{
		usleep(100);
	}
}


TPCANStatus send_out_183(int t_speed,int t_steering){

	TPCANMsg Message;
        TPCANStatus Status;
         
        memset(Message.DATA, '\0', sizeof(Message.DATA));
        ROS_INFO("start send message steer!!!!!");
        // TODO set message according to vehicle_msg
        // reset DATA to 0 first
        // Message.DATA[0] = ....

        //int16_t new_agle=0;
        Message.ID = 0x183;//SET the ID of the CAN1 Message               
        Message.LEN = 8;//Length of Data
        Message.MSGTYPE = PCAN_MESSAGE_STANDARD; // TODO check it
        // int i=0;
        // for(i=0;i<=7;i++)
        //      TxSteering.Data[i]=0; //clear
        //new_agle = (int16_t)((float)old_agle * (120.0/21));
        // new_agle = (int16_t)(((float)old_agle*0.0154)-0x78);//((float)old_agle*0.0037)-0x78; //sub bias 
//      if(0x100<break_size&&break_size<0x4b0)//0x4b0 if max break size
//              break_size = 0x100;
        Message.DATA[0] = t_speed&0xff;
	Message.DATA[1] = t_speed>>8;
        Message.DATA[2] = 0x00;
        Message.DATA[3] = 0x00; 
        Message.DATA[4] = t_steering&0xff;
        Message.DATA[5] = t_steering>>8;
        Message.DATA[6] = 0x11;
	Message.DATA[7] = 0X80;

        ROS_INFO(" steer - R ID:%4x LEN:%1x DATA:%02x %02x %02x %02x %02x %02x %02x %02x\n",
                (int)Message.ID, (int)Message.LEN,
                (int)Message.DATA[0], (int)Message.DATA[1],
                (int)Message.DATA[2], (int)Message.DATA[3],
                (int)Message.DATA[4], (int)Message.DATA[5],
                (int)Message.DATA[6], (int)Message.DATA[7]);

        Status = CAN_Write(pcan_device, &Message);
	ROS_INFO("CAN_info(%xh): Status=0x%x\n", pcan_device, (int )Status);

        return Status;

}

void testCallback(const ros::TimerEvent &te)
{
	if(count < 2){
		ROS_INFO("------------------stop----------------------------");
		autoware_msgs::VehicleCmd test_msg;
		test_msg.twist_cmd.twist.angular.z = 0;
		test_msg.twist_cmd.twist.linear.x = 0;	
		vehicle_msg = test_msg;
	}else if(count < 10){
		ROS_INFO("------------------go----------------------------");
		autoware_msgs::VehicleCmd test_msg;
		test_msg.twist_cmd.twist.angular.z = 0;
		test_msg.twist_cmd.twist.linear.x =1.93;// 0.84;	
		vehicle_msg = test_msg;
	}else{
		ROS_INFO("------------------stop----------------------------");
		autoware_msgs::VehicleCmd test_msg;
		test_msg.twist_cmd.twist.angular.z = 0;
		test_msg.twist_cmd.twist.linear.x = 0;	
		vehicle_msg = test_msg;
	}
	count ++;
}


int main(int argc, char* argv[]) 
{
	init_can();
	ros::init(argc ,argv, "pix_can_write");
	ros::NodeHandle nh;

	ROS_INFO("start node pix_can_write!!!!");
	ros::Subscriber sub = nh.subscribe("/vehicle_cmd", 1, vehicleCmdCallback);
	ros::Subscriber sub_can_info = nh.subscribe("/pix_wheel_speed", 1, caninfoCallback);
	ros::Publisher pub = nh.advertise<std_msgs::Int32>("/pix_can_state" , 1, true);
	std_msgs::Int32 state_cmd;
	state_cmd.data = 1;
	pub.publish(state_cmd);
	testinfo_pub = nh.advertise<pix_can::CANTestInfo>("/pixcan_test_info" , 100);

	double ctrl_period_ = 0.01; // control frequency [s]
	ros::Timer timer_control_ = nh.createTimer(ros::Duration(ctrl_period_), timerCallback);
	// ros::Timer timer_control_test = nh.createTimer(ros::Duration(5), testCallback);
	// CAN_Uninitialize(pcan_device);

	ros::spin();
	return 0;
}
