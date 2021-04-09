//****************************************************************************
// @Module        Analog / Digital Converter  (ADC0)
// @Filename      ADC0.h
// @Project       tiaoshi.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains all function prototypes and macros for 
//                the ADC0 module.
//
//----------------------------------------------------------------------------
// @Date          2020/1/14 16:27:48
//
//****************************************************************************

// USER CODE BEGIN (ADC0_Header,1)

// USER CODE END


#ifndef _ADC0_H_

#define _ADC0_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (ADC0_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (ADC0_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

//   This parameter identifies ADC0 analog channel 0
#define ADC0_ANA_0 0

//   This parameter identifies ADC0 analog channel 1
#define ADC0_ANA_1 1

//   This parameter identifies ADC0 analog channel 2
#define ADC0_ANA_2 2

//   This parameter identifies ADC0 analog channel 3
#define ADC0_ANA_3 3

//   This parameter identifies ADC0 analog channel 4
#define ADC0_ANA_4 4

//   This parameter identifies ADC0 analog channel 5
#define ADC0_ANA_5 5

//   This parameter identifies ADC0 analog channel 6
#define ADC0_ANA_6 6

//   This parameter identifies ADC0 analog channel 7
#define ADC0_ANA_7 7

//   This parameter identifies ADC0 analog channel 8
#define ADC0_ANA_8 8

//   This parameter identifies ADC0 analog channel 9
#define ADC0_ANA_9 9

//   This parameter identifies ADC0 analog channel 10
#define ADC0_ANA_10 10

//   This parameter identifies ADC0 analog channel 11
#define ADC0_ANA_11 11

//   This parameter identifies ADC0 analog channel 12
#define ADC0_ANA_12 12

//   This parameter identifies ADC0 analog channel 13
#define ADC0_ANA_13 13

//   This parameter identifies ADC0 analog channel 14
#define ADC0_ANA_14 14

//   This parameter identifies ADC0 analog channel 15
#define ADC0_ANA_15 15

//   This parameter identifies ADC0 -Source 0
#define ADC0_SOURCE_0 0

//   This parameter identifies ADC0 -Source 1
#define ADC0_SOURCE_1 1

//   This parameter identifies ADC0 -Source 2
#define ADC0_SOURCE_2 2


// USER CODE BEGIN (ADC0_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************


// USER CODE BEGIN (ADC0_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (ADC0_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (ADC0_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void ADC0_vInit(void);
void ADC0_vStartSeq0ReqChNum(ubyte ubExtTrg, ubyte ubEnIntr, ubyte ubRFill, ubyte ubChannelNum);


// USER CODE BEGIN (ADC0_Header,8)

// USER CODE END


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************


// USER CODE BEGIN (ADC0_Header,9)

// USER CODE END


#endif  // ifndef _ADC0_H_
