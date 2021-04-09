//****************************************************************************
// @Module        Project Settings
// @Filename      MAIN.h
// @Project       tiaoshi.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains all function prototypes and macros for 
//                the MAIN module.
//
//----------------------------------------------------------------------------
// @Date          2020/1/14 16:27:45
//
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,1)

// USER CODE END



#ifndef _MAIN_H_
#define _MAIN_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************
#define KEIL

#define SEG(func) (unsigned int)(((unsigned long)((void (far*)(void))func) >> 16))
#define SOF(func) (unsigned int)(((void (far *) (void))func))

// USER CODE BEGIN (MAIN_Header,4)
#define CS_MC33993_1 P1_OUT_P4
#define CS_MC33993_2 P1_OUT_P3
// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************


void MAIN_vUnlockProtecReg(void);

void MAIN_vLockProtecReg(void);

// USER CODE BEGIN (MAIN_Header,8)

// 柯默电动 此处进行函数声明
void delay(int time); 				//MAIN中定义
void SPI_Control(void);
void Switch_State(void);
void ADC_State(void);
void Switch_Control(void);

// USER CODE END


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,9)

// USER CODE END


//****************************************************************************
// @Project Includes
//****************************************************************************

#include <Intrins.h>

#include  "XC22xxMREGS.H"
#include  "SCS.h"

#include  "IO.h"
#include  "GPT1.h"
#include  "GPT2.h"
#include  "ADC0.h"
#include  "ADC1.h"
#include  "CAN.h"
#include  "USIC0.h"
#include  "USIC1.h"

// USER CODE BEGIN (MAIN_Header,10)

// 柯默电动 此处进行变量全局声明
extern ubyte ST[8];

extern ubyte Data3[8], Data4[8], Data5[8],CAN_Mark[8],CAN_Test[8];
extern ubyte CAN_Break_Timer,CAN_Break_Flag;

extern ubyte CC2_Mark[8],Period_Low[8],Period_High[8];
extern uword Period[8];

extern ubyte ADC_High[8],ADC_Low[8];

extern ubyte T_Mark[8],T_Mark_i[8];


// 柯默电动 此处进行宏定义
#define  SPEED_RATIO  6.43 	//主减速比
#define  PI  3.14	       	//圆周率
#define  WHEEL_R  0.5	   	//车轮半径


// USER CODE END


#endif  // ifndef _MAIN_H_
