//****************************************************************************
// @Module        Universal Serial Interface Channel (USIC) U0C0
// @Filename      U0C0.c
// @Project       tiaoshi.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the U0C0 module.
//
//----------------------------------------------------------------------------
// @Date          2020/1/14 16:27:47
//
//****************************************************************************

// USER CODE BEGIN (U0C0_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (U0C0_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (U0C0_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (U0C0_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (U0C0_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (U0C0_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (U0C0_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (U0C0_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (U0C0_General,9)



// USER CODE END


//****************************************************************************
// @Function      void U0C0_IIC_vInit(void)
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the U0C0 function
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

void U0C0_IIC_vInit(void)
{
  // USER CODE BEGIN (Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C0 Operation Mode:
  ///  -----------------------------------------------------------------------
  ///  - The Master mode is selected

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C0 Fractional Divider:
  ///  -----------------------------------------------------------------------
  ///  - The Fractional divider is selected
  ///  - The step value STEP = 640

  U0C0_FDRL      =  0x8280;      // load U0C0 fractional divider register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C0 Baudrate Generator:
  ///  -----------------------------------------------------------------------
  ///  - The selected BaudRate is 100.000 kbaud
  ///  - The PreDivider for CTQ, PCTQ = 1
  ///  - The Denominator for CTQ, DCTQ = 9
  ///  - The Divider factor PDIV = 24

  U0C0_BRGL      =  0x2500;      // load U0C0 load baud rate generator 
                                 // register L
  U0C0_BRGH      =  0x0018;      // load U0C0 load baud rate generator 
                                 // register H

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C0 Input Control Register:
  ///  -----------------------------------------------------------------------
  ///  - The data input DX0B (P10.1) is selected

  U0C0_DX0CR     =  0x0001;      // load U0C0 input control register(Data)

  ///  - The clock input DX1B (P10.2) is selected

  U0C0_DX1CR     =  0x0001;      // load U0C0 input control register(Clock)

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C0 Interrupt Node Pointer Register:
  ///  -----------------------------------------------------------------------

  U0C0_INPRL     =  0x0000;      // load U0C0 Interrupt Node Pointer register 
                                 // L
  U0C0_INPRH     =  0x0000;      // load U0C0 Interrupt Node Pointer register 
                                 // H

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C0 Shift Control:
  ///  -----------------------------------------------------------------------
  ///  - Transmit/Receive shift MSB first
  ///  - The passive data level is 1
  ///  - The shift control signal is active, data frame transfer is possible
  ///  - The frame length is 63 and the word length is 7

  U0C0_SCTRL     =  0x0303;      // load U0C0 shift control register L
  U0C0_SCTRH     =  0x073F;      // load U0C0 shift control register H

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C0 Transmit Control/Status Register:
  ///  -----------------------------------------------------------------------
  ///  - TBUF data single shot mode: TBUF data transferred only once
  ///  - TBUF data transmission starts if TDV = 1

  U0C0_TCSRL     =  0x0500;      // load U0C0 transmit control/status 
                                 // register L
  U0C0_TCSRH     =  0x0000;      // load U0C0 transmit control/status 
                                 // register H

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U0C0 Protocol Control Register:
  ///  -----------------------------------------------------------------------
  ///  - The Symbol Timing, A symbol contains 10 time quanta

  U0C0_PCRL      =  0x0000;      // load U0C0 protocol control register L
  U0C0_PCRH      =  0x3000;      // load U0C0 protocol control register H

  ///  -----------------------------------------------------------------------
  ///  Configuration of U0C0 FIFO:
  ///  -----------------------------------------------------------------------
  ///  -----------------------------------------------------------------------
  ///  Configuration of U0C0 Transmitter Buffer Conrol Register:
  ///  -----------------------------------------------------------------------
  ///  - Transmit FIFO buffer is disabled
  ///  -----------------------------------------------------------------------
  ///  Configuration of U0C0 Receiver Buffer Conrol Register:
  ///  -----------------------------------------------------------------------
  ///  - Receive FIFO buffer is disabled
  ///  -----------------------------------------------------------------------
  ///  Configuration of the used U0C0 Interrupts:
  ///  -----------------------------------------------------------------------
  ///  -----------------------------------------------------------------------
  ///  Configuration of the used U0C0 Port Pins:
  ///  -----------------------------------------------------------------------
  ///  - P10.1 is used for USIC0 Channel0 Shift Data output(DOUT)
  ///  - P10.2 is used for USIC0 Channel0 Shift Clock output(SCLKOUT)

  P10_IOCR01 = 0x00D0;    //set direction register
  P10_IOCR02 = 0x00D0;    //set direction register



  // USER CODE BEGIN (U0C0_Function,3)

  // USER CODE END



} //  End of function U0C0_IIC_vInit


//****************************************************************************
// @Function      void U0C0_IIC_vWriteData(uword uwTDF, uword uwData) 
//
//----------------------------------------------------------------------------
// @Description   This function writes data to the U0C0 Transmit buffer 
//                (U0C0_TBUF00). valid TDF & 8 bit data.
//                The valid TDF formats are available in U0C0 header file
//                Defines section. Ex..
//                 Master start                  U0C0TDF_MStart
//                 Master Transmit               U0C0TDF_MTxData
//                 Master receive with Ack 0     U0C0TDF_MRxAck0
//                 Master receive with Ack 1     U0C0TDF_MRxAck1
//                 Master stop                   U0C0TDF_MStop
//                
//                7 bit address mode:
//                if 7 bit slave address is 0x17 at PCRL[15:9] of the slave,
//                user has to transmit 0x2E (0x17 << 1) to select this slave.
//                Please refer User Manual for the detailed explanation.
//                
//                User can use the macro U0C0_IIC_vSlaveAddrFormat(Addr)
//                to left shift the address by 1,
//                U0C0_IIC_vWriteData(U0C0TDF_MStart, 
//                U0C0_IIC_vSlaveAddrFormat(Addr) + U0C0IIC_WRITE);
//                
//                10 bit address mode:
//                if 10 bit slave address is 0x1C4 at PCRL[10:9] & PCRL[7:0]
//                of the slave, user has to transmit 0xF2 first and 
//                0xC4 second to select this slave.
//                
//                U0C0_IIC_vWriteData(U0C0TDF_MStart, uwDeviceAddr + 
//                U0C0IIC_WRITE);
//                U0C0_IIC_vWriteData(U0C0TDF_MTxData, uwSubAddr);
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
	 unsigned int O = 0;
// USER CODE END

void U0C0_IIC_vWriteData(uword uwTDF, uword uwData)
{

  while(U0C0_TCSRL & 0x0080);             // check TDV, wait until TBUF is ready

  U0C0_PSCR   |= 0x2000;                                       // clear PSR_TBIF
  U0C0_TBUF00  = ((uwTDF << 8) & 0x0700) | (uwData & 0x00FF);  // load TBUF00

} //  End of function U0C0_IIC_vWriteData


//****************************************************************************
// @Function      uword U0C0_IIC_uwReadData(void) 
//
//----------------------------------------------------------------------------
// @Description   This function reads out the content of the U0C0 receive 
//                buffer (U0C0_RBUF).
//
//----------------------------------------------------------------------------
// @Returnvalue   Value of the register U0C0_RBUF
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

uword U0C0_IIC_uwReadData(void)
{

  while(!((U0C0_PSR & 0x8000) || (U0C0_PSR & 0x4000)));

  U0C0_PSCR   |= 0xC000;         // clear PSR_AIF & PSR_RIF
  return(U0C0_RBUF);             // return receive buffer register

} //  End of function U0C0_IIC_uwReadData




// USER CODE BEGIN (U0C0_General,10)

// USER CODE END

