//****************************************************************************
// @Module        Universal Serial Interface Channel (USIC) U0C1
// @Filename      U0C1.c
// @Project       tiaoshi.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the U0C1 module.
//
//----------------------------------------------------------------------------
// @Date          2020/1/14 16:27:47
//
//****************************************************************************

// USER CODE BEGIN (U0C1_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (U0C1_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (U0C1_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (U0C1_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (U0C1_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (U0C1_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (U0C1_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (U0C1_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (U0C1_General,9)

// USER CODE END


//****************************************************************************
// @Function      void U0C1_IIC_vInit(void)
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the U0C1 function
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

void U0C1_IIC_vInit(void)
{
  // USER CODE BEGIN (Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C1 Operation Mode:
  ///  -----------------------------------------------------------------------
  ///  - The Master mode is selected

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C1 Fractional Divider:
  ///  -----------------------------------------------------------------------
  ///  - The Fractional divider is selected
  ///  - The step value STEP = 640

  U0C1_FDRL      =  0x8280;      // load U0C1 fractional divider register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C1 Baudrate Generator:
  ///  -----------------------------------------------------------------------
  ///  - The selected BaudRate is 100.000 kbaud
  ///  - The PreDivider for CTQ, PCTQ = 1
  ///  - The Denominator for CTQ, DCTQ = 9
  ///  - The Divider factor PDIV = 24

  U0C1_BRGL      =  0x2500;      // load U0C1 load baud rate generator 
                                 // register L
  U0C1_BRGH      =  0x0018;      // load U0C1 load baud rate generator 
                                 // register H

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C1 Input Control Register:
  ///  -----------------------------------------------------------------------
  ///  - The data input DX0A (P10.0) is selected

  U0C1_DX0CR     =  0x0000;      // load U0C1 input control register(Data)

  ///  - The clock input DX1B (P10.5) is selected

  U0C1_DX1CR     =  0x0001;      // load U0C1 input control register(Clock)

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C1 Interrupt Node Pointer Register:
  ///  -----------------------------------------------------------------------

  U0C1_INPRL     =  0x0000;      // load U0C1 Interrupt Node Pointer register 
                                 // L
  U0C1_INPRH     =  0x0000;      // load U0C1 Interrupt Node Pointer register 
                                 // H

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C1 Shift Control:
  ///  -----------------------------------------------------------------------
  ///  - Transmit/Receive shift MSB first
  ///  - The passive data level is 1
  ///  - The shift control signal is active, data frame transfer is possible
  ///  - The frame length is 63 and the word length is 7

  U0C1_SCTRL     =  0x0303;      // load U0C1 shift control register L
  U0C1_SCTRH     =  0x073F;      // load U0C1 shift control register H

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C1 Transmit Control/Status Register:
  ///  -----------------------------------------------------------------------
  ///  - TBUF data single shot mode: TBUF data transferred only once
  ///  - TBUF data transmission starts if TDV = 1

  U0C1_TCSRL     =  0x0500;      // load U0C1 transmit control/status 
                                 // register L
  U0C1_TCSRH     =  0x0000;      // load U0C1 transmit control/status 
                                 // register H

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C1 Protocol Control Register:
  ///  -----------------------------------------------------------------------
  ///  - The Symbol Timing, A symbol contains 10 time quanta

  U0C1_PCRL      =  0x0000;      // load U0C1 protocol control register L
  U0C1_PCRH      =  0x3000;      // load U0C1 protocol control register H

  ///  -----------------------------------------------------------------------
  ///  Configuration of U0C1 FIFO:
  ///  -----------------------------------------------------------------------
  ///  -----------------------------------------------------------------------
  ///  Configuration of U0C1 Transmitter Buffer Conrol Register:
  ///  -----------------------------------------------------------------------
  ///  - Transmit FIFO buffer is disabled
  ///  -----------------------------------------------------------------------
  ///  Configuration of U0C1 Receiver Buffer Conrol Register:
  ///  -----------------------------------------------------------------------
  ///  - Receive FIFO buffer is disabled
  ///  -----------------------------------------------------------------------
  ///  Configuration of the used U0C1 Interrupts:
  ///  -----------------------------------------------------------------------
  ///  -----------------------------------------------------------------------
  ///  Configuration of the used U0C1 Port Pins:
  ///  -----------------------------------------------------------------------
  ///  - P10.0 is used for USIC0 Channel1 Shift Data output(DOUT)
  ///  - P10.5 is used for USIC0 Channel0 Shift Clock output(SCLKOUT)

  P10_IOCR00 = 0x00D0;    //set direction register
  P10_IOCR05 = 0x00D0;    //set direction register



  // USER CODE BEGIN (U0C1_Function,3)

  // USER CODE END



} //  End of function U0C1_IIC_vInit


//****************************************************************************
// @Function      void U0C1_IIC_vWriteData(uword uwTDF, uword uwData) 
//
//----------------------------------------------------------------------------
// @Description   This function writes data to the U0C1 Transmit buffer 
//                (U0C1_TBUF00). valid TDF & 8 bit data.
//                The valid TDF formats are available in U0C1 header file
//                Defines section. Ex..
//                 Master start                  U0C1TDF_MStart
//                 Master Transmit               U0C1TDF_MTxData
//                 Master receive with Ack 0     U0C1TDF_MRxAck0
//                 Master receive with Ack 1     U0C1TDF_MRxAck1
//                 Master stop                   U0C1TDF_MStop
//                
//                7 bit address mode:
//                if 7 bit slave address is 0x17 at PCRL[15:9] of the slave,
//                user has to transmit 0x2E (0x17 << 1) to select this slave.
//                Please refer User Manual for the detailed explanation.
//                
//                User can use the macro U0C1_IIC_vSlaveAddrFormat(Addr)
//                to left shift the address by 1,
//                U0C1_IIC_vWriteData(U0C1TDF_MStart, 
//                U0C1_IIC_vSlaveAddrFormat(Addr) + U0C1IIC_WRITE);
//                
//                10 bit address mode:
//                if 10 bit slave address is 0x1C4 at PCRL[10:9] & PCRL[7:0]
//                of the slave, user has to transmit 0xF2 first and 
//                0xC4 second to select this slave.
//                
//                U0C1_IIC_vWriteData(U0C1TDF_MStart, uwDeviceAddr + 
//                U0C1IIC_WRITE);
//                U0C1_IIC_vWriteData(U0C1TDF_MTxData, uwSubAddr);
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    uwTDF: 
//                valid Transmit Data Format TDF code
// @Parameters    uwData: 
//                8 bit data to be transmitted
//
//----------------------------------------------------------------------------
// @Date          2020/1/14
//
//****************************************************************************

// USER CODE BEGIN (IICWriteData,1)

// USER CODE END

void U0C1_IIC_vWriteData(uword uwTDF, uword uwData)
{

  while(U0C1_TCSRL & 0x0080);             // check TDV, wait until TBUF is ready

  U0C1_PSCR   |= 0x2000;                                       // clear PSR_TBIF
  U0C1_TBUF00  = ((uwTDF << 8) & 0x0700) | (uwData & 0x00FF);  // load TBUF00

} //  End of function U0C1_IIC_vWriteData


//****************************************************************************
// @Function      uword U0C1_IIC_uwReadData(void) 
//
//----------------------------------------------------------------------------
// @Description   This function reads out the content of the U0C1 receive 
//                buffer (U0C1_RBUF).
//
//----------------------------------------------------------------------------
// @Returnvalue   Value of the register U0C1_RBUF
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2020/1/14
//
//****************************************************************************

// USER CODE BEGIN (IICReadData,1)

// USER CODE END

uword U0C1_IIC_uwReadData(void)
{

  while(!((U0C1_PSR & 0x8000) || (U0C1_PSR & 0x4000)));

  U0C1_PSCR   |= 0xC000;         // clear PSR_AIF & PSR_RIF
  return(U0C1_RBUF);             // return receive buffer register

} //  End of function U0C1_IIC_uwReadData




// USER CODE BEGIN (U0C1_General,10)

// USER CODE END

