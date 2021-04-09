//****************************************************************************
// 文件名: MC33993.H
// 功  能: SPI MC33993 读写程序的头文件
// 作  者: 刘佳
// 版  本: V1.0
// 日  期: 2008.06.
// 修  订:
// 说  明：
//****************************************************************************
#ifndef _MC33993_H_
#define _MC33993_H_
//============================================================================

//****************************************************************************
// @Defines		MC33993指令集
//****************************************************************************

// 设置 MC33993的片选信号对应的引脚
//****************************************************************************

//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************
 void Set_Command(unsigned char setbit_H,unsigned char setbit_L,ubyte CS);
 void SP_Wake_inter(unsigned char setbit_H,unsigned char setbit_L);
 void SG_Wake_inter(unsigned char setbit_H,unsigned char setbit_L);
 void SP_Wetting_Current(unsigned char setbit_H,unsigned char setbit_L);
 void SG_Wetting_Current(unsigned char setbit_H,unsigned char setbit_L,ubyte CS);
 void SP_Wetting_Current_timer(unsigned char setbit_H,unsigned char setbit_L);
 void SG_Wetting_Current_timer(unsigned char setbit_H,unsigned char setbit_L);
 void SP_Tri_state(unsigned char setbit_H,unsigned char setbit_L,ubyte CS);
 void SG_Tri_state(unsigned char setbit_H,unsigned char setbit_L,ubyte CS);
 void Analog_Select(unsigned char anchannal_H,unsigned char anchannal_L,ubyte CS);
 
//=========================================================================================
#endif  // ifndef _MC33993_H_
