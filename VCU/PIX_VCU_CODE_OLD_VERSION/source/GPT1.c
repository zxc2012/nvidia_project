//****************************************************************************
// @Module        General Purpose Timer Unit (GPT1)
// @Filename      GPT1.c
// @Project       tiaoshi.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the GPT1 module.
//
//----------------------------------------------------------------------------
// @Date          2020/1/14 16:27:48
//
//****************************************************************************

// USER CODE BEGIN (GPT1_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (GPT1_General,2)
#include "remote.h"
#include "steering.h"
#include "vehicle_control.h"

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (GPT1_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (GPT1_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (GPT1_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (GPT1_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (GPT1_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (GPT1_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (GPT1_General,9)

// USER CODE END


//****************************************************************************
// @Function      void GPT1_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the GPT1 function 
//                library. It is assumed that the SFRs used by this library 
//                are in reset state. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2020/1/14
//
//****************************************************************************

// USER CODE BEGIN (Init,1)

// USER CODE END

void GPT1_vInit(void)
{
  // USER CODE BEGIN (Init,2)

  // USER CODE END
  ///  -----------------------------------------------------------------------
  ///  Configuration of Timer Block Prescaler 1:
  ///  -----------------------------------------------------------------------
  GPT12E_KSCCFG  =  0x0003;      // Module Enable

  _nop_();  // one cycle delay 

  _nop_();  // one cycle delay 



  ///  -----------------------------------------------------------------------
  ///  Configuration of Timer Block Prescaler 1:
  ///  -----------------------------------------------------------------------
  ///  - prescaler for timer block 1 is 4


  ///  -----------------------------------------------------------------------
  ///  Configuration of the GPT1 Core Timer 3:
  ///  -----------------------------------------------------------------------
  ///  - timer 3 works in timer mode
  ///  - external up/down control is disabled
  ///  - prescaler factor is 32
  ///  - up/down control bit is reset
  ///  - alternate output function T3OUT (P7.0) is disabled
  ///  - timer 3 output toggle latch (T3OTL) is set to 0

  GPT12E_T3CON   =  0x0803;      // load timer 3 control register
  GPT12E_T3      =  0x9E58;      // load timer 3 register
  ///  - prescaler for timer block 1 is 4

  ///  -----------------------------------------------------------------------
  ///  Configuration of the GPT1 Auxiliary Timer 2:
  ///  -----------------------------------------------------------------------
  ///  - timer 2 works in timer mode
  ///  - external up/down control is disabled
  ///  - prescaler factor is 8
  ///  - up/down control bit is reset

  GPT12E_T2CON   =  0x0001;      // load timer 2 control register
  GPT12E_T2      =  0x3CB0;      // load timer 2 register
  ///  - prescaler for timer block 1 is 4

  ///  -----------------------------------------------------------------------
  ///  Configuration of the GPT1 Auxiliary Timer 4:
  ///  -----------------------------------------------------------------------
  ///  - timer 4 works in timer mode
  ///  - external up/down control is disabled
  ///  - prescaler factor is 4
  ///  - up/down control bit is reset
  ///  - timer 4 run bit is reset

  GPT12E_T4CON   =  0x0000;      // load timer 4 control register
  GPT12E_T4      =  0x0000;      // load timer 4 register
  ///  - prescaler for timer block 1 is 4

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used GPT1 Port Pins:
  ///  -----------------------------------------------------------------------



  ///  -----------------------------------------------------------------------
  ///  Configuration of the used GPT1 Interrupts:
  ///  -----------------------------------------------------------------------
  ///  timer 2 service request node configuration:
  ///  - timer 2 interrupt priority level (ILVL) = 14
  ///  - timer 2 interrupt group level (GLVL) = 0
  ///  - timer 2 group priority extension (GPX) = 0

  GPT12E_T2IC    =  0x0078;     

  ///  Use PEC channel 0 for GPT1 T2 INT:
  ///  - normal interrupt
  ///  - pointers are not modified
  ///  - transfer a word
  ///  - service End of PEC interrrupt by a EOP interrupt node is disabled
  ///  - channel link mode is disabled

  PECC0          =  0x0000;      // load PECC0 control register


  ///  timer 3 service request node configuration:
  ///  - timer 3 interrupt priority level (ILVL) = 13
  ///  - timer 3 interrupt group level (GLVL) = 0
  ///  - timer 3 group priority extension (GPX) = 0

  GPT12E_T3IC    =  0x0074;     


  // USER CODE BEGIN (GPT1_Function,3)

  // USER CODE END

  GPT12E_T2CON_T2R  =  1;        // set timer 2 run bit

  GPT12E_T3CON_T3R  =  1;        // set timer 3 run bit

} //  End of function GPT1_viTmr4


//****************************************************************************
// @Function      void GPT1_viTmr3(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the GPT1 timer 3. 
//                It is called up in the case of over or underflow of the 
//                timer 3 register.
//                If the incremental interface mode is selected it is called 
//                up if count edge or count direction was detected.
//                
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2020/1/14
//
//****************************************************************************

// USER CODE BEGIN (Tmr3,1)
 int ms_100=0,ms_20=0;
// USER CODE END

void GPT1_viTmr3(void) interrupt T3INT
{
  // USER CODE BEGIN (Tmr3,2)

  // USER CODE END


  // USER CODE BEGIN (Tmr3,5)

  // USER CODE END

} //  End of function GPT1_viTmr3


//****************************************************************************
// @Function      void GPT1_viTmr2(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the GPT1 timer 2. 
//                It is called up in the case of over or underflow of the 
//                timer 2 register.
//                If the incremental interface mode is selected and the 
//                interrupt for this mode is not disabled it is called up if 
//                count edge or count direction was detected.
//                
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2020/1/14
//
//****************************************************************************

// USER CODE BEGIN (Tmr2,1)
 extern struct remote_receive remote_re;
 ubyte vehicle_status[8];
 int back_status_time=0;
// USER CODE END

void GPT1_viTmr2(void) interrupt T2INT
{
  // USER CODE BEGIN (Tmr2,2)
  
  //10ms
   extern struct error_code vehicle_ec;
   extern struct vehicle vehicle_rcv;
//   char vehicle_status[8];
   extern int send_cmd_enable;
   int error_size=0;
   static int count_times;
   ms_100++;
   ms_20++;
   back_status_time++;
   //vehicle_control();
   if(ms_20>5)	//sent control msg
   {
   		ms_20 = 0;
		send_cmd_enable = 0;   //debug
		if(send_cmd_enable==0)
			{
				//send cmd 
			    error_size=vehicle_control();	
			}		
		//	vehicle_control();	
   }
   if(back_status_time>5)
   {
   		back_status_time=0;
		//back status 
		vehicle_status[0]=vehicle_rcv.lfw.rpm&0xff;
		vehicle_status[1]=vehicle_rcv.lfw.rpm>>8;
		vehicle_status[2]=vehicle_rcv.lbw.rpm&0xff;
		vehicle_status[3]=vehicle_rcv.lbw.rpm>>8;
		vehicle_status[4]=vehicle_rcv.rfw.rpm&0xff;
		vehicle_status[5]=vehicle_rcv.rfw.rpm>>8;
		vehicle_status[6]=vehicle_rcv.rbw.rpm&0xff;
		vehicle_status[7]=vehicle_rcv.rbw.rpm>>8;
		CAN_vLoadData(STATUS_196,vehicle_status);
		CAN_vTransmit(STATUS_196);
		delay(500);

		vehicle_status[0]= vehicle_rcv.front_steering.steering_velaus&0xff;
		vehicle_status[1]=vehicle_rcv.front_steering.steering_velaus>>8;
		vehicle_status[2]=vehicle_rcv.back_steering.steering_velaus&0xff;
		vehicle_status[3]=vehicle_rcv.back_steering.steering_velaus>>8;
		vehicle_status[4]=0x00;
		vehicle_status[5]=0x00;
		vehicle_status[6]=0x00;
		vehicle_status[7]=0x00;

		CAN_vLoadData(STATUS_197,vehicle_status);
		CAN_vTransmit(STATUS_197);
		delay(500);	   
   }
   
   if(ms_100>20)   //sent error code msg 
   {
   		ms_100=0;
		count_times ++;
		if(count_times >11)count_times =0;
		//send error code don't need cmd enable
		if(error_size==0)
			vehicle_ec.msg_data[0]=0x00;
		else switch(count_times){
			case 1:
				if(vehicle_ec.remote_error==1)
					vehicle_ec.msg_data[0]=0x0b;
				else  vehicle_ec.msg_data[0]=0x00;
			break;
			case 2:
				if(vehicle_ec.gear_s_error==1)
			vehicle_ec.msg_data[0]=0x0a;
				else  vehicle_ec.msg_data[0]=0x00;
			break;
			case 3:
				if(vehicle_ec.mode_s_error==1)
			vehicle_ec.msg_data[0]=0x09;
			else  vehicle_ec.msg_data[0]=0x00;
			break;
			case 4:
				if(vehicle_ec.break_status==1)
			vehicle_ec.msg_data[0]=0x08;
			else  vehicle_ec.msg_data[0]=0x00;
			break;
			case 5:
				if(vehicle_ec.rbw_status==1)
			vehicle_ec.msg_data[0]=0x07;
			else  vehicle_ec.msg_data[0]=0x00;
			break;
			case 6:
				if(vehicle_ec.rfw_status==1)
			vehicle_ec.msg_data[0]=0x06;
			else  vehicle_ec.msg_data[0]=0x00;
			break;
			case 7:
				if(vehicle_ec.lbw_status==1)
			vehicle_ec.msg_data[0]=0x05;
			else  vehicle_ec.msg_data[0]=0x00;
			break;
			case 8:
				if(vehicle_ec.lfw_status==1)
			vehicle_ec.msg_data[0]=0x04;
			else  vehicle_ec.msg_data[0]=0x00;
			break;
			case 9:
				if(vehicle_ec.bs_status==1)
			vehicle_ec.msg_data[0]=0x03;
			else  vehicle_ec.msg_data[0]=0x00;
			break;
			case 10:
				if(vehicle_ec.fs_status==1)
			vehicle_ec.msg_data[0]=0x02;
			else  vehicle_ec.msg_data[0]=0x00;
			break;
			case 11:
				if(vehicle_ec.ess_status==1)
			vehicle_ec.msg_data[0]=0x01;
			else  vehicle_ec.msg_data[0]=0x00;
			break;

		}	

		CAN_vLoadData(13,vehicle_ec.msg_data);
		CAN_vTransmit(13);
		delay(500);

   }


/*	//柯默电动 10ms中断 主要控制指令发送
	T_Mark_i[3]++;	
	if(T_Mark_i[3] >= 100){T_Mark_i[3] = 0; T_Mark[3]++;}
	if(T_Mark[3]>=100) 	T_Mark[3]=0;
		   																   	 
   // CAN节点0，MO-发送ID181 M3-接收ID182；波特率250K
   // 功能 广播发送CAN_Test,收到信息M3后发送收到的信息
	if(CAN_Mark[3]==1)																		 
	{
		CAN_vLoadData(0,Data3);		//0为消息序号，Data3为数据地址
		CAN_vTransmit(0);
		delay(500);
		CAN_Mark[3] = 0;
    }
	else
	{
		CAN_vLoadData(0,CAN_Test);		
		CAN_vTransmit(0);
		delay(500);
	}

 	//节点1:M1-发送ID183 M4-接收ID185;  节点2:M2-发送ID184 M5-接收ID183;波特率250K
	//功能 节点1与节点2组成CAN网络，节点1发送报文，节点2接收，节点2接收不到后显示断线故障
	CAN_vLoadData(1,CAN_Test);  	
	CAN_vTransmit(1);
	delay(500);
	
	if(CAN_Mark[5]==1)
	{
	 	CAN_Mark[5] = 0;
		CAN_Break_Timer = 0;
		ST[4]=0xFF;ST[5]=0xFF;ST[6]=0x00;
	}
	if(CAN_Mark[5]==0)	CAN_Break_Timer ++;

	if(CAN_Break_Timer >= 100)
	{
		CAN_Break_Timer = 100;
		CAN_Break_Flag = 1;	  
	}	
		
	else
		CAN_Break_Flag = 0;

	if(CAN_Break_Flag==1){ST[4]=0x00;ST[5]=0x00;ST[6]=0xFF;}
	if(CAN_Break_Flag==0){ST[4]=0xFF;ST[5]=0xFF;ST[6]=0x00;}
			   

  // USER CODE END


  // USER CODE BEGIN (Tmr2,5)
 */
   // 柯默电动 设置寄存器
   GPT12E_T3=0x9E58;	   		

  // USER CODE END

} //  End of function GPT1_viTmr2




// USER CODE BEGIN (GPT1_General,10)

// USER CODE END

