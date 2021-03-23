//****************************************************************************
// @Module        Universal Serial Interface Channel (USIC) U2C0
// @Filename      U2C0.c
// @Project       tiaoshi.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.1
//
// @Description   This file contains functions that use the U2C0 module.
//
//----------------------------------------------------------------------------
// @Date          2015/3/16 12:47:13
//
//****************************************************************************

// USER CODE BEGIN (U2C0_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (U2C0_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (U2C0_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (U2C0_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (U2C0_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (U2C0_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (U2C0_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (U2C0_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (U2C0_General,9)

// USER CODE END


//****************************************************************************
// @Function      void U2C0_SSC_vInit(void)
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the U2C0 function
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
// @Date          2015/3/16
//
//****************************************************************************

// USER CODE BEGIN (Init,1)

// USER CODE END

void U2C0_SSC_vInit(void)
{
  // USER CODE BEGIN (Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U2C0 Fractional Divider:
  ///  -----------------------------------------------------------------------
  ///  - The Normal divider is selected
  ///  - The step value STEP = 1022

  U2C0_FDRL      =  0x43FE;      // load U2C0 fractional divider register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U2C0 Baudrate Generator:
  ///  -----------------------------------------------------------------------
  ///  - The selected BaudRate is 500.000 kbaud
  ///  - The PreDivider for CTQ, PCTQ = 0
  ///  - The Denominator for CTQ, DCTQ = 0
  ///  - The Divider factor PDIV = 39

  U2C0_BRGL      =  0x0000;      // load U2C0 load baud rate generator 
                                 // register L

  U2C0_BRGH      =  0x0027;      // load U2C0 load baud rate generator 
                                 // register H

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U2C0 Input Control Register:
  ///  -----------------------------------------------------------------------
  ///  - The data input DX0C is selected

  U2C0_DX0CR     =  0x0012;      // load U2C0 input control register(Data)

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U2C0 Interrupt Node Pointer Register:
  ///  -----------------------------------------------------------------------

  U2C0_INPRL     =  0x0000;      // load U2C0 Interrupt Node Pointer register 
                                 // L
  U2C0_INPRH     =  0x0000;      // load U2C0 Interrupt Node Pointer register 
                                 // H

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U2C0 Shift Control:
  ///  -----------------------------------------------------------------------
  ///  - Transmit/Receive MSB first is selected

  U2C0_SCTRL     =  0x0103;      // load U2C0 shift control register L
  U2C0_SCTRH     =  0x0707;      // load U2C0 shift control register H

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U2C0 Transmit Control/Status Register:
  ///  -----------------------------------------------------------------------

  U2C0_TCSRL     =  0x0500;      // load U2C0 transmit control/status 
                                 // register L
  U2C0_TCSRH     =  0x0000;      // load U2C0 transmit control/status 
                                 // register H

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U2C0 Protocol Control Register:
  ///  -----------------------------------------------------------------------

  U2C0_PCRL      =  0x0F47;      // load U2C0 protocol control register L
  U2C0_PCRH      =  0x0000;      // load U2C0 protocol control register H

  ///  -----------------------------------------------------------------------
  ///  Configuration of the U2C0 Protocol Status Register:
  ///  -----------------------------------------------------------------------
  ///  - TBIF is set to simplify polling

  U2C0_PSR      |=  0x2000;      // load U2C0 protocol status register


  ///  -----------------------------------------------------------------------
  ///  Configuration of the used U2C0 Interrupts:
  ///  -----------------------------------------------------------------------

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used U2C0 Port Pins:
  ///  -----------------------------------------------------------------------
  P1_IOCR05      =  0x0020;      // load port register for data input

  ///  - P1.6 is used for USIC2 Channel0 Shift Data output(DOUT)
  ///  - P1.7 is used for USIC2 Channel0 Shift Clock Output(SCLKOUT)

  P1_IOCR06 = 0x00B0;    //set direction register
  P1_IOCR07 = 0x00B0;    //set direction register


  ///  -----------------------------------------------------------------------
  ///  Configuration of U2C0 FIFO:
  ///  -----------------------------------------------------------------------
  ///  -----------------------------------------------------------------------
  ///  Configuration of U2C0 Transmitter Buffer Conrol Register:
  ///  -----------------------------------------------------------------------
  ///  - Transmit FIFO buffer is disabled
  ///  -----------------------------------------------------------------------
  ///  Configuration of U2C0 Receiver Buffer Conrol Register:
  ///  -----------------------------------------------------------------------
  ///  - Receive FIFO buffer is disabled

  // USER CODE BEGIN (U2C0_Function,3)

  // USER CODE END



} //  End of function U2C0_SSC_vInit


//****************************************************************************
// @Function      void U2C0_SSC_vSendData(uword uwData) 
//
//----------------------------------------------------------------------------
// @Description   This function clears the transmit buffer Indication flag 
//                first  & then writes the send data initialization word into 
//                the transmit buffer register.
//                
//                Note: 
//                In a multiprocessor system the master with this function 
//                has the possibility to send data to the selected slave.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    uwData: 
//                Data to be send
//
//----------------------------------------------------------------------------
// @Date          2015/3/16
//
//****************************************************************************

// USER CODE BEGIN (SSCSendData,1)

// USER CODE END

void U2C0_SSC_vSendData(uword uwData)
{

  while(!(U2C0_PSR & 0x2000));   //  wait until tx buffer indication flag is set

  U2C0_PSCR     |= 0x2000;   //  clear transmit buffer indication flag
  U2C0_TBUF00    = uwData;   //  load transmit buffer register

} //  End of function U2C0_SSC_vSendData


//****************************************************************************
// @Function      uword U2C0_SSC_uwGetData(void) 
//
//----------------------------------------------------------------------------
// @Description   This function reads out the content of the receive buffer 
//                register which contains the received data.
//
//----------------------------------------------------------------------------
// @Returnvalue   Data that has been received
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2015/3/16
//
//****************************************************************************

// USER CODE BEGIN (SSCGetData,1)

// USER CODE END

uword U2C0_SSC_uwGetData(void)
{
  while(!((U2C0_PSR & 0x8000) || (U2C0_PSR & 0x4000)));

  U2C0_PSCR     |= 0xC000;   //  clear alternate receive indication flag & receive indication flag
  return(U2C0_RBUF);         // return receive buffer register


} //  End of function U2C0_SSC_uwGetData


//****************************************************************************
// @Function      ubyte U2C0_SSC_ubTxDataReady(void) 
//
//----------------------------------------------------------------------------
// @Description   This function can be used for checking up the status of the 
//                transmit shift indication flag U2C0_PSR_TSIF. This function 
//                shows when the sending of data has terminated. By 
//                continuously polling this flag after the function 
//                U2C0_SSC_vSendData has been called, it is possible to 
//                establish when U2C0 has terminated its task.
//
//----------------------------------------------------------------------------
// @Returnvalue   0 if transmitter is busy, else 1
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2015/3/16
//
//****************************************************************************

// USER CODE BEGIN (SSCTxDataReady,1)

// USER CODE END

ubyte U2C0_SSC_ubTxDataReady(void)
{
  ubyte ubReturnValue;

  ubReturnValue = 0;

  if(U2C0_PSR & 0x1000)               // if sending of data is terminated
  {
    ubReturnValue = 1;
    U2C0_PSCR |= 0x1000;
  }
  return(ubReturnValue);         

} //  End of function U2C0_SSC_ubTxDataReady




// USER CODE BEGIN (U2C0_General,10)

// USER CODE END

