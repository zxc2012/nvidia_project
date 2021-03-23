//****************************************************************************
// @Module        USIC1
// @Filename      USIC1.c
// @Project       tiaoshi.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the USIC1 module.
//
//----------------------------------------------------------------------------
// @Date          2020/1/14 16:27:48
//
//****************************************************************************

// USER CODE BEGIN (USIC1_General,1)

// USER CODE END

//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (USIC1_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (USIC1_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (USIC1_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (USIC1_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (USIC1_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (USIC1_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (USIC1_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (USIC1_General,9)

// USER CODE END


//****************************************************************************
// @Function      void USIC1_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This function initializes USIC1 Module
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

void USIC1_vInit(void)
{
  // USER CODE BEGIN (Init,2)

  // USER CODE END

  //   -----------------------------------------------------------------------
  //   Initialization of USIC Peripherals:
  //   -----------------------------------------------------------------------

  ///  - USIC1 module clock = 80.00 MHz

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U1C0 Kernel State Configuration:
  ///  -----------------------------------------------------------------------

  U1C0_KSCFG     =  0x0003;      // load U1C0 kernel state configuration 
                                 // register

  _nop_();  // one cycle delay 

  _nop_();  // one cycle delay 

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U1C0 Channel Control Register (Mode & Interrupts):
  ///  -----------------------------------------------------------------------
  /// - The USIC channel is disabled
  /// - The parity generation is disabled

  U1C0_CCR       =  0x0000;      // load U0C0 channel control register

  //   initializes the Universal Serial Interface Channel (USIC) U1C0

  U1C0_SSC_vInit();

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U1C0 Channel Control Register (Mode & Interrupts):
  ///  -----------------------------------------------------------------------
  ///  - SSC (SPI) Protocol is selected 
  ///  - The parity generation is disabled

  U1C0_CCR       =  0x0001;      // load U1C0 channel control register


  // USER CODE BEGIN (Init,3)

  // USER CODE END

} //  End of function USIC1_vInit




// USER CODE BEGIN (USIC1_General,10)

// USER CODE END

