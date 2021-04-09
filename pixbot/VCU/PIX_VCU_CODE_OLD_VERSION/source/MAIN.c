//****************************************************************************
// @Module        Project Settings
// @Filename      MAIN.c
// @Project       tiaoshi.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains the project initialization function.
//
//----------------------------------------------------------------------------
// @Date          2020/1/14 16:27:45
//
//****************************************************************************

// USER CODE BEGIN (MAIN_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (MAIN_General,2)
#include "vehicle_control.h"
#include "steering.h"
#include "remote.h"
#include "pid_controler.h"
#include "breaking_control.h"

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (MAIN_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (MAIN_General,4)
extern struct remote_receive remote_re;	
extern struct error_code vehicle_ec;
extern struct vehicle vehicle_rcv;
extern struct self_driving auto_cmd;
extern int time_out_remote;
//extern int delay_time; 
int delay_time;
extern int hand_break_mark,time_hand_break,time_auto_hand_break; //手刹标志位和手刹计时

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (MAIN_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (MAIN_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (MAIN_General,9)

// 柯默电动 此处定义延时函数
void delay(int time)
{
	unsigned int i;
  	for(i=0;i<time;i++)
	{
	 	_nop_();
		_nop_();
		_nop_();
	}
} 

void delay_100ms(int time)
{
	
	delay_time = 0;
	while (delay_time < time){SPI_Control();}
		
}

// 柯默电动 此处定义开关量状态函数
void Switch_State(void)
{
	//ST[0]的状态：1（有效）或者0（无效）。8位从低到高对应SP0-SP7.管脚高电平时有效。

	if(P7_IN_P2==0)				//SP0
	ST[0]=ST[0]|0x01;
	else
	ST[0]=ST[0]&0xfe;

	if(P7_IN_P1==0)				//SP1
	ST[0]=ST[0]|0x02;
	else
	ST[0]=ST[0]&0xfd;

	if(P6_IN_P1==0)				//SP2
	ST[0]=ST[0]|0x04;
	else
	ST[0]=ST[0]&0xfb;

	if(P6_IN_P2==0)				//SP3
	ST[0]=ST[0]|0x08;
	else
	ST[0]=ST[0]&0xf7;

	if(P5_IN_P3==0)				//SP4
	ST[0]=ST[0]|0x10;
	else
	ST[0]=ST[0]&0xef;

	if(P5_IN_P5==0)				//SP5
	ST[0]=ST[0]|0x20;
	else
	ST[0]=ST[0]&0xdf;

	if(P5_IN_P8==0)				//SP6
	ST[0]=ST[0]|0x40;
	else
	ST[0]=ST[0]&0xbf;

	if(P5_IN_P9==0)				//SP7
	ST[0]=ST[0]|0x80;
	else
	ST[0]=ST[0]&0x7f;

    //ST[1]的状态：1（有效）或者0（无效）。8位从低到高对应SG0-SG7.管脚低电平时有效。

	if(P5_IN_P10==0)			//SG0
	ST[1]=ST[1]|0x01;
	else
	ST[1]=ST[1]&0xfe;

	if(P5_IN_P11==0)			//SG1
	ST[1]=ST[1]|0x02;
	else
	ST[1]=ST[1]&0xfd;

	if(P5_IN_P13==0)			//SG2
	ST[1]=ST[1]|0x04;
	else
	ST[1]=ST[1]&0xfb;

	if(P5_IN_P15==0)			//SG3
	ST[1]=ST[1]|0x08;
	else
	ST[1]=ST[1]&0xf7;

	if(P2_IN_P12==0)			//SG4
	ST[1]=ST[1]|0x10;
	else
	ST[1]=ST[1]&0xef;

	if(P2_IN_P11==0)			//SG5
	ST[1]=ST[1]|0x20;
	else
	ST[1]=ST[1]&0xdf;

	if(P2_IN_P2==0)				//SG6
	ST[1]=ST[1]|0x40;
	else
	ST[1]=ST[1]&0xbf;

	if(P4_IN_P0==0)				 //SG7
	ST[1]=ST[1]|0x80;
	else
	ST[1]=ST[1]&0x7f;

    //ST[2]的状态：1（有效）或者0（无效）。7位从低到高对应SG8-SG14.管脚低电平时有效。
	if(P4_IN_P1==0)				//SG8
	ST[2]=ST[2]|0x01;
	else
	ST[2]=ST[2]&0xfe;

	if(P2_IN_P8==0)				//SG9
	ST[2]=ST[2]|0x02;
	else
	ST[2]=ST[2]&0xfd;

	if(P2_IN_P13==0)			//SG10
	ST[2]=ST[2]|0x04;
	else
	ST[2]=ST[2]&0xfb;

	if(P2_IN_P10==0)			//SG11
	ST[2]=ST[2]|0x08;
	else
	ST[2]=ST[2]&0xf7;

	if(P10_IN_P6==0)			//SG12
	ST[2]=ST[2]|0x10;
	else
	ST[2]=ST[2]&0xef;

	if(P10_IN_P7==0)			//SG13
	ST[2]=ST[2]|0x20;
	else
	ST[2]=ST[2]&0xdf;
				   
	if(P1_IN_P7==0)				//SG14
	ST[2]=ST[2]|0x40;
	else
	ST[2]=ST[2]&0xbf;
		
    //ST[3]的状态：1（有效）或者0（无效）。8位从低到高对应SP8-SP15.管脚高电平时有效。

	if(P10_IN_P9==0)			//SP8
	ST[3]=ST[3]|0x01;
	else
	ST[3]=ST[3]&0xfe;

	if(P10_IN_P12==0)			//SP9
	ST[3]=ST[3]|0x02;
	else
	ST[3]=ST[3]&0xfd;

	if(P1_IN_P3==0)				//SP10
	ST[3]=ST[3]|0x04;
	else
	ST[3]=ST[3]&0xfb;

	if(P10_IN_P14==0)			//SP11
	ST[3]=ST[3]|0x08;
	else
	ST[3]=ST[3]&0xf7;

	if(P1_IN_P4==0)				//SP12
	ST[3]=ST[3]|0x10;
	else
	ST[3]=ST[3]&0xef;

	if(P10_IN_P15==0)			//SP13
	ST[3]=ST[3]|0x20;
	else
	ST[3]=ST[3]&0xdf;

	if(P1_IN_P5==0)				//SP14
	ST[3]=ST[3]|0x40;
	else
	ST[3]=ST[3]&0xbf;

	if(P1_IN_P6==0)				//SP15
	ST[3]=ST[3]|0x80;
	else
	ST[3]=ST[3]&0x7f;
}

void Switch_Control(void)
{
	//低边开关：从上到下为1~10 1:off 0:on OUT管脚有效相当于地。
	
	P7_OUT_P3  = ST[4]&0x01;		   			//低边开关1，定义为控制转向及刹车上电信号的继电器引脚  10号引脚接供电 14号地线 63  [10-1 31-2 30-9 32-6 29-3 28-7] 
																																	//[14 18 22 23 24 33 gnd]
	P7_OUT_P4  =(ST[4]>>1)&0x01;			 	//低边开关2，
			
	P6_OUT_P0  =(ST[4]>>2)&0x01;				//低边开关3	 29			   
			
	P10_OUT_P10=(ST[4]>>3)&0x01;		   		//低边开关4	 12
			
	P10_OUT_P11=(ST[4]>>4)&0x01;		   		//低边开关5	 9
			
	P1_OUT_P2  =(ST[4]>>5)&0x01; 				//低边开关6	 32
			     
	P10_OUT_P8 =(ST[4]>>6)&0x01;		   		//低边开关7	 28
			
	P10_OUT_P13=(ST[4]>>7)&0x01;				//低边开关8	 13
			
	P0_OUT_P7  = ST[5]&0x01;		   			//低边开关9	 30
			
	P1_OUT_P0  =(ST[5]>>1)&0x01;		   		//低边开关10  11
			 			 
	//高边开关：从上到下为1~4 1:on 0:off，OUT管脚有效相当于+24V/12V。
				  
	P10_OUT_P3 = ST[6]&0x01;					//高边开关1	  63 前大灯  
			
	P0_OUT_P5  =(ST[6]>>1)&0x01;		   		//高边开关2	  64 后大灯
			
	P10_OUT_P4 =(ST[6]>>2)&0x01;	   			//高边开关3
			
	P1_OUT_P1  =(ST[6]>>3)&0x01;		  		//高边开关4		
}

// 柯默电动 此处定义模数转换函数 从上到下是通道AI1~6
void ADC_State(void)								  
{
	ADC1_vStartSeq0ReqChNum(0,0,0,0);
	while(!(ADC1_RCR0 & 0x1000));	       			//AI1，5V对应0x03FF。              			 
    ADC_High[1]=((ADC1_RESR0>>2)&0x0300)>>8;		//high 2bit
	ADC_Low[1] =((ADC1_RESR0>>2)&0x00ff);	   		//low  8bit
	delay(500);

	ADC1_vStartSeq0ReqChNum(0,0,0,2);
	while(!(ADC1_RCR2 & 0x1000));					//AI2，5V对应0x03FF。		 
	ADC_High[2]=((ADC1_RESR2>>2)&0x0300)>>8;	    //high 2bit
	ADC_Low[2] =((ADC1_RESR2>>2)&0x00ff);        	//low  8bit
   	delay(500);	

	ADC1_vStartSeq0ReqChNum(0,0,0,4);
	while(!(ADC1_RCR4 & 0x1000));          			//AI3，5V对应0x03FF。
	ADC_High[3]=((ADC1_RESR4>>2)&0x0300)>>8;		//high 2bit	  
	ADC_Low[3] =((ADC1_RESR4>>2)&0x00ff);			//low  8bit
	delay(500);

    ADC1_vStartSeq0ReqChNum(0,0,0,5);
	while(!(ADC1_RCR5 & 0x1000));					// AI4，24V/5V对应0x03FF。
	ADC_High[4]=((ADC1_RESR5>>2)&0x0300)>>8;		//high 2bit		
	ADC_Low[4] =((ADC1_RESR5>>2)&0x00ff);			//low  8bit 
	delay(500);

	ADC1_vStartSeq0ReqChNum(0,0,0,6);
	while(!(ADC1_RCR6 & 0x1000));		   			// AI5，24V/5V对应0x03FF。
	ADC_High[5]=((ADC1_RESR6>>2)&0x0300)>>8;		//high 2bit
	ADC_Low[5] =((ADC1_RESR6>>2)&0x00ff);			//low  8bit
	delay(500);

	ADC0_vStartSeq0ReqChNum(0,0,0,0);
	while(!(ADC0_RCR0 & 0x1000));					// AI6，24V/5V对应0x03FF。
	ADC_High[6]=((ADC0_RESR0>>2)&0x0300)>>8;		//high 2bit	
	ADC_Low[6] =((ADC0_RESR0>>2)&0x00ff);			//low  8bit
}

// 柯默电动 此处定义低边开关SPI控制模式 本函数需在while中循环
void SPI_Control(void)
{
	P0_OUT_P3=1;							  //
	delay(3);				   				  //
   	P0_OUT_P3=0;							  //
	delay(3);								  //
											  //
	U1C0_SSC_vSendData(0x24ff);			      //
    while(!U1C0_SSC_ubTxDataReady());		  //
											  //
	P0_OUT_P3=1;							  //
	delay(3);								  //
	P0_OUT_P3=0;							  //
	delay(3);								  //
	U1C0_SSC_vSendData(0x27ff); 			  //
    while(!U1C0_SSC_ubTxDataReady());		  //
 											  //
	P0_OUT_P3=1;							  //
	delay(3);								  //
	P0_OUT_P3=0;							  //
	delay(3);								  //
	U1C0_SSC_vSendData(0x2ecf); 			  //
    while(!U1C0_SSC_ubTxDataReady());		  //
											  //
	delay(3);								  //
    P0_OUT_P3=1;	                   		  //
} 
										
// USER CODE END


//****************************************************************************
// @Function      void MAIN_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This function initializes the microcontroller.
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

void MAIN_vInit(void)
{

  SCS_ErrorType Error;

  // USER CODE BEGIN (Init,2)
  auto_cmd.steering = 7800;
  // USER CODE END

  //   globally disable interrupts
  PSW_IEN        =  0;          

  ///  -----------------------------------------------------------------------
  ///  Configuration of the System Clock:
  ///  -----------------------------------------------------------------------
  ///  - VCO clock used, input clock is connected
  ///  - input frequency is 8.00 MHz
  ///  - configured system frequency is 80.00 MHz
  ///  - system clock is 80.00MHz

  MAIN_vUnlockProtecReg();     // unlock write security

  // initialize CCU6 timer T13 for SCS driver
  SCS_InitTimer();

  // perform transition from base mode to normal operating mode
  Error = SCS_GoFromBaseToNormalMode();

  // restore CCU6 timer used by SCS driver
  SCS_RestoreTimer();

  //   -----------------------------------------------------------------------
  //   Initialization of the Peripherals:
  //   -----------------------------------------------------------------------

  //   initializes the Parallel Ports
  IO_vInit();

  //   initializes the General Purpose Timer Unit (GPT1)
  GPT1_vInit();

  //   initializes the General Purpose Timer Unit (GPT2)
  GPT2_vInit();

  //   initializes the Analog / Digital Converter  (ADC0)
  ADC0_vInit();

  //   initializes the Analog / Digital Converter (ADC1)
  ADC1_vInit();

  //   initializes the MultiCAN Module (CAN)
  CAN_vInit();

  //   initializes the USIC0 Module
  USIC0_vInit();

  //   initializes the USIC1 Module
  USIC1_vInit();


  //   -----------------------------------------------------------------------
  //   Initialization of the Bank Select registers:
  //   -----------------------------------------------------------------------


  // USER CODE BEGIN (Init,3)

  delay(1000);

  // USER CODE END

  MAIN_vLockProtecReg();       // lock write security

  //   globally enable interrupts
  PSW_IEN        =  1;          

} //  End of function MAIN_vInit


//****************************************************************************
// @Function      void MAIN_vUnlockProtecReg(void) 
//
//----------------------------------------------------------------------------
// @Description   This function makes it possible to write one protected 
//                register.
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

// USER CODE BEGIN (UnlockProtecReg,1)

// USER CODE END

void MAIN_vUnlockProtecReg(void)
{

    SCU_SLC = 0xAAAA;                   // command 0
    SCU_SLC = 0x5554;                   // command 1
    SCU_SLC = 0x96FF;                   // command 2
    SCU_SLC = 0x0000;                   // command 3

} //  End of function MAIN_vUnlockProtecReg


//****************************************************************************
// @Function      void MAIN_vLockProtecReg(void) 
//
//----------------------------------------------------------------------------
// @Description   This function makes it possible to lock one protected 
//                register.
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

// USER CODE BEGIN (LockProtecReg,1)

// USER CODE END

void MAIN_vLockProtecReg(void)
{

    SCU_SLC = 0xAAAA;                   // command 0
    SCU_SLC = 0x5554;                   // command 1
    SCU_SLC = 0x96FF;                   // command 2
    SCU_SLC = 0x1800;                   // command 3;
    SCU_SLC = 0x8EFF;                   // command 4

} //  End of function MAIN_vLockProtecReg


//****************************************************************************
// @Function      void main(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the main function.
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

// USER CODE BEGIN (Main,1)

// 柯默电动 此处进行变量定义 在MAIN.H中进行变量全局声明
ubyte ST[8]; 															// 开关量采集及控制

ubyte Data3[8], Data4[8], Data5[8],CAN_Mark[8];							// CAN接收数据 中断标志 测试发送数据
ubyte CAN_Test[8]={0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF}; 
ubyte CAN_Break_Timer=0,CAN_Break_Flag=0; 								// CAN断线时间 断线标志

ubyte CC2_Mark[8],Period_Low[8],Period_High[8]; 						// 霍尔轮速 捕捉中断 周期高低字节
uword Period[8];   														// 周期

ubyte ADC_High[8]={0},ADC_Low[8]={0};  									// 模拟量转换高低字节

ubyte T_Mark[8]={0},T_Mark_i[8]={0};   									// 定时器标志


// USER CODE END

void main(void)
{
  // USER CODE BEGIN (Main,2)
  extern int autohold_mark;
  extern int servo_breaking_init();
  int em_stop_mark=0;
  int times=0;
  int time_i=0;
	//柯默电动 初始化变量
	ST[4] = 0xFF; 
	ST[5] = 0xFF;
	ST[6] = 0x00;

  // USER CODE END

  MAIN_vInit();

  // USER CODE BEGIN (Main,3)

	SPI_Control();	 
	servo_breaking_init();	
	P7_OUT_P3 = 1;	//10 左转向
	P7_OUT_P4 = 1;	//31 电子手刹放
	P6_OUT_P0 =1;	//29 前尾灯
	P10_OUT_P10 =1;	//12 示宽灯
	P10_OUT_P11 =1;	//9  制动灯
	P1_OUT_P2  =1;	//32 电子手刹拉
	P10_OUT_P8=1;	//28 上电信号
	P10_OUT_P13 =1;	//13 尾灯
	P0_OUT_P7=1;	//30 前制动灯
	P1_OUT_P0 =1;	//11 右转向

	P10_OUT_P3 =0;  //  后大灯
	P0_OUT_P5=0;	//前大灯
	
	P10_OUT_P10 =0;	
	time_out_remote = 0x55;	
	remote_re.key=TRUE;   
	while(remote_re.key==TRUE);  //等待接收到遥控器信号 					
	//delay_100ms(1);	
	SPI_Control();
	//闪烁两秒表示启动

	for(delay_time=0;delay_time<20;){P1_OUT_P0 =0;P7_OUT_P3 =0;SPI_Control();}
	P7_OUT_P3 = 1;
	P1_OUT_P0 =1;
	//初始化手刹
	hand_break_mark = FALSE;
	for(delay_time=0;delay_time<30;){autohold(TRUE);SPI_Control();}
	//hand_break_mark = TRUE;
	//for(delay_time=0;delay_time<30;){autohold(FALSE);SPI_Control();}
	//上电信号
	P10_OUT_P8=0;
	P10_OUT_P13 =0;
	P10_OUT_P10=0;
	
  // USER CODE END

  while(1)
  {

   // USER CODE BEGIN (Main,4)

	SPI_Control();	  				// SPI控制 while中循环

	//ADC_State();   					// 模拟量状态采集函数 
	
	Switch_State();					// 开关量状态采集函数   

	//Switch_Control();  				// 开关量控制函数

	if(remote_re.t_em_stop == TRUE||remote_re.key==TRUE)//急停或者遥控信号丢失	
	{
	   	P7_OUT_P3 = 0;
		P1_OUT_P0 =0;
		remote_re.t_way_trl=0;
		if(vehicle_rcv.lfw.rpm+vehicle_rcv.lbw.rpm+vehicle_rcv.rfw.rpm\
  	+vehicle_rcv.rbw.rpm>0||hand_break_mark==FALSE)send_break(BREAKING_MAX,0x10);
		else send_break(BREAKING_FREE,0x10);
		em_stop_mark=1;
	}else if(remote_re.t_em_stop == FALSE&&remote_re.key==FALSE&&em_stop_mark==1)
	{
	   	P7_OUT_P3 = 1;
		P1_OUT_P0 =1;
		remote_re.t_way_trl=0; //遥控模式
		send_break(BREAKING_FREE,0x10);	
		em_stop_mark=0;
	}	

	if(remote_re.hand_break==TRUE)  // 拉手刹,禁止发送速度值			 //||auto_cmd.hand_break==TRUE //||auto_cmd.hand_break==TRUE
		autohold(TRUE);
	else if(remote_re.hand_break==FALSE&&autohold_mark==0) 
		autohold(FALSE);

	if(time_hand_break>15)//保护电机避免堵转
	{
		P7_OUT_P4=1;
		P1_OUT_P2=1;
		}
/*	//测试大灯开关			
	if(remote_re.t_backup1 == 1)
		P0_OUT_P5 = 1;
	else if(remote_re.t_backup1 == 2){
		P10_OUT_P3=0;
		P0_OUT_P5=0;
	}else if(remote_re.t_backup1 == 3)	
		P10_OUT_P3=1;
*/
	//auto_autohold();//自动手刹

		   
   // USER CODE END

  }

} //  End of function main



// USER CODE BEGIN (MAIN_General,10)

// USER CODE END

