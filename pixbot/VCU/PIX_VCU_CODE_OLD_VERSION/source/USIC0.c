//****************************************************************************
// @Module        USIC0
// @Filename      USIC0.c
// @Project       tiaoshi.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the USIC0 module.
//
//----------------------------------------------------------------------------
// @Date          2020/1/14 16:27:47
//
//****************************************************************************

// USER CODE BEGIN (USIC0_General,1)

// USER CODE END

//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (USIC0_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (USIC0_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (USIC0_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (USIC0_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (USIC0_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (USIC0_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (USIC0_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (USIC0_General,9)

// USER CODE END


//****************************************************************************
// @Function      void USIC0_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This function initializes USIC0 Module
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

void USIC0_vInit(void)
{
  // USER CODE BEGIN (Init,2)

  // USER CODE END

  //   -----------------------------------------------------------------------
  //   Initialization of USIC Peripherals:
  //   -----------------------------------------------------------------------

  ///  - USIC0 module clock = 80.00 MHz

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C0 Kernel State Configuration:
  ///  -----------------------------------------------------------------------

  U0C0_KSCFG     =  0x0003;      // load U0C0 kernel state configuration 
                                 // register

  _nop_();  // one cycle delay 

  _nop_();  // one cycle delay 

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C0 Channel Control Register (Mode & Interrupts):
  ///  -----------------------------------------------------------------------
  /// - The USIC channel is disabled
  /// - The parity generation is disabled

  U0C0_CCR       =  0x0000;      // load U0C0 channel control register

  //   initializes the Universal Serial Interface Channel (USIC) U0C0

  U0C0_IIC_vInit();

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C0 Channel Control Register (Mode & Interrupts):
  ///  -----------------------------------------------------------------------
  ///  - IIC protocol is selected 
  ///  - The parity generation is disabled

  U0C0_CCR       =  0x0004;      // load U0C0 channel control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C1 Kernel State Configuration:
  ///  -----------------------------------------------------------------------

  U0C1_KSCFG     =  0x0003;      // load U0C1 kernel state configuration 
                                 // register

  _nop_();  // one cycle delay 

  _nop_();  // one cycle delay 

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C1 Channel Control Register (Mode & Interrupts):
  ///  -----------------------------------------------------------------------
  /// - The USIC channel is disabled
  /// - The parity generation is disabled

  U0C1_CCR       =  0x0000;      // load U0C0 channel control register

  //   initializes the Universal Serial Interface Channel (USIC) U0C1

  U0C1_IIC_vInit();

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C1 Channel Control Register (Mode & Interrupts):
  ///  -----------------------------------------------------------------------
  ///  - IIC protocol is selected 
  ///  - The parity generation is disabled

  U0C1_CCR       =  0x0004;      // load U0C1 channel control register


  // USER CODE BEGIN (Init,3)

  // USER CODE END

} //  End of function USIC0_vInit




// USER CODE BEGIN (USIC0_General,10)

// USER CODE END

