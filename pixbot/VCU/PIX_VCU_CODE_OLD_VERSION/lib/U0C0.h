//****************************************************************************
// @Module        Universal Serial Interface Channel (USIC) U0C0
// @Filename      U0C0.h
// @Project       tiaoshi.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains all function prototypes and macros for 
//                the U0C0 module.
//
//----------------------------------------------------------------------------
// @Date          2020/1/14 16:27:47
//
//****************************************************************************

// USER CODE BEGIN (U0C0_Header,1)

// USER CODE END



#ifndef _U0C0_H_
#define _U0C0_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (U0C0_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (U0C0_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

//   This parameter identifies U0C0 IIC 7-bit addressing mode
#define ADR7 0

//   This parameter identifies U0C0 IIC 10-bit addressing mode
#define ADR10 1

// Definition of U0C0 IIC WRITE/READ mode
#define U0C0IIC_WRITE    0
#define U0C0IIC_READ     1

// Definition of bits in U0C0_PSR
#define U0C0IIC_SLSEL     0x0001
#define U0C0IIC_WTDF      0x0002
#define U0C0IIC_SCR       0x0004
#define U0C0IIC_RSCR      0x0008
#define U0C0IIC_PCR       0x0010
#define U0C0IIC_NACK      0x0020
#define U0C0IIC_ARL       0x0040
#define U0C0IIC_SRR       0x0080
#define U0C0IIC_ERR       0x0100
#define U0C0IIC_TBIF      0x2000
#define U0C0IIC_RIF       0x4000

// Definition of bits in U0C0_PCRH
#define U0C0IIC_ACK00     0x0001
#define U0C0IIC_STIM      0x0002
#define U0C0IIC_SACKDIS   0x0200

// Definition of valid TDFs
#define U0C0TDF_MTxData     0x00
#define U0C0TDF_STxData     0x01
#define U0C0TDF_MRxAck0     0x02
#define U0C0TDF_MRxAck1     0x03
#define U0C0TDF_MStart      0x04
#define U0C0TDF_MRStart     0x05
#define U0C0TDF_MStop       0x06

#define uwFFFFU0C0        0xFFFF

// USER CODE BEGIN (U0C0_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (U0C0_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (U0C0_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (U0C0_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void U0C0_IIC_vInit(void);
void U0C0_IIC_vWriteData(uword uwTDF, uword uwData);
uword U0C0_IIC_uwReadData(void);


// USER CODE BEGIN (U0C0_Header,8)

// USER CODE END


//****************************************************************************
// @Macro         U0C0_IIC_vSlaveAddrFormat(Addr)
//
//----------------------------------------------------------------------------
// @Description   Important: Use this macro only for 7 bit address.
//                This macro is used to left shift the slave address by 1
//                and stores the left shifted address in Addr variable.
//                The 7 bit address in the slave device resides in the sfr
//                PCRL[15:9]. To select the slave device, user has to shift the 
//                address by 1 and transmit it from master with start(TDF).
//                Please refer User Manual for the detailed explanation.
//
//                Example:
//                if 7 bit slave address is 0x17 at PCRL[15:9] of slave device,
//                user has to transmit 0x2E (0x17 << 1) to select this slave.
//
//                Now user can use this macro with other functions,
//                U0C0_IIC_vWriteData(U0C0TDF_MStart, U0C0_IIC_vSlaveAddrFormat(Addr) + U0C0IIC_WRITE);
//                U0C0_IIC_vMasterTransmit(U0C0_IIC_vSlaveAddrFormat(uwDeviceAddr), uwSubAddr, *uwTxBuffer, uwBufferSize, uwAddrMode);
//                U0C0_IIC_vMasterReceive(U0C0_IIC_vSlaveAddrFormat(uwDeviceAddr), uwSubAddr, *uwRxBuffer, uwBufferSize, uwAddrMode);
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    Slave address
//
//----------------------------------------------------------------------------
// @Date          2020/1/14
//
//****************************************************************************

#define U0C0_IIC_vSlaveAddrFormat(Addr) (Addr <<=  1)

//****************************************************************************
// @Interrupt Vectors
//****************************************************************************



// USER CODE BEGIN (U0C0_Header,9)

// USER CODE END


#endif  // ifndef _U0C0_H_
