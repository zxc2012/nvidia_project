//****************************************************************************
// @Module        Capture / Compare Unit 2 (CAPCOM2)
// @Filename      CC2.c
// @Project       tiaoshi.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the CC2 module.
//
//----------------------------------------------------------------------------
// @Date          2019/10/9 17:37:18
//
//****************************************************************************

// USER CODE BEGIN (CC2_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (CC2_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (CC2_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (CC2_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (CC2_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CC2_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (CC2_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (CC2_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (CC2_General,9)

// USER CODE END


//****************************************************************************
// @Function      void CC2_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the CAPCOM2 function 
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
// @Date          2019/10/9
//
//****************************************************************************

// USER CODE BEGIN (Init,1)

// USER CODE END

void CC2_vInit(void)
{
  // USER CODE BEGIN (Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of  Kernel state configuration Control:
  ///  -----------------------------------------------------------------------
  ///  - the Peripheral is supplied with clock signal for CAPCOM2 unit
  ///  - the CC2 module clock = 80.00 MHz

  CC2_KSCCFG     =  0x0003;      // load CAPCOM2 Kernel state configuration 
                                 // register


  _nop_();  // one cycle delay 

  _nop_();  // one cycle delay 

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAPCOM2 Control:
  ///  -----------------------------------------------------------------------
  ///  - the contents of the CC2_OUT register is visble at output port
  ///  - the contents of the port register is changed by the CAPCOM2 unit

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAPCOM2 Timer 7:
  ///  -----------------------------------------------------------------------
  ///  - timer 7 works in timer mode
  ///  - prescaler factor is 1024
  ///  - timer 7 run bit is set

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAPCOM2 Timer 8:
  ///  -----------------------------------------------------------------------
  ///  - timer 8 works in timer mode
  ///  - prescaler factor is 8
  ///  - timer 8 run bit is reset


  CC2_T78CON     =  0x0007;      // load CAPCOM2 timer 7 and timer 8 control 
                                 // register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Timer Port Pins:
  ///  -----------------------------------------------------------------------


  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Timer Interrupts:
  ///  -----------------------------------------------------------------------


  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 16:
  ///  -----------------------------------------------------------------------
  ///  - capture on negative transition (falling edge) at pin CC16IO (P2.3)
  ///  - CC16 allocated to CAPCOM2 timer 7
  ///  - single event mode is disabled


  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 17:
  ///  -----------------------------------------------------------------------
  ///  - capture on negative transition (falling edge) at pin CC17IO (P2.4)
  ///  - CC17 allocated to CAPCOM2 timer 7
  ///  - single event mode is disabled


  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 18:
  ///  -----------------------------------------------------------------------
  ///  - capture on negative transition (falling edge) at pin CC18IO (P2.5)
  ///  - CC18 allocated to CAPCOM2 timer 7
  ///  - single event mode is disabled


  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 19:
  ///  -----------------------------------------------------------------------
  ///  - capture on negative transition (falling edge) at pin CC19IO (P2.6)
  ///  - CC19 allocated to CAPCOM2 timer 7
  ///  - single event mode is disabled


  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 20:
  ///  -----------------------------------------------------------------------
  ///  - capture on negative transition (falling edge) at pin CC20IO (P2.7)
  ///  - CC20 allocated to CAPCOM2 timer 7
  ///  - single event mode is disabled


  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 21:
  ///  -----------------------------------------------------------------------
  ///  - channel 21 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 22:
  ///  -----------------------------------------------------------------------
  ///  - channel 22 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 23:
  ///  -----------------------------------------------------------------------
  ///  - channel 23 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 24:
  ///  -----------------------------------------------------------------------
  ///  - channel 24 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 25:
  ///  -----------------------------------------------------------------------
  ///  - channel 25 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 26:
  ///  -----------------------------------------------------------------------
  ///  - channel 26 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 27:
  ///  -----------------------------------------------------------------------
  ///  - channel 27 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 28:
  ///  -----------------------------------------------------------------------
  ///  - channel 28 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 29:
  ///  -----------------------------------------------------------------------
  ///  - channel 29 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 30:
  ///  -----------------------------------------------------------------------
  ///  - channel 30 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 31:
  ///  -----------------------------------------------------------------------
  ///  - channel 31 is disabled

  CC2_M4         =  0x2222;      // load CAPCOM2 mode register 4
  CC2_M5         =  0x0002;      // load CAPCOM2 mode register 5

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel Port Pins:
  ///  -----------------------------------------------------------------------
  ///  - P2.3 is used for CAPCOM2 input(CC2_16)
  ///  - P2.4 is used for CAPCOM2 input(CC2_17)
  ///  - P2.5 is used for CAPCOM2 input(CC2_18)
  ///  - P2.6 is used for CAPCOM2 input(CC2_19)
  ///  - P2.7 is used for CAPCOM2 input(CC2_20)


  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channels Interrupts:
  ///  -----------------------------------------------------------------------
  ///  CC16 service request node configuration:
  ///  - CC16 interrupt priority level (ILVL) = 9
  ///  - CC16 interrupt group level (GLVL) = 1
  ///  - CC16 group priority extension (GPX) = 0

  CC2_CC16IC     =  0x0065;     


  ///  CC17 service request node configuration:
  ///  - CC17 interrupt priority level (ILVL) = 8
  ///  - CC17 interrupt group level (GLVL) = 1
  ///  - CC17 group priority extension (GPX) = 0

  CC2_CC17IC     =  0x0061;     


  ///  CC18 service request node configuration:
  ///  - CC18 interrupt priority level (ILVL) = 7
  ///  - CC18 interrupt group level (GLVL) = 1
  ///  - CC18 group priority extension (GPX) = 0

  CC2_CC18IC     =  0x005D;     


  ///  CC19 service request node configuration:
  ///  - CC19 interrupt priority level (ILVL) = 6
  ///  - CC19 interrupt group level (GLVL) = 1
  ///  - CC19 group priority extension (GPX) = 0

  CC2_CC19IC     =  0x0059;     


  ///  CC20 service request node configuration:
  ///  - CC20 interrupt priority level (ILVL) = 5
  ///  - CC20 interrupt group level (GLVL) = 1
  ///  - CC20 group priority extension (GPX) = 0

  CC2_CC20IC     =  0x0055;     



  CC2_T78CON_T7R    = 1;    // set CAPCOM2 timer 7 run bit


  // USER CODE BEGIN (CC20,3)

  // USER CODE END

} //  End of function CC2_viCC20


//****************************************************************************
// @Function      void CC2_viCC16(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the CAPCOM2 
//                register CC16. If the content of the corresponding compare 
//                timer (configurable) equals the content of the 
//                capture/compare register CC16 or if a capture event occurs 
//                at the associated port pin, the interrupt request flag is 
//                set and an interrupt is triggered (only if enabled).
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
// @Date          2019/10/9
//
//****************************************************************************

// USER CODE BEGIN (CC16,1)



// USER CODE END

void CC2_viCC16(void) interrupt CC2_CC16INT
{
  // USER CODE BEGIN (CC16,2)
			  
    //柯默电动 CAPA0 通道16
/*
	uword static previous_CC16,first_timea = 1;

  	if (first_timea == 1)							 
    {
      	previous_CC16 = CC2_CC16;
	  	first_timea = 0;
    }
  	else
    {
	   	Period[0] = (CC2_CC16 - previous_CC16);          			//12.8微秒	  
		Period_High[0]=Period[0] / 256;
		Period_Low[0]=Period[0] % 256; 	 
	   	previous_CC16 = CC2_CC16;
		CC2_Mark[0] = 1;
	}
*/
	CC2_Mark[0]++;

  // USER CODE END

} //  End of function CC2_viCC16


//****************************************************************************
// @Function      void CC2_viCC17(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the CAPCOM2 
//                register CC17. If the content of the corresponding compare 
//                timer (configurable) equals the content of the 
//                capture/compare register CC17 or if a capture event occurs 
//                at the associated port pin, the interrupt request flag is 
//                set and an interrupt is triggered (only if enabled).
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
// @Date          2019/10/9
//
//****************************************************************************

// USER CODE BEGIN (CC17,1)

// USER CODE END

void CC2_viCC17(void) interrupt CC2_CC17INT
{
  // USER CODE BEGIN (CC17,2)

	//柯默电动 CAPA1 通道17
	uword static previous_CC17,first_timeb = 1;

  	if (first_timeb == 1)							 
    {
      	previous_CC17 = CC2_CC17;
	  	first_timeb = 0;
    }
  	else
    {
	   	Period[1] = (CC2_CC17 - previous_CC17);	   					//12.8微秒
		Period_High[1]=Period[1] / 256;
		Period_Low[1]=Period[1] % 256; 	 
	   	previous_CC17 = CC2_CC17;
		CC2_Mark[1] = 1;
	}

	//CC2_Mark[1]++;

  // USER CODE END

} //  End of function CC2_viCC17


//****************************************************************************
// @Function      void CC2_viCC18(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the CAPCOM2 
//                register CC18. If the content of the corresponding compare 
//                timer (configurable) equals the content of the 
//                capture/compare register CC18 or if a capture event occurs 
//                at the associated port pin, the interrupt request flag is 
//                set and an interrupt is triggered (only if enabled).
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
// @Date          2019/10/9
//
//****************************************************************************

// USER CODE BEGIN (CC18,1)

// USER CODE END

void CC2_viCC18(void) interrupt CC2_CC18INT
{
  // USER CODE BEGIN (CC18,2)

	//柯默电动 CAPA2 通道18
	uword static previous_CC18,first_timec = 1;

  	if (first_timec == 1)							 
    {
      	previous_CC18 = CC2_CC18;
	  	first_timec = 0;
    }
  	else
    {
	   	Period[2] = (CC2_CC18 - previous_CC18);						//12.8微秒
		Period_High[2]=Period[2] / 256;
		Period_Low[2]=Period[2] % 256;    	 
	   	previous_CC18 = CC2_CC18;
		CC2_Mark[2]=1;
	}

	//CC2_Mark[2]++;

  // USER CODE END

} //  End of function CC2_viCC18


//****************************************************************************
// @Function      void CC2_viCC19(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the CAPCOM2 
//                register CC19. If the content of the corresponding compare 
//                timer (configurable) equals the content of the 
//                capture/compare register CC19 or if a capture event occurs 
//                at the associated port pin, the interrupt request flag is 
//                set and an interrupt is triggered (only if enabled).
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
// @Date          2019/10/9
//
//****************************************************************************

// USER CODE BEGIN (CC19,1)

// USER CODE END

void CC2_viCC19(void) interrupt CC2_CC19INT
{
  // USER CODE BEGIN (CC19,2)

	//柯默电动 CAPA3 通道19
	uword static previous_CC19,first_timed = 1;

  	if (first_timed == 1)							 
    {
      	previous_CC19 = CC2_CC19;
	  	first_timed = 0;
    }
  	else
    {
	   	Period[3] = (CC2_CC19 - previous_CC19);						//12.8微秒
		Period_High[3]=Period[3] / 256;
		Period_Low[3]=Period[3] % 256; 	   	 
	   	previous_CC19 = CC2_CC19;
		CC2_Mark[3]=1;
	}

	//CC2_Mark[3]++;

  // USER CODE END

} //  End of function CC2_viCC19


//****************************************************************************
// @Function      void CC2_viCC20(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the CAPCOM2 
//                register CC20. If the content of the corresponding compare 
//                timer (configurable) equals the content of the 
//                capture/compare register CC20 or if a capture event occurs 
//                at the associated port pin, the interrupt request flag is 
//                set and an interrupt is triggered (only if enabled).
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
// @Date          2019/10/9
//
//****************************************************************************

// USER CODE BEGIN (CC20,1)

// USER CODE END

void CC2_viCC20(void) interrupt CC2_CC20INT
{
  // USER CODE BEGIN (CC20,2)

//柯默电动 CAPA3 通道19
	uword static previous_CC20,first_timee = 1;

  	if (first_timee == 1)							 
    {
      	previous_CC20 = CC2_CC20;
	  	first_timee = 0;
    }
  	else
    {
	   	Period[4] = (CC2_CC20 - previous_CC20);						//12.8微秒
		Period_High[4]=Period[4] / 256;
		Period_Low[4]=Period[4] % 256; 	   	 
	   	previous_CC20 = CC2_CC20;
		CC2_Mark[4]=1;
	}

	//CC2_Mark[4]++;

  // USER CODE END

} //  End of function CC2_viCC20




// USER CODE BEGIN (CC2_General,10)

// USER CODE END

