
#ifndef __REMOTE_H
#define __REMOTE_H

//creat a Structure use receive remote data 
struct remote_receive{
	uword t_steering_vle;
	uword t_breaking_vle;
	uword t_throttle_vle;
	ubyte t_gear;	//��λ
	ubyte t_backup1;//���ÿ���1
	ubyte t_backup3;//���ÿ���3
	ubyte t_steering_mod; //ת��ģʽ
	ubyte t_way_trl;	  // ģʽ�л�
	ubyte cabin_ctl;	  //���ſ���
	ubyte separate;		  //  ����������
	ubyte auto_joint;	  //�Զ��Խ�
	ubyte t_em_stop;	  //��ͣ
	ubyte hand_break;	  //������ɲ
	ubyte low_speed_mod;
	ubyte key;			  //ʹ��
	ubyte t_remote_status; //״̬
};















#endif


