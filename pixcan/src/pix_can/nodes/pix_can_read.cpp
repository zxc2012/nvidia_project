/**********************************************************************
 * Date: 2019.11.4
 * Author: wmm & tao
 * 
 **********************************************************************/

#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/UInt16.h>
#include <pthread.h>
#include "autoware_can_msgs/CANInfo.h"
#include "vehicle_speed_control.h" 


static ros::Publisher can_pub;
static ros::Publisher speed_pub;
struct WheelRotateSpeed Current_Wrs;
static std_msgs::UInt16 wheel_speed_msg;
static autoware_can_msgs::CANInfo can_msg;
static bool show_debug = false;
static int direction;
static double steer;

void timerCallback(const ros::TimerEvent &te)
{

	wheel_speed_msg.data = average_whell_speed(Current_Wrs);
	speed_pub.publish(wheel_speed_msg);
	can_msg.speed = get_whell2vehicle_speed(Current_Wrs); // km/h
	can_msg.driveshift = direction;
	can_msg.angle = steer;
	can_pub.publish(can_msg);
	ROS_INFO("pix_can_read: wheel_speed:%d  speed(km/h):%lf  direction:%d  steer:%lf", wheel_speed_msg.data, can_msg.speed, can_msg.driveshift, can_msg.angle);

}

static void* receiverCaller(void *unused)
{
	while(true){
		TPCANMsg Message;
		TPCANStatus Status;
		memset(Message.DATA, '\0', sizeof(Message.DATA));
		Status=CAN_Read(pcan_device, &Message, NULL);
		if (Status != PCAN_ERROR_OK) {
			ROS_INFO("CAN_Read(%xh) failure 0x%x\n", pcan_device, (int)Status);
			usleep(1000000);
			continue;
		}
		bool show_info = false;

		autoware_can_msgs::CANInfo can_msg;
				switch (Message.ID){
			case LAWELL_ID:
					show_info = true;
					Current_Wrs.la = (uint16_t)Message.DATA[1]<<8;
					Current_Wrs.la += Message.DATA[0];
					if(Current_Wrs.la>0xf000){//D
						// can_msg.driveshift = 1;
						direction = 1;
						Current_Wrs.la = ~(Current_Wrs.la)+1;
					}
					else if(Current_Wrs.la == 0x0000){
						direction = 2;
					}
					else{
						direction = 3;
						// can_msg.driveshift = 3;
					}

				break;
			case LBWELL_ID:
					show_info = true;
					Current_Wrs.lb = (uint16_t)Message.DATA[1]<<8;
					Current_Wrs.lb += Message.DATA[0];
					if(Current_Wrs.lb > 0xf000)//D
						Current_Wrs.lb = ~(Current_Wrs.lb)+1;
				break;
			case RAWELL_ID:
					show_info = true;
					Current_Wrs.ra = (uint16_t)Message.DATA[1]<<8;
					Current_Wrs.ra += Message.DATA[0];
					if(Current_Wrs.ra>0xf000)//D
						Current_Wrs.ra = ~(Current_Wrs.ra)+1;
				break;
			case RBWELL_ID:
					show_info = true;
					Current_Wrs.rb = (uint16_t)Message.DATA[1]<<8;
					Current_Wrs.rb += Message.DATA[0];
					if(Current_Wrs.rb > 0xf000)//D
						Current_Wrs.rb = ~(Current_Wrs.rb)+1;
				break;
			case WHEEL_STEER_ID:
					show_info = true;
					uint16_t steer_raw = (uint16_t)Message.DATA[1]<<8;
					steer_raw += Message.DATA[0];
					int sign = -1;
					if(steer_raw > 0xf000){
						sign = 1;
						steer_raw = ~(steer_raw)+1;
					}
					steer = sign * (double)steer_raw * (30.0/1024.0);
					ROS_INFO("read steer: %lf , direction: %d", steer,direction);
				break;


		}
		if (show_debug&&show_info){
			ROS_INFO("  - R ID:%4x LEN:%1x DATA:%02x %02x %02x %02x %02x %02x %02x %02x\n",
				(int)Message.ID, (int)Message.LEN,
				(int)Message.DATA[0], (int)Message.DATA[1],
				(int)Message.DATA[2], (int)Message.DATA[3],
				(int)Message.DATA[4], (int)Message.DATA[5],
				(int)Message.DATA[6], (int)Message.DATA[7]);
		}

	}


}

int main(int argc, char* argv[]) 
{
	init_can();
	ros::init(argc ,argv, "pix_can_read");
	ros::NodeHandle nh;

	ROS_INFO("start node pix_can_read!!!!");
	ros::Publisher pub = nh.advertise<std_msgs::Int32>("/pix_can_state" , 1, true);
	std_msgs::Int32 state_cmd;
	state_cmd.data = 1;
	pub.publish(state_cmd);
	can_pub = nh.advertise<autoware_can_msgs::CANInfo>("/can_info", 100);
	speed_pub = nh.advertise<std_msgs::UInt16>("/pix_wheel_speed", 1);
	
	double ctrl_period_ = 0.005; // control frequency [s]
	ros::Timer timer_control_ = nh.createTimer(ros::Duration(ctrl_period_), timerCallback);
	pthread_t th;
	if(pthread_create(&th, nullptr, receiverCaller, nullptr) != 0){
		std::perror("pthread_create");
		std::exit(1);
	}

	if (pthread_detach(th) != 0){
		std::perror("pthread_detach");
		std::exit(1);
	}

	// CAN_Uninitialize(pcan_device);

	ros::spin();
	return 0;
}
