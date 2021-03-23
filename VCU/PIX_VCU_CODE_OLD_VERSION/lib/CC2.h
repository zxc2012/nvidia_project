//****************************************************************************
// @Module        Capture / Compare Unit 2 (CAPCOM2)
// @Filename      CC2.h
// @Project       tiaoshi.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains all function prototypes and macros for 
//                the CC2 module.
//
//----------------------------------------------------------------------------
// @Date          2019/10/9 17:37:18
//
//****************************************************************************

// USER CODE BEGIN (CC2_Header,1)

// USER CODE END



#ifndef _CC2_H_
#define _CC2_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (CC2_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (CC2_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

//   This parameter identifies CAPCOM2 timer 7
#define CC2_TIMER_7 7

//   This parameter identifies CAPCOM2 timer 8
#define CC2_TIMER_8 8

//   This parameter identifies CAPCOM2 channel 16
#define CC2_CC_16 16

//   This parameter identifies CAPCOM2 channel 17
#define CC2_CC_17 17

//   This parameter identifies CAPCOM2 channel 18
#define CC2_CC_18 18

//   This parameter identifies CAPCOM2 channel 19
#define CC2_CC_19 19

//   This parameter identifies CAPCOM2 channel 20
#define CC2_CC_20 20


// USER CODE BEGIN (CC2_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (CC2_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CC2_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (CC2_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void CC2_vInit(void);


// USER CODE BEGIN (CC2_Header,8)

// USER CODE END


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

#define CC2_CC16INT    0x10
#define CC2_CC17INT    0x11
#define CC2_CC18INT    0x12
#define CC2_CC19INT    0x13
#define CC2_CC20INT    0x14


// USER CODE BEGIN (CC2_Header,8)

// USER CODE END


#endif  // ifndef _CC2_H_
