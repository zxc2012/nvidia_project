//****************************************************************************
// @Module        MultiCAN Module (CAN)
// @Filename      CAN.c
// @Project       tiaoshi.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the CAN module.
//
//----------------------------------------------------------------------------
// @Date          2020/1/14 16:27:48
//
//****************************************************************************



// USER CODE BEGIN (CAN_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (CAN_General,2)
#include "remote.h"
#include "steering.h"
#include "vehicle_control.h"
#include "breaking_control.h"

#define DEBUG TRUE
// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (CAN_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (CAN_General,4)
 	 
// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (CAN_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CAN_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************


// USER CODE BEGIN (CAN_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (CAN_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (CAN_General,9)

// USER CODE END


//****************************************************************************
// @Function      void CAN_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the CAN function 
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

void CAN_vInit(void)
{

  // USER CODE BEGIN (Init,2)
  
  
  // 柯默电动 此处注释CAN消息
  // 	Node0	 					Node1					Node2     
  // Mo (ID 181 发送) 		M1 (ID 183 发送)  			 M2 (ID 184 发送)
  // M3 (ID 182 接收)  		M4 (ID 185 接收) 			 M5 (ID 183 接收)
  	  
   

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of Kernel State Configuration Register:
  ///  -----------------------------------------------------------------------
  ///  - Enable the CAN module(MODEN)
  ///  - Enable Bit Protection for MODEN

    MCAN_KSCCFG  =  0x0003;      // load Kernel State Configuration Register

    _nop_();  // one cycle delay 

    _nop_();  // one cycle delay 


  ///  -----------------------------------------------------------------------
  ///  Configuration of the Module Clock:
  ///  -----------------------------------------------------------------------
  ///  - the CAN module clock = 40.00 MHz
  ///  - Normal divider mode selected

    CAN_FDRL     =  0x43FE;      // load Fractional Divider Register

  ///  -----------------------------------------------------------------------
  ///  Panel Control
  ///  -----------------------------------------------------------------------
  ///  - wait until Panel has finished the initialisation

    while(CAN_PANCTRL & CAN_PANCTR_BUSY){ // wait until Panel has finished 
                                          // the initialisation
      }                         

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 0:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 0:
  ///  - set INIT and CCE

    CAN_NCR0     =  0x0041;      // load NODE 0 control register[15-0]

  ///  - load NODE 0 interrupt pointer register

    CAN_NIPR0    =  0x0000;      // load NIPR0_LECINP, ALINP, CFCINP and TRINP

  ///  Configuration of the used CAN Port Pins:
  ///  - Loop-back mode is disabled
  ///  - P2.0 is used for CAN0 Receive input(RXDC0C)
  ///  - P2.1 is used for CAN0 Transmit output(TXDC0C)

  P2_IOCR01 = 0x0090;    //set direction register
    CAN_NPCR0    =  0x0002;      // load node0 port control register


  ///  Configuration of the Node 0 Baud Rate:
  ///  - required baud rate = 500.000 kbaud
  ///  - real baud rate     = 500.000 kbaud
  ///  - sample point       = 60.00 %
  ///  - there are 5 time quanta before sample point
  ///  - there are 4 time quanta after sample point
  ///  - the (re)synchronization jump width is 2 time quanta

    CAN_NBTR0L   =  0x3447;      // load NBTR0_DIV8, TSEG2, TSEG1, SJW and BRP

  ///  Configuration of the Node 0 Error Counter:
  ///  - the error warning threshold value (warning level) is 96

    CAN_NECNT0H = 0x0060;        // load NECNT0_EWRNLVL register
    CAN_NECNT0L = 0x0000;       

  ///  Configuration of the Frame Counter:
  ///  - Frame Counter Mode: the counter is incremented upon the reception 
  ///    and transmission of frames
  ///  - frame counter: 0x0000

    CAN_NFCR0H = 0x0000;         // load NFCR0_CFCOV, CFCIE, CFMOD, CFSEL
    CAN_NFCR0L = 0x0000;         // load NFCR0_CFC

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 1:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 1:
  ///  - set INIT and CCE

    CAN_NCR1     =  0x0041;      // load NODE 1 control register[15-0]

  ///  - load NODE 1 interrupt pointer register

    CAN_NIPR1    =  0x0000;      // load NIPR1_LECINP, ALINP, CFCINP and TRINP

  ///  Configuration of the used CAN Port Pins:
  ///  - Loop-back mode is disabled
  ///  - P0.4 is used for CAN1 Receive input(RXDC1B)
  ///  - P0.6 is used for CAN1 Transmit Output(TXDC1A)

  P0_IOCR06 = 0x00A0;    //set direction register
    CAN_NPCR1    =  0x0001;      // load node1 port control register


  ///  Configuration of the Node 1 Baud Rate:
  ///  - required baud rate = 500.000 kbaud
  ///  - real baud rate     = 500.000 kbaud
  ///  - sample point       = 60.00 %
  ///  - there are 5 time quanta before sample point
  ///  - there are 4 time quanta after sample point
  ///  - the (re)synchronization jump width is 2 time quanta

    CAN_NBTR1L   =  0x3447;      // load NBTR1_DIV8, TSEG2, TSEG1, SJW and BRP

  ///  Configuration of the Node 1 Error Counter:
  ///  - the error warning threshold value (warning level) is 96

    CAN_NECNT1H = 0x0060;        // load NECNT1_EWRNLVL register
    CAN_NECNT1L = 0x0000;       

  ///  Configuration of the Frame Counter:
  ///  - Frame Counter Mode: the counter is incremented upon the reception 
  ///    and transmission of frames
  ///  - frame counter: 0x0000

    CAN_NFCR1H = 0x0000;         // load NFCR1_CFCOV, CFCIE, CFMOD, CFSEL
    CAN_NFCR1L = 0x0000;         // load NFCR1_CFC

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 2:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 2:
  ///  - set INIT and CCE

    CAN_NCR2     =  0x0041;      // load NODE 2 control register[15-0]

  ///  - load NODE 2 interrupt pointer register

    CAN_NIPR2    =  0x0000;      // load NIPR2_LECINP, ALINP, CFCINP and TRINP

  ///  Configuration of the used CAN Port Pins:
  ///  - Loop-back mode is disabled
  ///  - P4.3 is used for CAN2 Receive inputA(RXDC2A)
  ///  - P4.2 is used for CAN2 Transmit output(TXDC2B)

  P4_IOCR02 = 0x00A0;    //set direction register
    CAN_NPCR2    =  0x0000;      // load node2 port control register


  ///  Configuration of the Node 2 Baud Rate:
  ///  - required baud rate = 500.000 kbaud
  ///  - real baud rate     = 500.000 kbaud
  ///  - sample point       = 60.00 %
  ///  - there are 5 time quanta before sample point
  ///  - there are 4 time quanta after sample point
  ///  - the (re)synchronization jump width is 2 time quanta

    CAN_NBTR2L   =  0x3447;      // load NBTR2_DIV8, TSEG2, TSEG1, SJW and BRP

  ///  Configuration of the Node 2 Error Counter:
  ///  - the error warning threshold value (warning level) is 96

    CAN_NECNT2H = 0x0060;        // load NECNT2_EWRNLVL register
    CAN_NECNT2L = 0x0000;       

  ///  Configuration of the Frame Counter:
  ///  - Frame Counter Mode: the counter is incremented upon the reception 
  ///    and transmission of frames
  ///  - frame counter: 0x0000

    CAN_NFCR2H = 0x0000;         // load NFCR2_CFCOV, CFCIE, CFMOD, CFSEL
    CAN_NFCR2L = 0x0000;         // load NFCR2_CFC

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 3:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 3:
  ///  - set INIT and CCE

    CAN_NCR3     =  0x0041;      // load NODE 3 control register[15-0]

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 4:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 4:
  ///  - set INIT and CCE

    CAN_NCR4     =  0x0041;      // load NODE 4 control register[15-0]

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 5:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 5:
  ///  - set INIT and CCE

    CAN_NCR5     =  0x0041;      // load NODE 5 control register[15-0]

  ///  -----------------------------------------------------------------------
  ///  Configuration of the CAN Message Object List Structure:
  ///  -----------------------------------------------------------------------

  ///  Allocate MOs for list 1:

    SetListCommand(0x010E,0x0002);  // MO14 for list 1 (Node 0)

    SetListCommand(0x010D,0x0002);  // MO13 for list 1 (Node 0)

    SetListCommand(0x010C,0x0002);  // MO12 for list 1 (Node 0)

    SetListCommand(0x010B,0x0002);  // MO11 for list 1 (Node 0)

    SetListCommand(0x010A,0x0002);  // MO10 for list 1 (Node 0)

    SetListCommand(0x0109,0x0002);  // MO9 for list 1 (Node 0)

    SetListCommand(0x0108,0x0002);  // MO8 for list 1 (Node 0)

    SetListCommand(0x0107,0x0002);  // MO7 for list 1 (Node 0)

    SetListCommand(0x0106,0x0002);  // MO6 for list 1 (Node 0)

    SetListCommand(0x0105,0x0002);  // MO5 for list 1 (Node 0)

    SetListCommand(0x0104,0x0002);  // MO4 for list 1 (Node 0)

    SetListCommand(0x0103,0x0002);  // MO3 for list 1 (Node 0)

    SetListCommand(0x0102,0x0002);  // MO2 for list 1 (Node 0)

    SetListCommand(0x0101,0x0002);  // MO1 for list 1 (Node 0)

    SetListCommand(0x0100,0x0002);  // MO0 for list 1 (Node 0)

    SetListCommand(0x010F,0x0002);  // MO15 for list 1 (Node 0)

    SetListCommand(0x0110,0x0002);  // MO16 for list 1 (Node 0)

    SetListCommand(0x0111,0x0002);  // MO17 for list 1 (Node 0)

    SetListCommand(0x0112,0x0002);  // MO18 for list 1 (Node 0)

    SetListCommand(0x0119,0x0002);  // MO25 for list 1 (Node 0)

    SetListCommand(0x0113,0x0002);  // MO19 for list 1 (Node 0)

    SetListCommand(0x0114,0x0002);  // MO20 for list 1 (Node 0)

    SetListCommand(0x0115,0x0002);  // MO21 for list 1 (Node 0)

    SetListCommand(0x0116,0x0002);  // MO22 for list 1 (Node 0)

    SetListCommand(0x0117,0x0002);  // MO23 for list 1 (Node 0)

    SetListCommand(0x0118,0x0002);  // MO24 for list 1 (Node 0)

    SetListCommand(0x011A,0x0002);  // MO26 for list 1 (Node 0)

  ///  -----------------------------------------------------------------------
  ///  Configuration of the CAN Message Objects 0 - 254:
  ///  -----------------------------------------------------------------------
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 0:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 0 :
  ///  - message object 0 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR0H = 0x00A0;        // load MO0 control register high
    CAN_MOCTR0L = 0x0000;        // load MO0 control register low

  ///  Configuration of Message Object 0 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x316

    CAN_MOAR0H = 0x4C58;         // load MO0 arbitration register high
    CAN_MOAR0L = 0x0000;         // load MO0 arbitration register low

  ///  Configuration of Message Object 0 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR0H = 0x3FFF;        // load MO0 acceptance mask register high
    CAN_MOAMR0L = 0xFFFF;        // load MO0 acceptance mask register low

  ///  Configuration of Message Object 0 interrupt pointer:
  ///  - use message pending register 0 bit position 0
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR0H = 0x0000;        // load MO0 interrupt pointer register high
    CAN_MOIPR0L = 0x0000;        // load MO0 interrupt pointer register low

  ///  Configuration of Message Object 0 FIFO/Gateway pointer:

    CAN_MOFGPR0H = 0x0000;       // load MO0 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR0L = 0x0000;       // load MO0 FIFO/gateway pointer register low


  ///  Configuration of Message Object 0 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR0H = 0x0801;        // load MO0 function control register high
    CAN_MOFCR0L = 0x0000;        // load MO0 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 1:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 1 :
  ///  - message object 1 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR1H = 0x00A0;        // load MO1 control register high
    CAN_MOCTR1L = 0x0000;        // load MO1 control register low

  ///  Configuration of Message Object 1 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x326

    CAN_MOAR1H = 0x4C98;         // load MO1 arbitration register high
    CAN_MOAR1L = 0x0000;         // load MO1 arbitration register low

  ///  Configuration of Message Object 1 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR1H = 0x3FFF;        // load MO1 acceptance mask register high
    CAN_MOAMR1L = 0xFFFF;        // load MO1 acceptance mask register low

  ///  Configuration of Message Object 1 interrupt pointer:
  ///  - use message pending register 0 bit position 1
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR1H = 0x0000;        // load MO1 interrupt pointer register high
    CAN_MOIPR1L = 0x0100;        // load MO1 interrupt pointer register low

  ///  Configuration of Message Object 1 FIFO/Gateway pointer:

    CAN_MOFGPR1H = 0x0000;       // load MO1 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR1L = 0x0000;       // load MO1 FIFO/gateway pointer register low


  ///  Configuration of Message Object 1 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR1H = 0x0801;        // load MO1 function control register high
    CAN_MOFCR1L = 0x0000;        // load MO1 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 2:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 2 :
  ///  - message object 2 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR2H = 0x00A0;        // load MO2 control register high
    CAN_MOCTR2L = 0x0000;        // load MO2 control register low

  ///  Configuration of Message Object 2 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x336

    CAN_MOAR2H = 0x4CD8;         // load MO2 arbitration register high
    CAN_MOAR2L = 0x0000;         // load MO2 arbitration register low

  ///  Configuration of Message Object 2 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR2H = 0x3FFF;        // load MO2 acceptance mask register high
    CAN_MOAMR2L = 0xFFFF;        // load MO2 acceptance mask register low

  ///  Configuration of Message Object 2 interrupt pointer:
  ///  - use message pending register 0 bit position 2
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR2H = 0x0000;        // load MO2 interrupt pointer register high
    CAN_MOIPR2L = 0x0200;        // load MO2 interrupt pointer register low

  ///  Configuration of Message Object 2 FIFO/Gateway pointer:

    CAN_MOFGPR2H = 0x0000;       // load MO2 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR2L = 0x0000;       // load MO2 FIFO/gateway pointer register low


  ///  Configuration of Message Object 2 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR2H = 0x0801;        // load MO2 function control register high
    CAN_MOFCR2L = 0x0000;        // load MO2 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 3:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 3 :
  ///  - message object 3 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR3H = 0x00A0;        // load MO3 control register high
    CAN_MOCTR3L = 0x0000;        // load MO3 control register low

  ///  Configuration of Message Object 3 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x346

    CAN_MOAR3H = 0x4D18;         // load MO3 arbitration register high
    CAN_MOAR3L = 0x0000;         // load MO3 arbitration register low

  ///  Configuration of Message Object 3 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR3H = 0x3FFF;        // load MO3 acceptance mask register high
    CAN_MOAMR3L = 0xFFFF;        // load MO3 acceptance mask register low

  ///  Configuration of Message Object 3 interrupt pointer:
  ///  - use message pending register 0 bit position 3
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR3H = 0x0000;        // load MO3 interrupt pointer register high
    CAN_MOIPR3L = 0x0300;        // load MO3 interrupt pointer register low

  ///  Configuration of Message Object 3 FIFO/Gateway pointer:

    CAN_MOFGPR3H = 0x0000;       // load MO3 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR3L = 0x0000;       // load MO3 FIFO/gateway pointer register low


  ///  Configuration of Message Object 3 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR3H = 0x0801;        // load MO3 function control register high
    CAN_MOFCR3L = 0x0000;        // load MO3 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 4:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 4 :
  ///  - message object 4 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR4H = 0x00A0;        // load MO4 control register high
    CAN_MOCTR4L = 0x0000;        // load MO4 control register low

  ///  Configuration of Message Object 4 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x416

    CAN_MOAR4H = 0x5058;         // load MO4 arbitration register high
    CAN_MOAR4L = 0x0000;         // load MO4 arbitration register low

  ///  Configuration of Message Object 4 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR4H = 0x3FFF;        // load MO4 acceptance mask register high
    CAN_MOAMR4L = 0xFFFF;        // load MO4 acceptance mask register low

  ///  Configuration of Message Object 4 interrupt pointer:
  ///  - use message pending register 0 bit position 4
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR4H = 0x0000;        // load MO4 interrupt pointer register high
    CAN_MOIPR4L = 0x0400;        // load MO4 interrupt pointer register low

  ///  Configuration of Message Object 4 FIFO/Gateway pointer:

    CAN_MOFGPR4H = 0x0000;       // load MO4 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR4L = 0x0000;       // load MO4 FIFO/gateway pointer register low


  ///  Configuration of Message Object 4 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR4H = 0x0801;        // load MO4 function control register high
    CAN_MOFCR4L = 0x0000;        // load MO4 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 5:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 5 :
  ///  - message object 5 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR5H = 0x00A0;        // load MO5 control register high
    CAN_MOCTR5L = 0x0000;        // load MO5 control register low

  ///  Configuration of Message Object 5 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x426

    CAN_MOAR5H = 0x5098;         // load MO5 arbitration register high
    CAN_MOAR5L = 0x0000;         // load MO5 arbitration register low

  ///  Configuration of Message Object 5 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR5H = 0x3FFF;        // load MO5 acceptance mask register high
    CAN_MOAMR5L = 0xFFFF;        // load MO5 acceptance mask register low

  ///  Configuration of Message Object 5 interrupt pointer:
  ///  - use message pending register 0 bit position 5
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR5H = 0x0000;        // load MO5 interrupt pointer register high
    CAN_MOIPR5L = 0x0500;        // load MO5 interrupt pointer register low

  ///  Configuration of Message Object 5 FIFO/Gateway pointer:

    CAN_MOFGPR5H = 0x0000;       // load MO5 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR5L = 0x0000;       // load MO5 FIFO/gateway pointer register low


  ///  Configuration of Message Object 5 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR5H = 0x0801;        // load MO5 function control register high
    CAN_MOFCR5L = 0x0000;        // load MO5 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 6:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 6 :
  ///  - message object 6 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR6H = 0x0EA8;        // load MO6 control register high
    CAN_MOCTR6L = 0x0000;        // load MO6 control register low

  ///  Configuration of Message Object 6 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x410

    CAN_MOAR6H = 0x5040;         // load MO6 arbitration register high
    CAN_MOAR6L = 0x0000;         // load MO6 arbitration register low

  ///  Configuration of Message Object 6 Data:

    CAN_MODATA6HH = 0x0000;      // load MO6 Data Bytes(DB7 & DB6)
    CAN_MODATA6HL = 0x0000;      // load MO6 Data Bytes(DB5 & DB4)
    CAN_MODATA6LH = 0x0000;      // load MO6 Data Bytes(DB3 & DB2)
    CAN_MODATA6LL = 0x0000;      // load MO6 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 6 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x000

    CAN_MOAMR6H = 0x2000;        // load MO6 acceptance mask register high
    CAN_MOAMR6L = 0x0000;        // load MO6 acceptance mask register low

  ///  Configuration of Message Object 6 interrupt pointer:
  ///  - use message pending register 0 bit position 6

    CAN_MOIPR6H = 0x0000;        // load MO6 interrupt pointer register high
    CAN_MOIPR6L = 0x0600;        // load MO6 interrupt pointer register low

  ///  Configuration of Message Object 6 FIFO/Gateway pointer:

    CAN_MOFGPR6H = 0x0000;       // load MO6 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR6L = 0x0000;       // load MO6 FIFO/gateway pointer register low


  ///  Configuration of Message Object 6 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR6H = 0x0800;        // load MO6 function control register high
    CAN_MOFCR6L = 0x0000;        // load MO6 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 7:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 7 :
  ///  - message object 7 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR7H = 0x0EA8;        // load MO7 control register high
    CAN_MOCTR7L = 0x0000;        // load MO7 control register low

  ///  Configuration of Message Object 7 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x420

    CAN_MOAR7H = 0x5080;         // load MO7 arbitration register high
    CAN_MOAR7L = 0x0000;         // load MO7 arbitration register low

  ///  Configuration of Message Object 7 Data:

    CAN_MODATA7HH = 0x0000;      // load MO7 Data Bytes(DB7 & DB6)
    CAN_MODATA7HL = 0x0000;      // load MO7 Data Bytes(DB5 & DB4)
    CAN_MODATA7LH = 0x0000;      // load MO7 Data Bytes(DB3 & DB2)
    CAN_MODATA7LL = 0x0000;      // load MO7 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 7 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR7H = 0x3FFF;        // load MO7 acceptance mask register high
    CAN_MOAMR7L = 0xFFFF;        // load MO7 acceptance mask register low

  ///  Configuration of Message Object 7 interrupt pointer:
  ///  - use message pending register 0 bit position 7

    CAN_MOIPR7H = 0x0000;        // load MO7 interrupt pointer register high
    CAN_MOIPR7L = 0x0700;        // load MO7 interrupt pointer register low

  ///  Configuration of Message Object 7 FIFO/Gateway pointer:

    CAN_MOFGPR7H = 0x0000;       // load MO7 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR7L = 0x0000;       // load MO7 FIFO/gateway pointer register low


  ///  Configuration of Message Object 7 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR7H = 0x0800;        // load MO7 function control register high
    CAN_MOFCR7L = 0x0000;        // load MO7 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 8:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 8 :
  ///  - message object 8 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR8H = 0x0EA8;        // load MO8 control register high
    CAN_MOCTR8L = 0x0000;        // load MO8 control register low

  ///  Configuration of Message Object 8 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x310

    CAN_MOAR8H = 0x4C40;         // load MO8 arbitration register high
    CAN_MOAR8L = 0x0000;         // load MO8 arbitration register low

  ///  Configuration of Message Object 8 Data:

    CAN_MODATA8HH = 0x0000;      // load MO8 Data Bytes(DB7 & DB6)
    CAN_MODATA8HL = 0x0000;      // load MO8 Data Bytes(DB5 & DB4)
    CAN_MODATA8LH = 0x0000;      // load MO8 Data Bytes(DB3 & DB2)
    CAN_MODATA8LL = 0x0000;      // load MO8 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 8 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR8H = 0x3FFF;        // load MO8 acceptance mask register high
    CAN_MOAMR8L = 0xFFFF;        // load MO8 acceptance mask register low

  ///  Configuration of Message Object 8 interrupt pointer:
  ///  - use message pending register 0 bit position 8

    CAN_MOIPR8H = 0x0000;        // load MO8 interrupt pointer register high
    CAN_MOIPR8L = 0x0800;        // load MO8 interrupt pointer register low

  ///  Configuration of Message Object 8 FIFO/Gateway pointer:

    CAN_MOFGPR8H = 0x0000;       // load MO8 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR8L = 0x0000;       // load MO8 FIFO/gateway pointer register low


  ///  Configuration of Message Object 8 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR8H = 0x0800;        // load MO8 function control register high
    CAN_MOFCR8L = 0x0000;        // load MO8 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 9:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 9 :
  ///  - message object 9 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR9H = 0x0EA8;        // load MO9 control register high
    CAN_MOCTR9L = 0x0000;        // load MO9 control register low

  ///  Configuration of Message Object 9 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x320

    CAN_MOAR9H = 0x4C80;         // load MO9 arbitration register high
    CAN_MOAR9L = 0x0000;         // load MO9 arbitration register low

  ///  Configuration of Message Object 9 Data:

    CAN_MODATA9HH = 0x0000;      // load MO9 Data Bytes(DB7 & DB6)
    CAN_MODATA9HL = 0x0000;      // load MO9 Data Bytes(DB5 & DB4)
    CAN_MODATA9LH = 0x0000;      // load MO9 Data Bytes(DB3 & DB2)
    CAN_MODATA9LL = 0x0000;      // load MO9 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 9 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR9H = 0x3FFF;        // load MO9 acceptance mask register high
    CAN_MOAMR9L = 0xFFFF;        // load MO9 acceptance mask register low

  ///  Configuration of Message Object 9 interrupt pointer:
  ///  - use message pending register 0 bit position 9

    CAN_MOIPR9H = 0x0000;        // load MO9 interrupt pointer register high
    CAN_MOIPR9L = 0x0900;        // load MO9 interrupt pointer register low

  ///  Configuration of Message Object 9 FIFO/Gateway pointer:

    CAN_MOFGPR9H = 0x0000;       // load MO9 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR9L = 0x0000;       // load MO9 FIFO/gateway pointer register low


  ///  Configuration of Message Object 9 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR9H = 0x0800;        // load MO9 function control register high
    CAN_MOFCR9L = 0x0000;        // load MO9 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 10:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 10 :
  ///  - message object 10 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR10H = 0x0EA8;       // load MO10 control register high
    CAN_MOCTR10L = 0x0000;       // load MO10 control register low

  ///  Configuration of Message Object 10 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x330

    CAN_MOAR10H = 0x4CC0;        // load MO10 arbitration register high
    CAN_MOAR10L = 0x0000;        // load MO10 arbitration register low

  ///  Configuration of Message Object 10 Data:

    CAN_MODATA10HH = 0x0000;     // load MO10 Data Bytes(DB7 & DB6)
    CAN_MODATA10HL = 0x0000;     // load MO10 Data Bytes(DB5 & DB4)
    CAN_MODATA10LH = 0x0000;     // load MO10 Data Bytes(DB3 & DB2)
    CAN_MODATA10LL = 0x0000;     // load MO10 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 10 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR10H = 0x3FFF;       // load MO10 acceptance mask register high
    CAN_MOAMR10L = 0xFFFF;       // load MO10 acceptance mask register low

  ///  Configuration of Message Object 10 interrupt pointer:
  ///  - use message pending register 0 bit position 10

    CAN_MOIPR10H = 0x0000;       // load MO10 interrupt pointer register high
    CAN_MOIPR10L = 0x0A00;       // load MO10 interrupt pointer register low

  ///  Configuration of Message Object 10 FIFO/Gateway pointer:

    CAN_MOFGPR10H = 0x0000;      // load MO10 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR10L = 0x0000;      // load MO10 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 10 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR10H = 0x0800;       // load MO10 function control register high
    CAN_MOFCR10L = 0x0000;       // load MO10 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 11:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 11 :
  ///  - message object 11 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR11H = 0x0EA8;       // load MO11 control register high
    CAN_MOCTR11L = 0x0000;       // load MO11 control register low

  ///  Configuration of Message Object 11 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x340

    CAN_MOAR11H = 0x4D00;        // load MO11 arbitration register high
    CAN_MOAR11L = 0x0000;        // load MO11 arbitration register low

  ///  Configuration of Message Object 11 Data:

    CAN_MODATA11HH = 0x0000;     // load MO11 Data Bytes(DB7 & DB6)
    CAN_MODATA11HL = 0x0000;     // load MO11 Data Bytes(DB5 & DB4)
    CAN_MODATA11LH = 0x0000;     // load MO11 Data Bytes(DB3 & DB2)
    CAN_MODATA11LL = 0x0000;     // load MO11 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 11 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR11H = 0x3FFF;       // load MO11 acceptance mask register high
    CAN_MOAMR11L = 0xFFFF;       // load MO11 acceptance mask register low

  ///  Configuration of Message Object 11 interrupt pointer:
  ///  - use message pending register 0 bit position 11

    CAN_MOIPR11H = 0x0000;       // load MO11 interrupt pointer register high
    CAN_MOIPR11L = 0x0B00;       // load MO11 interrupt pointer register low

  ///  Configuration of Message Object 11 FIFO/Gateway pointer:

    CAN_MOFGPR11H = 0x0000;      // load MO11 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR11L = 0x0000;      // load MO11 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 11 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR11H = 0x0800;       // load MO11 function control register high
    CAN_MOFCR11L = 0x0000;       // load MO11 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 12:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 12 :
  ///  - message object 12 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR12H = 0x00A0;       // load MO12 control register high
    CAN_MOCTR12L = 0x0000;       // load MO12 control register low

  ///  Configuration of Message Object 12 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x283

    CAN_MOAR12H = 0x4A0C;        // load MO12 arbitration register high
    CAN_MOAR12L = 0x0000;        // load MO12 arbitration register low

  ///  Configuration of Message Object 12 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR12H = 0x3FFF;       // load MO12 acceptance mask register high
    CAN_MOAMR12L = 0xFFFF;       // load MO12 acceptance mask register low

  ///  Configuration of Message Object 12 interrupt pointer:
  ///  - use message pending register 0 bit position 12
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR12H = 0x0000;       // load MO12 interrupt pointer register high
    CAN_MOIPR12L = 0x0C00;       // load MO12 interrupt pointer register low

  ///  Configuration of Message Object 12 FIFO/Gateway pointer:

    CAN_MOFGPR12H = 0x0000;      // load MO12 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR12L = 0x0000;      // load MO12 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 12 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR12H = 0x0801;       // load MO12 function control register high
    CAN_MOFCR12L = 0x0000;       // load MO12 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 13:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 13 :
  ///  - message object 13 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR13H = 0x0EA8;       // load MO13 control register high
    CAN_MOCTR13L = 0x0000;       // load MO13 control register low

  ///  Configuration of Message Object 13 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x190

    CAN_MOAR13H = 0x4640;        // load MO13 arbitration register high
    CAN_MOAR13L = 0x0000;        // load MO13 arbitration register low

  ///  Configuration of Message Object 13 Data:

    CAN_MODATA13HH = 0x0000;     // load MO13 Data Bytes(DB7 & DB6)
    CAN_MODATA13HL = 0x0000;     // load MO13 Data Bytes(DB5 & DB4)
    CAN_MODATA13LH = 0x0000;     // load MO13 Data Bytes(DB3 & DB2)
    CAN_MODATA13LL = 0x0000;     // load MO13 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 13 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR13H = 0x3FFF;       // load MO13 acceptance mask register high
    CAN_MOAMR13L = 0xFFFF;       // load MO13 acceptance mask register low

  ///  Configuration of Message Object 13 interrupt pointer:
  ///  - use message pending register 0 bit position 13

    CAN_MOIPR13H = 0x0000;       // load MO13 interrupt pointer register high
    CAN_MOIPR13L = 0x0D00;       // load MO13 interrupt pointer register low

  ///  Configuration of Message Object 13 FIFO/Gateway pointer:

    CAN_MOFGPR13H = 0x0000;      // load MO13 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR13L = 0x0000;      // load MO13 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 13 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR13H = 0x0800;       // load MO13 function control register high
    CAN_MOFCR13L = 0x0000;       // load MO13 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 14:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 14 :
  ///  - message object 14 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR14H = 0x0EA8;       // load MO14 control register high
    CAN_MOCTR14L = 0x0000;       // load MO14 control register low

  ///  Configuration of Message Object 14 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x077

    CAN_MOAR14H = 0x41DC;        // load MO14 arbitration register high
    CAN_MOAR14L = 0x0000;        // load MO14 arbitration register low

  ///  Configuration of Message Object 14 Data:

    CAN_MODATA14HH = 0x0000;     // load MO14 Data Bytes(DB7 & DB6)
    CAN_MODATA14HL = 0x0000;     // load MO14 Data Bytes(DB5 & DB4)
    CAN_MODATA14LH = 0x0000;     // load MO14 Data Bytes(DB3 & DB2)
    CAN_MODATA14LL = 0x0000;     // load MO14 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 14 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR14H = 0x3FFF;       // load MO14 acceptance mask register high
    CAN_MOAMR14L = 0xFFFF;       // load MO14 acceptance mask register low

  ///  Configuration of Message Object 14 interrupt pointer:
  ///  - use message pending register 0 bit position 14

    CAN_MOIPR14H = 0x0000;       // load MO14 interrupt pointer register high
    CAN_MOIPR14L = 0x0E00;       // load MO14 interrupt pointer register low

  ///  Configuration of Message Object 14 FIFO/Gateway pointer:

    CAN_MOFGPR14H = 0x0000;      // load MO14 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR14L = 0x0000;      // load MO14 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 14 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR14H = 0x0800;       // load MO14 function control register high
    CAN_MOFCR14L = 0x0000;       // load MO14 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 15:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 15 :
  ///  - message object 15 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR15H = 0x00A0;       // load MO15 control register high
    CAN_MOCTR15L = 0x0000;       // load MO15 control register low

  ///  Configuration of Message Object 15 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x183

    CAN_MOAR15H = 0x460C;        // load MO15 arbitration register high
    CAN_MOAR15L = 0x0000;        // load MO15 arbitration register low

  ///  Configuration of Message Object 15 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR15H = 0x3FFF;       // load MO15 acceptance mask register high
    CAN_MOAMR15L = 0xFFFF;       // load MO15 acceptance mask register low

  ///  Configuration of Message Object 15 interrupt pointer:
  ///  - use message pending register 0 bit position 15
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR15H = 0x0000;       // load MO15 interrupt pointer register high
    CAN_MOIPR15L = 0x0F00;       // load MO15 interrupt pointer register low

  ///  Configuration of Message Object 15 FIFO/Gateway pointer:

    CAN_MOFGPR15H = 0x0000;      // load MO15 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR15L = 0x0000;      // load MO15 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 15 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR15H = 0x0801;       // load MO15 function control register high
    CAN_MOFCR15L = 0x0000;       // load MO15 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 16:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 16 :
  ///  - message object 16 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR16H = 0x00A0;       // load MO16 control register high
    CAN_MOCTR16L = 0x0000;       // load MO16 control register low

  ///  Configuration of Message Object 16 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x436

    CAN_MOAR16H = 0x50D8;        // load MO16 arbitration register high
    CAN_MOAR16L = 0x0000;        // load MO16 arbitration register low

  ///  Configuration of Message Object 16 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR16H = 0x3FFF;       // load MO16 acceptance mask register high
    CAN_MOAMR16L = 0xFFFF;       // load MO16 acceptance mask register low

  ///  Configuration of Message Object 16 interrupt pointer:
  ///  - use message pending register 0 bit position 16
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR16H = 0x0000;       // load MO16 interrupt pointer register high
    CAN_MOIPR16L = 0x1000;       // load MO16 interrupt pointer register low

  ///  Configuration of Message Object 16 FIFO/Gateway pointer:

    CAN_MOFGPR16H = 0x0000;      // load MO16 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR16L = 0x0000;      // load MO16 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 16 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR16H = 0x0801;       // load MO16 function control register high
    CAN_MOFCR16L = 0x0000;       // load MO16 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 17:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 17 :
  ///  - message object 17 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR17H = 0x0EA8;       // load MO17 control register high
    CAN_MOCTR17L = 0x0000;       // load MO17 control register low

  ///  Configuration of Message Object 17 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x430

    CAN_MOAR17H = 0x50C0;        // load MO17 arbitration register high
    CAN_MOAR17L = 0x0000;        // load MO17 arbitration register low

  ///  Configuration of Message Object 17 Data:

    CAN_MODATA17HH = 0x0000;     // load MO17 Data Bytes(DB7 & DB6)
    CAN_MODATA17HL = 0x0000;     // load MO17 Data Bytes(DB5 & DB4)
    CAN_MODATA17LH = 0x0000;     // load MO17 Data Bytes(DB3 & DB2)
    CAN_MODATA17LL = 0x0000;     // load MO17 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 17 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR17H = 0x3FFF;       // load MO17 acceptance mask register high
    CAN_MOAMR17L = 0xFFFF;       // load MO17 acceptance mask register low

  ///  Configuration of Message Object 17 interrupt pointer:
  ///  - use message pending register 0 bit position 17

    CAN_MOIPR17H = 0x0000;       // load MO17 interrupt pointer register high
    CAN_MOIPR17L = 0x1100;       // load MO17 interrupt pointer register low

  ///  Configuration of Message Object 17 FIFO/Gateway pointer:

    CAN_MOFGPR17H = 0x0000;      // load MO17 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR17L = 0x0000;      // load MO17 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 17 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR17H = 0x0800;       // load MO17 function control register high
    CAN_MOFCR17L = 0x0000;       // load MO17 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 18:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 18 :
  ///  - message object 18 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR18H = 0x0EA8;       // load MO18 control register high
    CAN_MOCTR18L = 0x0000;       // load MO18 control register low

  ///  Configuration of Message Object 18 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x401

    CAN_MOAR18H = 0x5004;        // load MO18 arbitration register high
    CAN_MOAR18L = 0x0000;        // load MO18 arbitration register low

  ///  Configuration of Message Object 18 Data:

    CAN_MODATA18HH = 0x0000;     // load MO18 Data Bytes(DB7 & DB6)
    CAN_MODATA18HL = 0x0000;     // load MO18 Data Bytes(DB5 & DB4)
    CAN_MODATA18LH = 0x0000;     // load MO18 Data Bytes(DB3 & DB2)
    CAN_MODATA18LL = 0x0000;     // load MO18 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 18 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR18H = 0x3FFF;       // load MO18 acceptance mask register high
    CAN_MOAMR18L = 0xFFFF;       // load MO18 acceptance mask register low

  ///  Configuration of Message Object 18 interrupt pointer:
  ///  - use message pending register 0 bit position 18

    CAN_MOIPR18H = 0x0000;       // load MO18 interrupt pointer register high
    CAN_MOIPR18L = 0x1200;       // load MO18 interrupt pointer register low

  ///  Configuration of Message Object 18 FIFO/Gateway pointer:

    CAN_MOFGPR18H = 0x0000;      // load MO18 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR18L = 0x0000;      // load MO18 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 18 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR18H = 0x0800;       // load MO18 function control register high
    CAN_MOFCR18L = 0x0000;       // load MO18 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 19:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 19 :
  ///  - message object 19 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR19H = 0x00A0;       // load MO19 control register high
    CAN_MOCTR19L = 0x0000;       // load MO19 control register low

  ///  Configuration of Message Object 19 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x319

    CAN_MOAR19H = 0x4C64;        // load MO19 arbitration register high
    CAN_MOAR19L = 0x0000;        // load MO19 arbitration register low

  ///  Configuration of Message Object 19 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR19H = 0x3FFF;       // load MO19 acceptance mask register high
    CAN_MOAMR19L = 0xFFFF;       // load MO19 acceptance mask register low

  ///  Configuration of Message Object 19 interrupt pointer:
  ///  - use message pending register 0 bit position 19
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR19H = 0x0000;       // load MO19 interrupt pointer register high
    CAN_MOIPR19L = 0x1300;       // load MO19 interrupt pointer register low

  ///  Configuration of Message Object 19 FIFO/Gateway pointer:

    CAN_MOFGPR19H = 0x0000;      // load MO19 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR19L = 0x0000;      // load MO19 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 19 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR19H = 0x0801;       // load MO19 function control register high
    CAN_MOFCR19L = 0x0000;       // load MO19 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 20:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 20 :
  ///  - message object 20 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR20H = 0x00A0;       // load MO20 control register high
    CAN_MOCTR20L = 0x0000;       // load MO20 control register low

  ///  Configuration of Message Object 20 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x329

    CAN_MOAR20H = 0x4CA4;        // load MO20 arbitration register high
    CAN_MOAR20L = 0x0000;        // load MO20 arbitration register low

  ///  Configuration of Message Object 20 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR20H = 0x3FFF;       // load MO20 acceptance mask register high
    CAN_MOAMR20L = 0xFFFF;       // load MO20 acceptance mask register low

  ///  Configuration of Message Object 20 interrupt pointer:
  ///  - use message pending register 0 bit position 20
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR20H = 0x0000;       // load MO20 interrupt pointer register high
    CAN_MOIPR20L = 0x1400;       // load MO20 interrupt pointer register low

  ///  Configuration of Message Object 20 FIFO/Gateway pointer:

    CAN_MOFGPR20H = 0x0000;      // load MO20 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR20L = 0x0000;      // load MO20 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 20 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR20H = 0x0801;       // load MO20 function control register high
    CAN_MOFCR20L = 0x0000;       // load MO20 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 21:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 21 :
  ///  - message object 21 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR21H = 0x00A0;       // load MO21 control register high
    CAN_MOCTR21L = 0x0000;       // load MO21 control register low

  ///  Configuration of Message Object 21 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x339

    CAN_MOAR21H = 0x4CE4;        // load MO21 arbitration register high
    CAN_MOAR21L = 0x0000;        // load MO21 arbitration register low

  ///  Configuration of Message Object 21 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR21H = 0x3FFF;       // load MO21 acceptance mask register high
    CAN_MOAMR21L = 0xFFFF;       // load MO21 acceptance mask register low

  ///  Configuration of Message Object 21 interrupt pointer:
  ///  - use message pending register 0 bit position 21
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR21H = 0x0000;       // load MO21 interrupt pointer register high
    CAN_MOIPR21L = 0x1500;       // load MO21 interrupt pointer register low

  ///  Configuration of Message Object 21 FIFO/Gateway pointer:

    CAN_MOFGPR21H = 0x0000;      // load MO21 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR21L = 0x0000;      // load MO21 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 21 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR21H = 0x0801;       // load MO21 function control register high
    CAN_MOFCR21L = 0x0000;       // load MO21 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 22:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 22 :
  ///  - message object 22 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR22H = 0x00A0;       // load MO22 control register high
    CAN_MOCTR22L = 0x0000;       // load MO22 control register low

  ///  Configuration of Message Object 22 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x349

    CAN_MOAR22H = 0x4D24;        // load MO22 arbitration register high
    CAN_MOAR22L = 0x0000;        // load MO22 arbitration register low

  ///  Configuration of Message Object 22 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR22H = 0x3FFF;       // load MO22 acceptance mask register high
    CAN_MOAMR22L = 0xFFFF;       // load MO22 acceptance mask register low

  ///  Configuration of Message Object 22 interrupt pointer:
  ///  - use message pending register 0 bit position 22
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR22H = 0x0000;       // load MO22 interrupt pointer register high
    CAN_MOIPR22L = 0x1600;       // load MO22 interrupt pointer register low

  ///  Configuration of Message Object 22 FIFO/Gateway pointer:

    CAN_MOFGPR22H = 0x0000;      // load MO22 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR22L = 0x0000;      // load MO22 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 22 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR22H = 0x0801;       // load MO22 function control register high
    CAN_MOFCR22L = 0x0000;       // load MO22 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 23:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 23 :
  ///  - message object 23 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR23H = 0x0EA8;       // load MO23 control register high
    CAN_MOCTR23L = 0x0000;       // load MO23 control register low

  ///  Configuration of Message Object 23 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x196

    CAN_MOAR23H = 0x4658;        // load MO23 arbitration register high
    CAN_MOAR23L = 0x0000;        // load MO23 arbitration register low

  ///  Configuration of Message Object 23 Data:

    CAN_MODATA23HH = 0x0000;     // load MO23 Data Bytes(DB7 & DB6)
    CAN_MODATA23HL = 0x0000;     // load MO23 Data Bytes(DB5 & DB4)
    CAN_MODATA23LH = 0x0000;     // load MO23 Data Bytes(DB3 & DB2)
    CAN_MODATA23LL = 0x0000;     // load MO23 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 23 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR23H = 0x3FFF;       // load MO23 acceptance mask register high
    CAN_MOAMR23L = 0xFFFF;       // load MO23 acceptance mask register low

  ///  Configuration of Message Object 23 interrupt pointer:
  ///  - use message pending register 0 bit position 23

    CAN_MOIPR23H = 0x0000;       // load MO23 interrupt pointer register high
    CAN_MOIPR23L = 0x1700;       // load MO23 interrupt pointer register low

  ///  Configuration of Message Object 23 FIFO/Gateway pointer:

    CAN_MOFGPR23H = 0x0000;      // load MO23 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR23L = 0x0000;      // load MO23 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 23 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR23H = 0x0800;       // load MO23 function control register high
    CAN_MOFCR23L = 0x0000;       // load MO23 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 24:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 24 :
  ///  - message object 24 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR24H = 0x0EA8;       // load MO24 control register high
    CAN_MOCTR24L = 0x0000;       // load MO24 control register low

  ///  Configuration of Message Object 24 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x197

    CAN_MOAR24H = 0x465C;        // load MO24 arbitration register high
    CAN_MOAR24L = 0x0000;        // load MO24 arbitration register low

  ///  Configuration of Message Object 24 Data:

    CAN_MODATA24HH = 0x0000;     // load MO24 Data Bytes(DB7 & DB6)
    CAN_MODATA24HL = 0x0000;     // load MO24 Data Bytes(DB5 & DB4)
    CAN_MODATA24LH = 0x0000;     // load MO24 Data Bytes(DB3 & DB2)
    CAN_MODATA24LL = 0x0000;     // load MO24 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 24 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR24H = 0x3FFF;       // load MO24 acceptance mask register high
    CAN_MOAMR24L = 0xFFFF;       // load MO24 acceptance mask register low

  ///  Configuration of Message Object 24 interrupt pointer:
  ///  - use message pending register 0 bit position 24

    CAN_MOIPR24H = 0x0000;       // load MO24 interrupt pointer register high
    CAN_MOIPR24L = 0x1800;       // load MO24 interrupt pointer register low

  ///  Configuration of Message Object 24 FIFO/Gateway pointer:

    CAN_MOFGPR24H = 0x0000;      // load MO24 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR24L = 0x0000;      // load MO24 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 24 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR24H = 0x0800;       // load MO24 function control register high
    CAN_MOFCR24L = 0x0000;       // load MO24 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 25:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 25 :
  ///  - message object 25 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR25H = 0x0EA8;       // load MO25 control register high
    CAN_MOCTR25L = 0x0000;       // load MO25 control register low

  ///  Configuration of Message Object 25 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x101

    CAN_MOAR25H = 0x4404;        // load MO25 arbitration register high
    CAN_MOAR25L = 0x0000;        // load MO25 arbitration register low

  ///  Configuration of Message Object 25 Data:

    CAN_MODATA25HH = 0x0000;     // load MO25 Data Bytes(DB7 & DB6)
    CAN_MODATA25HL = 0x0000;     // load MO25 Data Bytes(DB5 & DB4)
    CAN_MODATA25LH = 0x0000;     // load MO25 Data Bytes(DB3 & DB2)
    CAN_MODATA25LL = 0x0000;     // load MO25 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 25 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR25H = 0x3FFF;       // load MO25 acceptance mask register high
    CAN_MOAMR25L = 0xFFFF;       // load MO25 acceptance mask register low

  ///  Configuration of Message Object 25 interrupt pointer:
  ///  - use message pending register 0 bit position 25

    CAN_MOIPR25H = 0x0000;       // load MO25 interrupt pointer register high
    CAN_MOIPR25L = 0x1900;       // load MO25 interrupt pointer register low

  ///  Configuration of Message Object 25 FIFO/Gateway pointer:

    CAN_MOFGPR25H = 0x0000;      // load MO25 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR25L = 0x0000;      // load MO25 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 25 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR25H = 0x0800;       // load MO25 function control register high
    CAN_MOFCR25L = 0x0000;       // load MO25 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 26:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 26 :
  ///  - message object 26 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR26H = 0x00A0;       // load MO26 control register high
    CAN_MOCTR26L = 0x0000;       // load MO26 control register low

  ///  Configuration of Message Object 26 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x700

    CAN_MOAR26H = 0x5C00;        // load MO26 arbitration register high
    CAN_MOAR26L = 0x0000;        // load MO26 arbitration register low

  ///  Configuration of Message Object 26 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR26H = 0x3FFF;       // load MO26 acceptance mask register high
    CAN_MOAMR26L = 0xFFFF;       // load MO26 acceptance mask register low

  ///  Configuration of Message Object 26 interrupt pointer:
  ///  - use message pending register 0 bit position 26
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR26H = 0x0000;       // load MO26 interrupt pointer register high
    CAN_MOIPR26L = 0x1A00;       // load MO26 interrupt pointer register low

  ///  Configuration of Message Object 26 FIFO/Gateway pointer:

    CAN_MOFGPR26H = 0x0000;      // load MO26 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR26L = 0x0000;      // load MO26 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 26 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR26H = 0x0801;       // load MO26 function control register high
    CAN_MOFCR26L = 0x0000;       // load MO26 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 27:
  ///  -----------------------------------------------------------------------
  ///  - message object 27 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 28:
  ///  -----------------------------------------------------------------------
  ///  - message object 28 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 29:
  ///  -----------------------------------------------------------------------
  ///  - message object 29 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 30:
  ///  -----------------------------------------------------------------------
  ///  - message object 30 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 31:
  ///  -----------------------------------------------------------------------
  ///  - message object 31 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 32:
  ///  -----------------------------------------------------------------------
  ///  - message object 32 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 33:
  ///  -----------------------------------------------------------------------
  ///  - message object 33 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 34:
  ///  -----------------------------------------------------------------------
  ///  - message object 34 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 35:
  ///  -----------------------------------------------------------------------
  ///  - message object 35 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 36:
  ///  -----------------------------------------------------------------------
  ///  - message object 36 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 37:
  ///  -----------------------------------------------------------------------
  ///  - message object 37 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 38:
  ///  -----------------------------------------------------------------------
  ///  - message object 38 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 39:
  ///  -----------------------------------------------------------------------
  ///  - message object 39 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 40:
  ///  -----------------------------------------------------------------------
  ///  - message object 40 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 41:
  ///  -----------------------------------------------------------------------
  ///  - message object 41 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 42:
  ///  -----------------------------------------------------------------------
  ///  - message object 42 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 43:
  ///  -----------------------------------------------------------------------
  ///  - message object 43 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 44:
  ///  -----------------------------------------------------------------------
  ///  - message object 44 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 45:
  ///  -----------------------------------------------------------------------
  ///  - message object 45 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 46:
  ///  -----------------------------------------------------------------------
  ///  - message object 46 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 47:
  ///  -----------------------------------------------------------------------
  ///  - message object 47 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 48:
  ///  -----------------------------------------------------------------------
  ///  - message object 48 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 49:
  ///  -----------------------------------------------------------------------
  ///  - message object 49 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 50:
  ///  -----------------------------------------------------------------------
  ///  - message object 50 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 51:
  ///  -----------------------------------------------------------------------
  ///  - message object 51 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 52:
  ///  -----------------------------------------------------------------------
  ///  - message object 52 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 53:
  ///  -----------------------------------------------------------------------
  ///  - message object 53 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 54:
  ///  -----------------------------------------------------------------------
  ///  - message object 54 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 55:
  ///  -----------------------------------------------------------------------
  ///  - message object 55 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 56:
  ///  -----------------------------------------------------------------------
  ///  - message object 56 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 57:
  ///  -----------------------------------------------------------------------
  ///  - message object 57 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 58:
  ///  -----------------------------------------------------------------------
  ///  - message object 58 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 59:
  ///  -----------------------------------------------------------------------
  ///  - message object 59 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 60:
  ///  -----------------------------------------------------------------------
  ///  - message object 60 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 61:
  ///  -----------------------------------------------------------------------
  ///  - message object 61 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 62:
  ///  -----------------------------------------------------------------------
  ///  - message object 62 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 63:
  ///  -----------------------------------------------------------------------
  ///  - message object 63 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 64:
  ///  -----------------------------------------------------------------------
  ///  - message object 64 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 65:
  ///  -----------------------------------------------------------------------
  ///  - message object 65 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 66:
  ///  -----------------------------------------------------------------------
  ///  - message object 66 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 67:
  ///  -----------------------------------------------------------------------
  ///  - message object 67 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 68:
  ///  -----------------------------------------------------------------------
  ///  - message object 68 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 69:
  ///  -----------------------------------------------------------------------
  ///  - message object 69 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 70:
  ///  -----------------------------------------------------------------------
  ///  - message object 70 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 71:
  ///  -----------------------------------------------------------------------
  ///  - message object 71 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 72:
  ///  -----------------------------------------------------------------------
  ///  - message object 72 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 73:
  ///  -----------------------------------------------------------------------
  ///  - message object 73 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 74:
  ///  -----------------------------------------------------------------------
  ///  - message object 74 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 75:
  ///  -----------------------------------------------------------------------
  ///  - message object 75 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 76:
  ///  -----------------------------------------------------------------------
  ///  - message object 76 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 77:
  ///  -----------------------------------------------------------------------
  ///  - message object 77 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 78:
  ///  -----------------------------------------------------------------------
  ///  - message object 78 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 79:
  ///  -----------------------------------------------------------------------
  ///  - message object 79 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 80:
  ///  -----------------------------------------------------------------------
  ///  - message object 80 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 81:
  ///  -----------------------------------------------------------------------
  ///  - message object 81 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 82:
  ///  -----------------------------------------------------------------------
  ///  - message object 82 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 83:
  ///  -----------------------------------------------------------------------
  ///  - message object 83 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 84:
  ///  -----------------------------------------------------------------------
  ///  - message object 84 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 85:
  ///  -----------------------------------------------------------------------
  ///  - message object 85 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 86:
  ///  -----------------------------------------------------------------------
  ///  - message object 86 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 87:
  ///  -----------------------------------------------------------------------
  ///  - message object 87 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 88:
  ///  -----------------------------------------------------------------------
  ///  - message object 88 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 89:
  ///  -----------------------------------------------------------------------
  ///  - message object 89 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 90:
  ///  -----------------------------------------------------------------------
  ///  - message object 90 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 91:
  ///  -----------------------------------------------------------------------
  ///  - message object 91 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 92:
  ///  -----------------------------------------------------------------------
  ///  - message object 92 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 93:
  ///  -----------------------------------------------------------------------
  ///  - message object 93 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 94:
  ///  -----------------------------------------------------------------------
  ///  - message object 94 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 95:
  ///  -----------------------------------------------------------------------
  ///  - message object 95 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 96:
  ///  -----------------------------------------------------------------------
  ///  - message object 96 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 97:
  ///  -----------------------------------------------------------------------
  ///  - message object 97 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 98:
  ///  -----------------------------------------------------------------------
  ///  - message object 98 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 99:
  ///  -----------------------------------------------------------------------
  ///  - message object 99 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 100:
  ///  -----------------------------------------------------------------------
  ///  - message object 100 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 101:
  ///  -----------------------------------------------------------------------
  ///  - message object 101 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 102:
  ///  -----------------------------------------------------------------------
  ///  - message object 102 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 103:
  ///  -----------------------------------------------------------------------
  ///  - message object 103 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 104:
  ///  -----------------------------------------------------------------------
  ///  - message object 104 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 105:
  ///  -----------------------------------------------------------------------
  ///  - message object 105 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 106:
  ///  -----------------------------------------------------------------------
  ///  - message object 106 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 107:
  ///  -----------------------------------------------------------------------
  ///  - message object 107 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 108:
  ///  -----------------------------------------------------------------------
  ///  - message object 108 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 109:
  ///  -----------------------------------------------------------------------
  ///  - message object 109 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 110:
  ///  -----------------------------------------------------------------------
  ///  - message object 110 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 111:
  ///  -----------------------------------------------------------------------
  ///  - message object 111 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 112:
  ///  -----------------------------------------------------------------------
  ///  - message object 112 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 113:
  ///  -----------------------------------------------------------------------
  ///  - message object 113 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 114:
  ///  -----------------------------------------------------------------------
  ///  - message object 114 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 115:
  ///  -----------------------------------------------------------------------
  ///  - message object 115 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 116:
  ///  -----------------------------------------------------------------------
  ///  - message object 116 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 117:
  ///  -----------------------------------------------------------------------
  ///  - message object 117 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 118:
  ///  -----------------------------------------------------------------------
  ///  - message object 118 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 119:
  ///  -----------------------------------------------------------------------
  ///  - message object 119 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 120:
  ///  -----------------------------------------------------------------------
  ///  - message object 120 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 121:
  ///  -----------------------------------------------------------------------
  ///  - message object 121 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 122:
  ///  -----------------------------------------------------------------------
  ///  - message object 122 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 123:
  ///  -----------------------------------------------------------------------
  ///  - message object 123 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 124:
  ///  -----------------------------------------------------------------------
  ///  - message object 124 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 125:
  ///  -----------------------------------------------------------------------
  ///  - message object 125 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 126:
  ///  -----------------------------------------------------------------------
  ///  - message object 126 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 127:
  ///  -----------------------------------------------------------------------
  ///  - message object 127 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 128:
  ///  -----------------------------------------------------------------------
  ///  - message object 128 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 129:
  ///  -----------------------------------------------------------------------
  ///  - message object 129 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 130:
  ///  -----------------------------------------------------------------------
  ///  - message object 130 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 131:
  ///  -----------------------------------------------------------------------
  ///  - message object 131 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 132:
  ///  -----------------------------------------------------------------------
  ///  - message object 132 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 133:
  ///  -----------------------------------------------------------------------
  ///  - message object 133 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 134:
  ///  -----------------------------------------------------------------------
  ///  - message object 134 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 135:
  ///  -----------------------------------------------------------------------
  ///  - message object 135 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 136:
  ///  -----------------------------------------------------------------------
  ///  - message object 136 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 137:
  ///  -----------------------------------------------------------------------
  ///  - message object 137 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 138:
  ///  -----------------------------------------------------------------------
  ///  - message object 138 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 139:
  ///  -----------------------------------------------------------------------
  ///  - message object 139 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 140:
  ///  -----------------------------------------------------------------------
  ///  - message object 140 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 141:
  ///  -----------------------------------------------------------------------
  ///  - message object 141 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 142:
  ///  -----------------------------------------------------------------------
  ///  - message object 142 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 143:
  ///  -----------------------------------------------------------------------
  ///  - message object 143 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 144:
  ///  -----------------------------------------------------------------------
  ///  - message object 144 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 145:
  ///  -----------------------------------------------------------------------
  ///  - message object 145 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 146:
  ///  -----------------------------------------------------------------------
  ///  - message object 146 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 147:
  ///  -----------------------------------------------------------------------
  ///  - message object 147 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 148:
  ///  -----------------------------------------------------------------------
  ///  - message object 148 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 149:
  ///  -----------------------------------------------------------------------
  ///  - message object 149 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 150:
  ///  -----------------------------------------------------------------------
  ///  - message object 150 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 151:
  ///  -----------------------------------------------------------------------
  ///  - message object 151 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 152:
  ///  -----------------------------------------------------------------------
  ///  - message object 152 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 153:
  ///  -----------------------------------------------------------------------
  ///  - message object 153 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 154:
  ///  -----------------------------------------------------------------------
  ///  - message object 154 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 155:
  ///  -----------------------------------------------------------------------
  ///  - message object 155 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 156:
  ///  -----------------------------------------------------------------------
  ///  - message object 156 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 157:
  ///  -----------------------------------------------------------------------
  ///  - message object 157 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 158:
  ///  -----------------------------------------------------------------------
  ///  - message object 158 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 159:
  ///  -----------------------------------------------------------------------
  ///  - message object 159 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 160:
  ///  -----------------------------------------------------------------------
  ///  - message object 160 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 161:
  ///  -----------------------------------------------------------------------
  ///  - message object 161 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 162:
  ///  -----------------------------------------------------------------------
  ///  - message object 162 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 163:
  ///  -----------------------------------------------------------------------
  ///  - message object 163 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 164:
  ///  -----------------------------------------------------------------------
  ///  - message object 164 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 165:
  ///  -----------------------------------------------------------------------
  ///  - message object 165 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 166:
  ///  -----------------------------------------------------------------------
  ///  - message object 166 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 167:
  ///  -----------------------------------------------------------------------
  ///  - message object 167 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 168:
  ///  -----------------------------------------------------------------------
  ///  - message object 168 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 169:
  ///  -----------------------------------------------------------------------
  ///  - message object 169 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 170:
  ///  -----------------------------------------------------------------------
  ///  - message object 170 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 171:
  ///  -----------------------------------------------------------------------
  ///  - message object 171 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 172:
  ///  -----------------------------------------------------------------------
  ///  - message object 172 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 173:
  ///  -----------------------------------------------------------------------
  ///  - message object 173 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 174:
  ///  -----------------------------------------------------------------------
  ///  - message object 174 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 175:
  ///  -----------------------------------------------------------------------
  ///  - message object 175 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 176:
  ///  -----------------------------------------------------------------------
  ///  - message object 176 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 177:
  ///  -----------------------------------------------------------------------
  ///  - message object 177 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 178:
  ///  -----------------------------------------------------------------------
  ///  - message object 178 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 179:
  ///  -----------------------------------------------------------------------
  ///  - message object 179 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 180:
  ///  -----------------------------------------------------------------------
  ///  - message object 180 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 181:
  ///  -----------------------------------------------------------------------
  ///  - message object 181 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 182:
  ///  -----------------------------------------------------------------------
  ///  - message object 182 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 183:
  ///  -----------------------------------------------------------------------
  ///  - message object 183 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 184:
  ///  -----------------------------------------------------------------------
  ///  - message object 184 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 185:
  ///  -----------------------------------------------------------------------
  ///  - message object 185 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 186:
  ///  -----------------------------------------------------------------------
  ///  - message object 186 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 187:
  ///  -----------------------------------------------------------------------
  ///  - message object 187 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 188:
  ///  -----------------------------------------------------------------------
  ///  - message object 188 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 189:
  ///  -----------------------------------------------------------------------
  ///  - message object 189 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 190:
  ///  -----------------------------------------------------------------------
  ///  - message object 190 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 191:
  ///  -----------------------------------------------------------------------
  ///  - message object 191 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 192:
  ///  -----------------------------------------------------------------------
  ///  - message object 192 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 193:
  ///  -----------------------------------------------------------------------
  ///  - message object 193 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 194:
  ///  -----------------------------------------------------------------------
  ///  - message object 194 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 195:
  ///  -----------------------------------------------------------------------
  ///  - message object 195 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 196:
  ///  -----------------------------------------------------------------------
  ///  - message object 196 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 197:
  ///  -----------------------------------------------------------------------
  ///  - message object 197 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 198:
  ///  -----------------------------------------------------------------------
  ///  - message object 198 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 199:
  ///  -----------------------------------------------------------------------
  ///  - message object 199 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 200:
  ///  -----------------------------------------------------------------------
  ///  - message object 200 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 201:
  ///  -----------------------------------------------------------------------
  ///  - message object 201 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 202:
  ///  -----------------------------------------------------------------------
  ///  - message object 202 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 203:
  ///  -----------------------------------------------------------------------
  ///  - message object 203 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 204:
  ///  -----------------------------------------------------------------------
  ///  - message object 204 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 205:
  ///  -----------------------------------------------------------------------
  ///  - message object 205 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 206:
  ///  -----------------------------------------------------------------------
  ///  - message object 206 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 207:
  ///  -----------------------------------------------------------------------
  ///  - message object 207 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 208:
  ///  -----------------------------------------------------------------------
  ///  - message object 208 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 209:
  ///  -----------------------------------------------------------------------
  ///  - message object 209 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 210:
  ///  -----------------------------------------------------------------------
  ///  - message object 210 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 211:
  ///  -----------------------------------------------------------------------
  ///  - message object 211 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 212:
  ///  -----------------------------------------------------------------------
  ///  - message object 212 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 213:
  ///  -----------------------------------------------------------------------
  ///  - message object 213 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 214:
  ///  -----------------------------------------------------------------------
  ///  - message object 214 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 215:
  ///  -----------------------------------------------------------------------
  ///  - message object 215 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 216:
  ///  -----------------------------------------------------------------------
  ///  - message object 216 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 217:
  ///  -----------------------------------------------------------------------
  ///  - message object 217 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 218:
  ///  -----------------------------------------------------------------------
  ///  - message object 218 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 219:
  ///  -----------------------------------------------------------------------
  ///  - message object 219 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 220:
  ///  -----------------------------------------------------------------------
  ///  - message object 220 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 221:
  ///  -----------------------------------------------------------------------
  ///  - message object 221 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 222:
  ///  -----------------------------------------------------------------------
  ///  - message object 222 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 223:
  ///  -----------------------------------------------------------------------
  ///  - message object 223 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 224:
  ///  -----------------------------------------------------------------------
  ///  - message object 224 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 225:
  ///  -----------------------------------------------------------------------
  ///  - message object 225 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 226:
  ///  -----------------------------------------------------------------------
  ///  - message object 226 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 227:
  ///  -----------------------------------------------------------------------
  ///  - message object 227 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 228:
  ///  -----------------------------------------------------------------------
  ///  - message object 228 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 229:
  ///  -----------------------------------------------------------------------
  ///  - message object 229 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 230:
  ///  -----------------------------------------------------------------------
  ///  - message object 230 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 231:
  ///  -----------------------------------------------------------------------
  ///  - message object 231 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 232:
  ///  -----------------------------------------------------------------------
  ///  - message object 232 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 233:
  ///  -----------------------------------------------------------------------
  ///  - message object 233 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 234:
  ///  -----------------------------------------------------------------------
  ///  - message object 234 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 235:
  ///  -----------------------------------------------------------------------
  ///  - message object 235 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 236:
  ///  -----------------------------------------------------------------------
  ///  - message object 236 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 237:
  ///  -----------------------------------------------------------------------
  ///  - message object 237 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 238:
  ///  -----------------------------------------------------------------------
  ///  - message object 238 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 239:
  ///  -----------------------------------------------------------------------
  ///  - message object 239 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 240:
  ///  -----------------------------------------------------------------------
  ///  - message object 240 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 241:
  ///  -----------------------------------------------------------------------
  ///  - message object 241 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 242:
  ///  -----------------------------------------------------------------------
  ///  - message object 242 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 243:
  ///  -----------------------------------------------------------------------
  ///  - message object 243 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 244:
  ///  -----------------------------------------------------------------------
  ///  - message object 244 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 245:
  ///  -----------------------------------------------------------------------
  ///  - message object 245 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 246:
  ///  -----------------------------------------------------------------------
  ///  - message object 246 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 247:
  ///  -----------------------------------------------------------------------
  ///  - message object 247 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 248:
  ///  -----------------------------------------------------------------------
  ///  - message object 248 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 249:
  ///  -----------------------------------------------------------------------
  ///  - message object 249 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 250:
  ///  -----------------------------------------------------------------------
  ///  - message object 250 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 251:
  ///  -----------------------------------------------------------------------
  ///  - message object 251 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 252:
  ///  -----------------------------------------------------------------------
  ///  - message object 252 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 253:
  ///  -----------------------------------------------------------------------
  ///  - message object 253 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 254:
  ///  -----------------------------------------------------------------------
  ///  - message object 254 is not valid

  ///  -----------------------------------------------------------------------
  ///  Configuration of Service Request Nodes 0 - 15:
  ///  -----------------------------------------------------------------------
  ///  SRN0 service request node configuration:
  ///  - SRN0 interrupt priority level (ILVL) = 10
  ///  - SRN0 interrupt group level (GLVL) = 0
  ///  - SRN0 group priority extension (GPX) = 0

  CAN_0IC        =  0x0068;     


  //   -----------------------------------------------------------------------
  //   Start the CAN Nodes:
  //   -----------------------------------------------------------------------

  ///  - ------------- CAN_NCR0 ----------------------------------------------

    CAN_NCR0 &= ~ (uword) 0x0041; // reset INIT and CCE
  ///  - ------------- CAN_NCR1 ----------------------------------------------

    CAN_NCR1 &= ~ (uword) 0x0041; // reset INIT and CCE
  ///  - ------------- CAN_NCR2 ----------------------------------------------

    CAN_NCR2 &= ~ (uword) 0x0041; // reset INIT and CCE



  // USER CODE BEGIN (Init,3)

  // USER CODE END

} //  End of function CAN_vInit

//****************************************************************************
// @Function      void CAN_vGetMsgObj(ubyte ubObjNr, stCAN_SWObj *pstObj) 
//
//----------------------------------------------------------------------------
// @Description   This function fills the forwarded SW message object with 
//                the content of the chosen HW message object.
//                
//                For Receive Message object use function CAN_vReleaseObj, to 
//                release the message object. 
//                
//                The structure of the SW message object is defined in the 
//                header file CAN.h (see stCAN_SWObj).
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object to be read (0-254)
// @Parameters    *pstObj: 
//                Pointer on a message object to be filled by this function
//
//----------------------------------------------------------------------------
// @Date          2020/1/14
//
//****************************************************************************

// USER CODE BEGIN (GetMsgObj,1)

// USER CODE END

void CAN_vGetMsgObj(ubyte ubObjNr, stCAN_SWObj *pstObj)
{
  ubyte i;

  //----- get DLC -------------------------------------------------------
  pstObj->ubMOCfg = (ubyte)((CAN_HWOBJ[ubObjNr].uwMOFCRH & 0x0F00) >> 8); //MOFCRnH[11-8] DLC

  //----- get MODATA ----------------------------------------------------
  for(i = 0; i < pstObj->ubMOCfg; i++)
  {
    pstObj->ubData[i] = CAN_HWOBJ[ubObjNr].ubData[i];
  }

  //----- get DIR -------------------------------------------------------
    pstObj->ubMOCfg |= (ubyte)((CAN_HWOBJ[ubObjNr].uwMOCTRL & 0x0800) >> 7);  // set DIR if transmit object

  //----- get Identifier ------------------------------------------------
  if(CAN_HWOBJ[ubObjNr].uwMOARH & 0x2000)    // if extended identifier
  {
    //----- get Extended Identifier -------------------------------------
    pstObj->ulID = (((ulong)(CAN_HWOBJ[ubObjNr].uwMOARH & 0x1FFF))<<16) + CAN_HWOBJ[ubObjNr].uwMOARL;

    pstObj->ubMOCfg = pstObj->ubMOCfg | 0x20;  // set IDE
  }
  else                                       // standard identifier
  {
    //----- get Standard Identifier -------------------------------------
    pstObj->ulID = (CAN_HWOBJ[ubObjNr].uwMOARH & 0x1FFF) >> 2;
  }

  //----- get Acceptance Mask -----------------------------------------
  if(((CAN_HWOBJ[ubObjNr].uwMOARH & 0x2000) == 0) && (CAN_HWOBJ[ubObjNr].uwMOAMRH & 0x2000))    // if IDE = 0 & MIDE = 1
  {
    pstObj->ulMask = (CAN_HWOBJ[ubObjNr].uwMOAMRH & 0x1FFF) >> 2;
  }
  else
  {
    pstObj->ulMask = (((ulong)(CAN_HWOBJ[ubObjNr].uwMOAMRH & 0x1FFF))<<16) + CAN_HWOBJ[ubObjNr].uwMOAMRL;
  }

  //----- get Acceptance Mask bit ---------------------------------------
  pstObj->ubMOCfg |= (ubyte)((CAN_HWOBJ[ubObjNr].uwMOAMRH & 0x2000) >> 7); // set MIDE

  //----- get Frame Counter Value ---------------------------------------
  pstObj->uwCounter = CAN_HWOBJ[ubObjNr].uwMOIPRH;

} //  End of function CAN_vGetMsgObj

//****************************************************************************
// @Function      void CAN_vTransmit(ubyte ubObjNr) 
//
//----------------------------------------------------------------------------
// @Description   This function triggers the CAN controller to send the 
//                selected message.
//                If the selected message object is a TRANSMIT OBJECT then 
//                this function triggers the sending of a data frame. If 
//                however the selected message object is a RECEIVE OBJECT 
//                this function triggers the sending of a remote frame.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object (0-254)
//
//----------------------------------------------------------------------------
// @Date          2020/1/14
//
//****************************************************************************

// USER CODE BEGIN (Transmit,1)

// USER CODE END

void CAN_vTransmit(ubyte ubObjNr)
{

  CAN_HWOBJ[ubObjNr].uwMOCTRH = 0x0720;  // set TXRQ,TXEN0,TXEN1,MSGVAL

} //  End of function CAN_vTransmit

//****************************************************************************
// @Function      void CAN_vLoadData(ubyte ubObjNr, ubyte *ubpubData) 
//
//----------------------------------------------------------------------------
// @Description   If a hardware TRANSMIT OBJECT has to be loaded with data 
//                but not with a new identifier, this function may be used 
//                instead of the function CAN_vConfigMsgObj. The message 
//                object should be accessed by calling the function 
//                CAN_ubRequestMsgObj before calling this function. This 
//                prevents the CAN controller from working with invalid data.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object to be configured (0-254)
// @Parameters    *ubpubData: 
//                Pointer on a data buffer
//
//----------------------------------------------------------------------------
// @Date          2020/1/14
//
//****************************************************************************

// USER CODE BEGIN (LoadData,1)

// USER CODE END

void CAN_vLoadData(ubyte ubObjNr, ubyte *ubpubData)
{
  ubyte i;

  CAN_HWOBJ[ubObjNr].uwMOCTRH = 0x0008;       // set NEWDAT

  for(i = 0; i < (CAN_HWOBJ[ubObjNr].uwMOFCRH & 0x0F00) >> 8; i++)
  {
    CAN_HWOBJ[ubObjNr].ubData[i] = *(ubpubData++); //load MODATA
  }

  CAN_HWOBJ[ubObjNr].uwMOCTRH = 0x0020;       // set MSGVAL
  CAN_HWOBJ[ubObjNr].uwMOCTRL = 0x0040;       // reset RTSEL

} //  End of function CAN_vLoadData



//****************************************************************************
// @Macro         CAN_viSRN0() 
//
//----------------------------------------------------------------------------
// @Description   
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2020/1/14
//
//****************************************************************************

// USER CODE BEGIN (SRN0,1)
// USER CODE END

void CAN_viSRN0(void) interrupt CAN_SRN0INT
{

  uword uwSRN0ObjHandler;

  // USER CODE BEGIN (SRN0,2)
  	
  	uword i=0;
	uword temp =0;
	extern int time_out_remote; 
	extern int time_out_auto; 
	extern struct remote_receive remote_re;
	extern struct vehicle vehicle_rcv;
	extern struct self_driving auto_cmd;
	extern struct servo_breaking s_breaking;
	
  // USER CODE END

  CAN_MSIMASKH = 0x0479;          // set message index mask register
  CAN_MSIMASKL = 0x903F;

  while (CAN_MSID0 != 0x0020)
  {
    switch(CAN_MSID0){

    case 0: // message object 0 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[0].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 0 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ0,1)

            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ0,2)
		if (DEBUG ==FALSE)
			{
			vehicle_rcv.lfw.rpm = CAN_HWOBJ[0].ubData[1];
			vehicle_rcv.lfw.rpm<<=8;
			vehicle_rcv.lfw.rpm += CAN_HWOBJ[0].ubData[0] ;
			}
            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ0,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ0,4)

            // USER CODE END
          }

        }

        CAN_HWOBJ[0].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND0


      CAN_MSPND0H = ~(uword) 0x0000; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0001;

      // USER CODE BEGIN (SRN0_OBJ0,7)

      // USER CODE END

      break;


    case 1: // message object 1 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[1].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 1 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ1,1)
		if (DEBUG ==FALSE)
			{
				vehicle_rcv.lbw.rpm = CAN_HWOBJ[1].ubData[1];
				vehicle_rcv.lbw.rpm<<=8;
				vehicle_rcv.lbw.rpm += CAN_HWOBJ[1].ubData[0] ;
			}
            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ1,2)

            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ1,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ1,4)

            // USER CODE END
          }

        }

        CAN_HWOBJ[1].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND1


      CAN_MSPND0H = ~(uword) 0x0000; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0002;

      // USER CODE BEGIN (SRN0_OBJ1,7)

      // USER CODE END

      break;


    case 2: // message object 2 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[2].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 2 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ2,1)

            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ2,2)
			if (DEBUG ==FALSE)
			{
				vehicle_rcv.rfw.rpm = CAN_HWOBJ[2].ubData[1];
				vehicle_rcv.rfw.rpm<<=8;
				vehicle_rcv.rfw.rpm += CAN_HWOBJ[2].ubData[0] ;
			}
            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ2,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ2,4)

            // USER CODE END
          }

        }

        CAN_HWOBJ[2].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND2


      CAN_MSPND0H = ~(uword) 0x0000; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0004;

      // USER CODE BEGIN (SRN0_OBJ2,7)

      // USER CODE END

      break;


    case 3: // message object 3 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[3].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 3 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ3,1)

            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ3,2)
		if (DEBUG ==FALSE)
			{
			vehicle_rcv.rbw.rpm = CAN_HWOBJ[3].ubData[1];
			vehicle_rcv.rbw.rpm<<=8;
			vehicle_rcv.rbw.rpm += CAN_HWOBJ[3].ubData[0] ;
			}
            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ3,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ3,4)

            // USER CODE END
          }

        }

        CAN_HWOBJ[3].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND3


      CAN_MSPND0H = ~(uword) 0x0000; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0008;

      // USER CODE BEGIN (SRN0_OBJ3,7)

      // USER CODE END

      break;


    case 4: // message object 4 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[4].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 4 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ4,1)

            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ4,2)
			vehicle_rcv.front_steering.steering_velaus = CAN_HWOBJ[4].ubData[1];
			vehicle_rcv.front_steering.steering_velaus<<=8;
			vehicle_rcv.front_steering.steering_velaus += CAN_HWOBJ[4].ubData[0] ;

            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ4,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ4,4)

            // USER CODE END
          }

        }

        CAN_HWOBJ[4].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND4


      CAN_MSPND0H = ~(uword) 0x0000; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0010;

      // USER CODE BEGIN (SRN0_OBJ4,7)

      // USER CODE END

      break;


    case 5: // message object 5 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[5].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 5 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ5,1)
			vehicle_rcv.back_steering.steering_velaus = CAN_HWOBJ[5].ubData[1];
			vehicle_rcv.back_steering.steering_velaus<<=8;
			vehicle_rcv.back_steering.steering_velaus += CAN_HWOBJ[5].ubData[0] ;
            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ5,2)

            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ5,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ5,4)

            // USER CODE END
          }

        }

        CAN_HWOBJ[5].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND5


      CAN_MSPND0H = ~(uword) 0x0000; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0020;

      // USER CODE BEGIN (SRN0_OBJ5,7)

      // USER CODE END

      break;


    case 12: // message object 12 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[12].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 12 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ12,1)

            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ12,2)
			//数据清除
			remote_re.t_throttle_vle=0;
			remote_re.t_breaking_vle=0;
			remote_re.t_steering_vle=0;

			//get control velues 	 0x283
			remote_re.t_throttle_vle = CAN_HWOBJ[12].ubData[1];
			remote_re.t_throttle_vle <<=8;
			remote_re.t_throttle_vle += CAN_HWOBJ[12].ubData[0];
			//get control velues 
			remote_re.t_breaking_vle = CAN_HWOBJ[12].ubData[3];
			remote_re.t_breaking_vle <<=8;
			remote_re.t_breaking_vle += CAN_HWOBJ[12].ubData[2];
			//get control velues 
			remote_re.t_steering_vle = CAN_HWOBJ[12].ubData[5];
			remote_re.t_steering_vle <<=8;
			remote_re.t_steering_vle += CAN_HWOBJ[12].ubData[4];

			//挡位
			if((CAN_HWOBJ[12].ubData[6]>>6)==0x1) remote_re.t_gear = GEAR_D;	//0x06 
			else if((CAN_HWOBJ[12].ubData[6]>>6)==0x2) remote_re.t_gear = GEAR_N;  //0x0a
			else if((CAN_HWOBJ[12].ubData[6]>>6)==0x3) remote_re.t_gear = GEAR_R;  //0x0e
			else remote_re.t_gear = 0x0;
			//备用开关1
			if((CAN_HWOBJ[12].ubData[6]&0x03)==0x1) remote_re.t_backup1 = 1;	
			else if((CAN_HWOBJ[12].ubData[6]&0x03)==0x2) remote_re.t_backup1 = 2;  
			else if((CAN_HWOBJ[12].ubData[6]&0x03)==0x3) remote_re.t_backup1 = 3;  
			else remote_re.t_backup1 = 0x0;

			//转向模式
			if(((CAN_HWOBJ[12].ubData[6]>>2)&0x03)==0x1) remote_re.t_steering_mod = S_DIFF;
			else if(((CAN_HWOBJ[12].ubData[6]>>2)&0x03)==0x2) remote_re.t_steering_mod = S_NORM;
			else if(((CAN_HWOBJ[12].ubData[6]>>2)&0x03)==0x3) remote_re.t_steering_mod = S_SAME;
			 else remote_re.t_steering_mod = 0x0;

			//备用开关3
			if(((CAN_HWOBJ[12].ubData[6]>>4)&0x03)==0x1) remote_re.t_backup3 = 1; 
			else if(((CAN_HWOBJ[12].ubData[6]>>4)&0x03)==0x2) remote_re.t_backup3 = 2;  
			else if(((CAN_HWOBJ[12].ubData[6]>>4)&0x03)==0x3) remote_re.t_backup3 = 3;  
			else remote_re.t_backup3 = 0x0;

			//手/自动模式 
			if((CAN_HWOBJ[12].ubData[7]&0x01))  remote_re.t_way_trl = TRUE;  //自动驾驶模式	
			else   remote_re.t_way_trl = FALSE;	//遥控模式
			//急停
		 	if(CAN_HWOBJ[12].ubData[7]&0x02) remote_re.t_em_stop = TRUE;	//急停按钮触发
			 else remote_re.t_em_stop = FALSE;
			//舱门控制
			 if(CAN_HWOBJ[12].ubData[7]&0x04) remote_re.cabin_ctl = TRUE;	
			 else remote_re.cabin_ctl = FALSE;
			//手刹
			 if(CAN_HWOBJ[12].ubData[7]&0x08) remote_re.hand_break =   FALSE;	
			 else remote_re.hand_break =  TRUE;
			  //debug_hand_break1=FALSE;
			 //debug_hand_break1=CAN_HWOBJ[12].ubData[7] ;
			 //分离
			 if(CAN_HWOBJ[12].ubData[7]&0x10) remote_re.separate = TRUE;	
			 else remote_re.separate = FALSE;
			//自动对接
			 if(CAN_HWOBJ[12].ubData[7]&0x20) remote_re.auto_joint = TRUE;	
			 else remote_re.auto_joint = FALSE;
			//低速模式
			if(CAN_HWOBJ[12].ubData[7]&0x40) remote_re.low_speed_mod = TRUE;	
			 else remote_re.low_speed_mod = FALSE;
			//使能钥匙，遥控断链后会置位
			if(CAN_HWOBJ[12].ubData[7]&0x80) {remote_re.key = TRUE;}
			 else {remote_re.key = FALSE;	time_out_remote =0;}
            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ12,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ12,4)

            // USER CODE END
          }

        }

        CAN_HWOBJ[12].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND12


      CAN_MSPND0H = ~(uword) 0x0000; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x1000;

      // USER CODE BEGIN (SRN0_OBJ12,7)

      // USER CODE END

      break;


    case 15: // message object 15 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[15].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 15 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ15,1)
			
            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
			
            // USER CODE BEGIN (SRN0_OBJ15,2)

			auto_cmd.speed = CAN_HWOBJ[15].ubData[1];
			auto_cmd.speed <<=8;
			auto_cmd.speed += CAN_HWOBJ[15].ubData[0];

			//breaking
			auto_cmd.breaking = CAN_HWOBJ[15].ubData[3];
			auto_cmd.breaking <<=8;
			auto_cmd.breaking += CAN_HWOBJ[15].ubData[2];
			//steering
			auto_cmd.steering =CAN_HWOBJ[15].ubData[5];
			auto_cmd.steering<<=8;
			auto_cmd.steering +=CAN_HWOBJ[15].ubData[4];
			//挡位
			if((CAN_HWOBJ[15].ubData[6]>>6)==0x1) auto_cmd.gear = GEAR_D;
			else if((CAN_HWOBJ[15].ubData[6]>>6)==0x2) auto_cmd.gear = GEAR_N;
			else if((CAN_HWOBJ[15].ubData[6]>>6)==0x3) auto_cmd.gear = GEAR_R;
			else auto_cmd.gear = 0x0;
			//转向模式
			if((CAN_HWOBJ[15].ubData[6]&0x03)==0x1) auto_cmd.steering_mod = S_DIFF;
			else if((CAN_HWOBJ[15].ubData[6]&0x03)==0x2) auto_cmd.steering_mod = S_NORM;
			else if((CAN_HWOBJ[15].ubData[6]&0x03)==0x3) auto_cmd.steering_mod = S_SAME;
			else auto_cmd.steering_mod = 0x0;

			//手/自动模式 
			if((CAN_HWOBJ[15].ubData[7]&0x01))  auto_cmd.trun_laft = TRUE;  //左转向灯	
			else   auto_cmd.trun_laft = FALSE;	
			//急停
		 	if(CAN_HWOBJ[15].ubData[7]&0x02) auto_cmd.em_stop = TRUE;	//急停按钮触发
			 else auto_cmd.em_stop = FALSE;
			//右转向
			 if(CAN_HWOBJ[15].ubData[7]&0x04) auto_cmd.turn_right = TRUE;	
			 else auto_cmd.turn_right = FALSE;
			//手刹
			 if(CAN_HWOBJ[15].ubData[7]&0x08) auto_cmd.hand_break = TRUE;	
			 else auto_cmd.hand_break = FALSE;
			 //大灯	近光
			 if(CAN_HWOBJ[15].ubData[7]&0x10) auto_cmd.near_light = TRUE;	
			 else auto_cmd.near_light = FALSE;
			//远光灯
			 if(CAN_HWOBJ[15].ubData[7]&0x20) auto_cmd.fear_light = TRUE;	
			 else auto_cmd.fear_light = FALSE;
			//低速模式
			if(CAN_HWOBJ[15].ubData[7]&0x20) auto_cmd.low_speed_mod = TRUE;	
			 else auto_cmd.low_speed_mod = FALSE;
			//使能钥匙
		//	if(CAN_HWOBJ[15].ubData[7]&0x80) auto_cmd.key = TRUE;	
		//	 else auto_cmd.key = FALSE;

			time_out_auto=0;
            // USER CODE END
 
          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ15,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ15,4)

            // USER CODE END
          }

        }

        CAN_HWOBJ[15].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND15


      CAN_MSPND0H = ~(uword) 0x0000; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x8000;

      // USER CODE BEGIN (SRN0_OBJ15,7)

      // USER CODE END

      break;


    case 16: // message object 16 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[16].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 16 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ16,1)

            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ16,2)

            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ16,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ16,4)

            // USER CODE END
          }

        }

        CAN_HWOBJ[16].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND16


      CAN_MSPND0H = ~(uword) 0x0001; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0000;

      // USER CODE BEGIN (SRN0_OBJ16,7)

      // USER CODE END

      break;


    case 19: // message object 19 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[19].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 19 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ19,1)
		if (DEBUG ==TRUE)
			{
				vehicle_rcv.lfw.rpm = CAN_HWOBJ[19].ubData[1];
				vehicle_rcv.lfw.rpm<<=8;
				vehicle_rcv.lfw.rpm += CAN_HWOBJ[19].ubData[0] ;

			}
            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ19,2)

            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ19,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ19,4)

            // USER CODE END
          }

        }

        CAN_HWOBJ[19].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND19


      CAN_MSPND0H = ~(uword) 0x0008; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0000;

      // USER CODE BEGIN (SRN0_OBJ19,7)

      // USER CODE END

      break;


    case 20: // message object 20 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[20].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 20 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ20,1)
		if (DEBUG ==TRUE)
			{
				vehicle_rcv.lbw.rpm = CAN_HWOBJ[20].ubData[1];
				vehicle_rcv.lbw.rpm<<=8;
				vehicle_rcv.lbw.rpm += CAN_HWOBJ[20].ubData[0] ;
			}
            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ20,2)

            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ20,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ20,4)

            // USER CODE END
          }

        }

        CAN_HWOBJ[20].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND20


      CAN_MSPND0H = ~(uword) 0x0010; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0000;

      // USER CODE BEGIN (SRN0_OBJ20,7)

      // USER CODE END

      break;


    case 21: // message object 21 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[21].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 21 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ21,1)
		if (DEBUG ==TRUE)
			{
				vehicle_rcv.rfw.rpm = CAN_HWOBJ[21].ubData[1];
				vehicle_rcv.rfw.rpm<<=8;
				vehicle_rcv.rfw.rpm += CAN_HWOBJ[21].ubData[0] ;
			}
            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ21,2)

            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ21,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ21,4)

            // USER CODE END
          }

        }

        CAN_HWOBJ[21].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND21


      CAN_MSPND0H = ~(uword) 0x0020; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0000;

      // USER CODE BEGIN (SRN0_OBJ21,7)

      // USER CODE END

      break;


    case 22: // message object 22 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[22].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 22 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ22,1)
 		if (DEBUG ==TRUE)
			{
				vehicle_rcv.rbw.rpm = CAN_HWOBJ[22].ubData[1];
				vehicle_rcv.rbw.rpm<<=8;
				vehicle_rcv.rbw.rpm += CAN_HWOBJ[22].ubData[0] ;
			}
            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ22,2)

            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ22,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ22,4)

            // USER CODE END
          }

        }

        CAN_HWOBJ[22].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND22


      CAN_MSPND0H = ~(uword) 0x0040; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0000;

      // USER CODE BEGIN (SRN0_OBJ22,7)

      // USER CODE END

      break;


    case 26: // message object 26 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[26].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 26 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ26,1)
			//获取伺服控制状态值
			s_breaking.servo_rx_data[0] =  CAN_HWOBJ[22].ubData[0];
			s_breaking.servo_rx_data[1] =  CAN_HWOBJ[22].ubData[1];
			s_breaking.servo_rx_data[2] =  CAN_HWOBJ[22].ubData[2];
			s_breaking.servo_rx_data[3] =  CAN_HWOBJ[22].ubData[3];
			s_breaking.servo_rx_data[4] =  CAN_HWOBJ[22].ubData[4];
			s_breaking.servo_rx_data[5] =  CAN_HWOBJ[22].ubData[5];
			s_breaking.servo_rx_data[6] =  CAN_HWOBJ[22].ubData[6];
			s_breaking.servo_rx_data[7] =  CAN_HWOBJ[22].ubData[7];
            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ26,2)

            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ26,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ26,4)

            // USER CODE END
          }

        }

        CAN_HWOBJ[26].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND26


      CAN_MSPND0H = ~(uword) 0x0400; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0000;

      // USER CODE BEGIN (SRN0_OBJ26,7)

      // USER CODE END

      break;

    default:

      // USER CODE BEGIN (SRN0,3)

      // USER CODE END

      break;

    }  // end switch 

    // USER CODE BEGIN (SRN0,7)

    // USER CODE END

  }  // end of while CAN_MSID


  // USER CODE BEGIN (SRN0,15)

  // USER CODE END

} //  End of function CAN_viSRN0



// USER CODE BEGIN (CAN_General,10)

// USER CODE END

