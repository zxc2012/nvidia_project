//****************************************************************************
// @Module        General Purpose Timer Unit (GPT2)
// @Filename      GPT2.c
// @Project       tiaoshi.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the GPT2 module.
//
//----------------------------------------------------------------------------
// @Date          2020/1/14 16:27:48
//
//****************************************************************************

// USER CODE BEGIN (GPT2_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (GPT2_General,2)
#include "remote.h"
#include "steering.h"
#include "vehicle_control.h"
// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (GPT2_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (GPT2_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (GPT2_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (GPT2_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (GPT2_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (GPT2_General,8)

// USER CODE END



//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (GPT2_General,9)

// USER CODE END


//****************************************************************************
// @Function      void GPT2_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the GPT2 function 
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

void GPT2_vInit(void)
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
  ///  Configuration of Timer Block Prescaler 2:
  ///  -----------------------------------------------------------------------
  ///  - prescaler for timer block 2 is 4


  ///  -----------------------------------------------------------------------
  ///  Configuration of the GPT2 Core Timer 5:
  ///  -----------------------------------------------------------------------
  ///  - timer 5 works in timer mode
  ///  - prescaler factor is 128
  ///  - up/down control bit is reset
  ///  - external up/down control is disabled
  ///  - timer 5 remote control is disabled

  GPT12E_T5CON   =  0x0005;      // load timer 5 control register
  GPT12E_T5      =  0x85EE;      // load timer 5 register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the GPT2 Core Timer 6:
  ///  -----------------------------------------------------------------------
  ///  - timer 6 works in timer mode
  ///  - prescaler factor is 128
  ///  - up/down control bit is reset
  ///  - external up/down control is disabled
  ///  - alternate output function T6OUT (P6.2) is disabled
  ///  - alternate output function T6OUT (P7.0) is disabled
  ///  - timer 6 output toggle latch (T6OTL) is set to 0
  ///  - timer 6 is not cleared on a capture

  GPT12E_T6CON   =  0x0005;      // load timer 6 control register
  GPT12E_T6      =  0x85EE;      // load timer 6 register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the GPT2 CAPREL:
  ///  -----------------------------------------------------------------------
  ///  - capture T5 into CAPREL is disabled
  ///  - capture trigger from pin CAPIN
  ///  - capure is disabled
  ///  - timer 5 is not cleared on a capture
  ///  - timer 5 is just captured without any correction

  GPT12E_T5CON  |=  0x0000;      // load timer 5 control register
  GPT12E_CAPREL  =  0x0000;      // load CAPREL register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used GPT2 Port Pins:
  ///  -----------------------------------------------------------------------



  ///  -----------------------------------------------------------------------
  ///  Configuration of the used GPT2 Interrupts:
  ///  -----------------------------------------------------------------------
  ///  timer 5 service request node configuration:
  ///  - timer 5 interrupt priority level (ILVL) = 11
  ///  - timer 5 interrupt group level (GLVL) = 0
  ///  - timer 5 group priority extension (GPX) = 0

  GPT12E_T5IC    =  0x006C;     

  ///  timer 6 service request node configuration:
  ///  - timer 6 interrupt priority level (ILVL) = 12
  ///  - timer 6 interrupt group level (GLVL) = 0
  ///  - timer 6 group priority extension (GPX) = 0

  GPT12E_T6IC    =  0x0070;     



  // USER CODE BEGIN (GPT2_Function,3)

  // USER CODE END

  GPT12E_T5CON_T5R  =  1;        // set timer 5 run bit

  GPT12E_T6CON_T6R  =  1;        // set timer 6 run bit

} //  End of function GPT2_viCAPREL

//****************************************************************************
// @Function      void GPT2_viTmr6(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the GPT2 timer 6. 
//                It is called up in the case of over or underflow of the 
//                timer 6 register.
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

// USER CODE BEGIN (Tmr6,1)
	
	//  100ms定时器
	// GPT12E_T6=0xC2F7；
	//command recive time out data clean
int time_out_remote =0,time_out_auto=0;
extern int delay_time;
  	extern struct self_driving auto_cmd;
	extern struct remote_receive remote_re;
	extern int time_hand_break,hand_break_mark,time_auto_hand_break;
// USER CODE END

void GPT2_viTmr6(void) interrupt T6INT
{
  // USER CODE BEGIN (Tmr6,2)

	time_out_auto++;
	time_out_remote++;
	time_hand_break++;
	time_auto_hand_break++;
  	T_Mark_i[6]++;	
	if(T_Mark_i[6] >= 10){T_Mark_i[6] = 0; T_Mark[6]++;}
	if(T_Mark[6]>=100) 	T_Mark[6]=0;

		Data3[0] = 0xaa;	
		CAN_vLoadData(DBO_77,Data3);	 //310-340  8-11   
		CAN_vTransmit(DBO_77);

	//如果超时则清除所有滞留的敏感数据，如速度，转向等
	if(time_out_auto>5) //500ms
		{
			auto_cmd.speed = 0;
			auto_cmd.steering = 0;
			auto_cmd.gear = 2;	
			//remote 
		
		}
	if(time_out_remote>5)
		{
			remote_re.t_steering_vle = 0;
			remote_re.t_throttle_vle = 0;			
		}
		
	delay_time++; //一次20ms
	if(delay_time == 65530)
		delay_time=1000; 
	if(time_hand_break>30000)
		time_hand_break=1000;  //防止溢出
	if(time_auto_hand_break>30000)
		time_auto_hand_break=1000;


  // USER CODE END

} //  End of function GPT2_viTmr6


//****************************************************************************
// @Function      void GPT2_viTmr5(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the GPT2 timer 5. 
//                It is called up in the case of over or underflow of the 
//                timer 5 register.
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

// USER CODE BEGIN (Tmr5,1)

	// 柯默电动 200ms定时器
	// GPT12E_T5=0x0BDC；

// USER CODE END

void GPT2_viTmr5(void) interrupt T5INT
{
  // USER CODE BEGIN (Tmr5,2)

  	T_Mark_i[5]++;	
	if(T_Mark_i[5] >= 5){T_Mark_i[5] = 0; T_Mark[5]++;}
	if(T_Mark[5]>=100) 	T_Mark[5]=0;

  // USER CODE END

} //  End of function GPT2_viTmr5




// USER CODE BEGIN (GPT2_General,10)

// USER CODE END

