//****************************************************************************
// @Module        Analog / Digital Converter (ADC1)
// @Filename      ADC1.h
// @Project       tiaoshi.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains all function prototypes and macros for 
//                the ADC1 module.
//
//----------------------------------------------------------------------------
// @Date          2020/1/14 16:27:48
//
//****************************************************************************

// USER CODE BEGIN (ADC1_Header,1)

// USER CODE END


#ifndef _ADC1_H_

#define _ADC1_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (ADC1_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (ADC1_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

//   This parameter identifies ADC1 analog channel 0
#define ADC1_ANA_0 0

//   This parameter identifies ADC1 analog channel 1
#define ADC1_ANA_1 1

//   This parameter identifies ADC1 analog channel 2
#define ADC1_ANA_2 2

//   This parameter identifies ADC1 analog channel 3
#define ADC1_ANA_3 3

//   This parameter identifies ADC1 analog channel 4
#define ADC1_ANA_4 4

//   This parameter identifies ADC1 analog channel 5
#define ADC1_ANA_5 5

//   This parameter identifies ADC1 analog channel 6
#define ADC1_ANA_6 6

//   This parameter identifies ADC1 analog channel 7
#define ADC1_ANA_7 7

//   This parameter identifies ADC1 -Source 0
#define ADC1_SOURCE_0 0

//   This parameter identifies ADC1 -Source 1
#define ADC1_SOURCE_1 1

//   This parameter identifies ADC1 -Source 2
#define ADC1_SOURCE_2 2


// USER CODE BEGIN (ADC1_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************


// USER CODE BEGIN (ADC1_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (ADC1_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (ADC1_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void ADC1_vInit(void);
void ADC1_vStartSeq0ReqChNum(ubyte ubExtTrg, ubyte ubEnIntr, ubyte ubRFill, ubyte ubChannelNum);


// USER CODE BEGIN (ADC1_Header,8)

// USER CODE END


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************


// USER CODE BEGIN (ADC1_Header,9)

// USER CODE END


#endif  // ifndef _ADC1_H_
