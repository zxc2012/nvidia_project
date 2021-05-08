#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <autoware_msgs/VehicleCmd.h>
#include <thread>
#include <mutex>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "controlcan.h"

#include <ctime>
#include <cstdlib>
#include "unistd.h"

using namespace std;

void send_out(int t_speed,int t_steering);
void pubCANThread();


ros::Subscriber subCmdVel;
ros::Publisher pubVehicleCmd;

std::mutex mtx; // 互斥锁

VCI_INIT_CONFIG config;
VCI_CAN_OBJ message[1];

void cmdVelHandler(const geometry_msgs::TwistConstPtr& twistin){
    double angular_pi = twistin->angular.z;
    double speed_ms = twistin->linear.x;
    double steer_degree = 0;

    //汽车转角
    steer_degree = atan2(-angular_pi/4.0,1)*180/3.14;        // 当omega=1，大约转15度

    if(steer_degree > 30){
        steer_degree = 30;
    }else if(steer_degree < -30){
        steer_degree = -30;
    }
    double vel_real = steer_degree *(1024/30);
    int vel_steering = vel_real;
    //汽车速度
    int vel_speed=(int)(speed_ms*3600/1000*10);
    if(vel_speed>600){
        vel_speed=600;
    }else if(vel_speed<-600){
        vel_speed=-600;
    }
    cout << endl;
    cout<<"转角："<<steer_degree<<" 度"<<"  速度："<<speed_ms<<" m/s"<<endl;
    if(vel_speed<0){
        vel_steering = -vel_steering;
    }
    send_out(vel_speed,vel_steering);
}

void send_out(int t_speed,int t_steering){
    std::lock_guard<std::mutex> lock(mtx); //上锁
    //需要发送的帧，结构体设置
    if(t_speed>=0){
        message[0].Data[0] = t_speed & 0xff;
        message[0].Data[1] = t_speed >> 8;     // 速度位
        message[0].Data[2] = 0x00;             
        message[0].Data[3] = 0x00;             // 刹车位
        message[0].Data[4] = t_steering & 0xff;    
        message[0].Data[5] = t_steering >> 8;      // 转向位
        message[0].Data[6] = 0x11;                 // D档 差分转向
        message[0].Data[7] = 0x80;                 // 自动驾驶使能
    }else{
        t_speed = abs(t_speed);
        message[0].Data[0] = t_speed & 0xff;
        message[0].Data[1] = t_speed >> 8;     // 速度位
        message[0].Data[2] = 0x00;             
        message[0].Data[3] = 0x00;             // 刹车位
        message[0].Data[4] = t_steering & 0xff;    
        message[0].Data[5] = t_steering >> 8;      // 转向位
        message[0].Data[6] = 0x13;                 // R档 差分转向
        message[0].Data[7] = 0x80;                 // 自动驾驶使能      
    }
    for(int i = 0; i < message[0].DataLen; i++)
	{
		printf(" %02x", message[0].Data[i]);
	}
    printf("\n");
}

void pubCANThread()
{
    while(ros::ok()){
        VCI_Transmit(VCI_USBCAN2, 0, 0, message, 1);
		usleep(20000);//延时20ms。
    }
    return;
}


int main(int argc, char** argv){
    ros::init(argc, argv, "control_test");
    ros::NodeHandle nh;
    
    subCmdVel = nh.subscribe<geometry_msgs::Twist>("/cmd_vel",1,&cmdVelHandler);

    std::thread pubCANthread(pubCANThread);

    // 初始化设备
    if(VCI_OpenDevice(VCI_USBCAN2,0,0)==1)//打开设备
	{
		printf(">>open deivce success!\n");//打开设备成功
	}else
	{
		printf(">>open deivce error!\n");
		exit(1);
	}
    // 初始化CAN口
    config.AccCode=0;
    config.AccMask=0xFFFFFFFF;
    config.Filter=1;            //接收所有帧
    config.Timing0=0x00;        /*波特率125 Kbps  0x03  0x1C*/
    config.Timing1=0x1C;
    config.Mode=0;              //正常模式
    //初始化message
    message[0].ID=0x183;
    message[0].SendType=0;
    message[0].RemoteFlag=0;
    message[0].ExternFlag=0;
    message[0].DataLen=8;

    if(VCI_InitCAN(VCI_USBCAN2,0,0,&config)!=1)
	{
		printf(">>Init CAN1 error\n");
		VCI_CloseDevice(VCI_USBCAN2,0);
	}

	if(VCI_StartCAN(VCI_USBCAN2,0,0)!=1)
	{
		printf(">>Start CAN1 error\n");
		VCI_CloseDevice(VCI_USBCAN2,0);

	}

    ROS_INFO("\033[1;32m----> Control Test Started.\033[0m");

    ros::spin();

    pubCANthread.join();

    return 0;
}