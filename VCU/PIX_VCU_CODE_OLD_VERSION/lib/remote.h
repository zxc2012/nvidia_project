
#ifndef __REMOTE_H
#define __REMOTE_H

//creat a Structure use receive remote data 
struct remote_receive{
	uword t_steering_vle;
	uword t_breaking_vle;
	uword t_throttle_vle;
	ubyte t_gear;	//挡位
	ubyte t_backup1;//备用开关1
	ubyte t_backup3;//备用开关3
	ubyte t_steering_mod; //转向模式
	ubyte t_way_trl;	  // 模式切换
	ubyte cabin_ctl;	  //舱门控制
	ubyte separate;		  //  舱体分离控制
	ubyte auto_joint;	  //自动对接
	ubyte t_em_stop;	  //急停
	ubyte hand_break;	  //电子手刹
	ubyte low_speed_mod;
	ubyte key;			  //使能
	ubyte t_remote_status; //状态
};















#endif


