//****************************************************************************
// 文件名: MC33993.C
// 功  能: 
// 作  者: 刘佳
// 版  本: V1.0
// 日  期: 2008.06.21
// 修  订:
// 说  明：
//****************************************************************************

//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

//****************************************************************************
// @Function      ubyte Set_Command(unsigned char setbit) 
//
//----------------------------------------------------------------------------
// @Description   设置SP接电源or接GND
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    setbit    SPn,setbit<=8
//
//----------------------------------------------------------------------------
// @Date          2008-6-21	 by liujia
//
//****************************************************************************
void Set_Command(ubyte setbit_C_H,ubyte setbit_C_L,ubyte CS)
{
    if(CS==1)
	{
  	CS_MC33993_1 = 1;

    delay(5);
	CS_MC33993_1 = 0;						//片选信号激活（‘0’有效）

	delay(5);
	
	U2C0_SSC_vSendData(0x01);			        //command					
	while(!U2C0_SSC_ubTxDataReady());						
	
	U2C0_SSC_vSendData(setbit_C_H); 
	while(!U2C0_SSC_ubTxDataReady());							
	
	U2C0_SSC_vSendData(setbit_C_L);		        //setbit:1:connect to Bat;  0:connect to GND
	while(!U2C0_SSC_ubTxDataReady());
			     								
	delay(120);
	CS_MC33993_1 = 1;						

	delay(2);
	}

	if(CS==2)
	{
  	CS_MC33993_2 = 1;

    delay(5);
	CS_MC33993_2 = 0;						//片选信号激活（‘0’有效）

	delay(5);
	
	U2C0_SSC_vSendData(0x01);			        //command					
	while(!U2C0_SSC_ubTxDataReady());						
	
	U2C0_SSC_vSendData(setbit_C_H); 
	while(!U2C0_SSC_ubTxDataReady());							
	
	U2C0_SSC_vSendData(setbit_C_L);		        //setbit:1:connect to Bat;  0:connect to GND
	while(!U2C0_SSC_ubTxDataReady());
			     								
	delay(120);
	CS_MC33993_2 = 1;						

	delay(2);
	}
}
//****************************************************************************
// @Function      ubyte Wake_inter_SP(unsigned char setbit) 
//
//----------------------------------------------------------------------------
// @Description   唤醒及中断位产生
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    setbit    SPn,setbit<=8
//
//----------------------------------------------------------------------------
// @Date          2008-6-21	 by liujia
//
//****************************************************************************
void SP_Wake_inter(unsigned char setbit_H,unsigned char setbit_L)
{
	CS_MC33993_1 = 1;

	delay(5);
	CS_MC33993_1 = 0;						//片选信号激活（‘0’有效）

	delay(5);
	
	U2C0_SSC_vSendData(0x02);				    //command
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(setbit_H);			    //setbit_H:没用	
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(setbit_L);			    //setbit:1:enable
	while(!U2C0_SSC_ubTxDataReady());

	delay(120);
	CS_MC33993_1 = 1;						

	delay(2);		 
 }
//****************************************************************************
// @Function      ubyte Wake_inter_SG(unsigned char setbit) 
//
//----------------------------------------------------------------------------
// @Description   唤醒及中断位产生
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    setbit    SGn,setbit<=16
//
//----------------------------------------------------------------------------
// @Date          2008-6-21	 by liujia
//
//****************************************************************************
void SG_Wake_inter(unsigned char setbit_H,unsigned char setbit_L)
{

	CS_MC33993_1 = 1;

	delay(5);
	CS_MC33993_1 = 0;						//片选信号激活（‘0’有效）

	delay(5);

	U2C0_SSC_vSendData(0x03);				    //command
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(setbit_H);			    //setbit:  1:enable
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(setbit_L);			    //setbit:  1:enable
	while(!U2C0_SSC_ubTxDataReady());

	delay(120);
	CS_MC33993_1 = 1;						

	delay(2);	

 }
//****************************************************************************
// @Function      ubyte Wetting_Current_SP(unsigned char setbit) 
//
//----------------------------------------------------------------------------
// @Description   湿性电流设置
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    setbit    SPn,setbit<=8
//
//----------------------------------------------------------------------------
// @Date          2008-6-21	 by liujia
//
//****************************************************************************
void SP_Wetting_Current(unsigned char setbit_H,unsigned char setbit_L)
{

	CS_MC33993_1 = 1;

	delay(5);
	CS_MC33993_1 = 0;						//片选信号激活（‘0’有效）

	delay(5);

	U2C0_SSC_vSendData(0x04);				    //command
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(setbit_H);			    //setbit_H:无用  
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(setbit_L);			    //setbit:  1:16mA 0:2mA
	while(!U2C0_SSC_ubTxDataReady());

	delay(120);
	CS_MC33993_1 = 1;						

	delay(2);

 }
//****************************************************************************
// @Function      ubyte Wetting_Current_SP(unsigned char setbit) 
//
//----------------------------------------------------------------------------
// @Description   湿性电流设置
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    setbit    SPn,setbit<=16
//
//----------------------------------------------------------------------------
// @Date          2008-6-21	 by liujia
//
//****************************************************************************
void SG_Wetting_Current(unsigned char setbit_H,unsigned char setbit_L,ubyte CS)
{
	if(CS==1)
   {
	CS_MC33993_1 = 1;

	delay(5);
	CS_MC33993_1 = 0;						//片选信号激活（‘0’有效）

	delay(5);

	U2C0_SSC_vSendData(0x05);				    //command
	while(!U2C0_SSC_ubTxDataReady());
    
	U2C0_SSC_vSendData(setbit_H);			    //setbit:  1:16mA 0:2mA
	while(!U2C0_SSC_ubTxDataReady());
    
	U2C0_SSC_vSendData(setbit_L);			    //setbit:  1:16mA 0:2mA
	while(!U2C0_SSC_ubTxDataReady());

	delay(120);
	CS_MC33993_1 = 1;						

	delay(2);
	   }

		if(CS==2)
   {
	CS_MC33993_2 = 1;

	delay(5);
	CS_MC33993_2 = 0;						//片选信号激活（‘0’有效）

	delay(5);

	U2C0_SSC_vSendData(0x05);				    //command
	while(!U2C0_SSC_ubTxDataReady());
    
	U2C0_SSC_vSendData(setbit_H);			    //setbit:  1:16mA 0:2mA
	while(!U2C0_SSC_ubTxDataReady());
    
	U2C0_SSC_vSendData(setbit_L);			    //setbit:  1:16mA 0:2mA
	while(!U2C0_SSC_ubTxDataReady());

	delay(120);
	CS_MC33993_2 = 1;						

	delay(2);
	   }
 }
//****************************************************************************
// @Function      ubyte Wetting_Current_timer_SP(unsigned char setbit) 
//
//----------------------------------------------------------------------------
// @Description   湿性电流定时设置
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    setbit    SPn,setbit<=8
//
//----------------------------------------------------------------------------
// @Date          2008-6-21	 by liujia
//
//****************************************************************************
void SP_Wetting_Current_timer(unsigned char setbit_H,unsigned char setbit_L)
{

	CS_MC33993_1 = 1;

	delay(5);
	CS_MC33993_1 = 0;						//片选信号激活（‘0’有效）

	delay(5);

	U2C0_SSC_vSendData(0x07);				    //command
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(setbit_H);			    //setbit:  1:enable 20ms
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(setbit_L);			    //setbit:  1:enable 20ms
	while(!U2C0_SSC_ubTxDataReady());

	delay(120);
	CS_MC33993_1 = 1;							

	delay(2);

 }
//****************************************************************************
// @Function      ubyte Wetting_Current_timer_SG(unsigned char setbit) 
//
//----------------------------------------------------------------------------
// @Description   湿性电流定时设置
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    setbit    SPn,setbit<=16
//
//----------------------------------------------------------------------------
// @Date          2008-6-21	 by liujia
//
//****************************************************************************
void SG_Wetting_Current_timer(unsigned char setbit_H,unsigned char setbit_L)
{

	CS_MC33993_1 = 1;

	delay(5);
	CS_MC33993_1 = 0;						//片选信号激活（‘0’有效）

	delay(5);

	U2C0_SSC_vSendData(0x08);				    //command
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(setbit_H);			    //setbit:  1:enable 20ms
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(setbit_L);			    //setbit:  1:enable 20ms
	while(!U2C0_SSC_ubTxDataReady());

	delay(120);
	CS_MC33993_1 = 1;						

	delay(2);

 }
//****************************************************************************
// @Function      ubyte Tri_state_SP(unsigned char setbit) 
//
//----------------------------------------------------------------------------
// @Description   高阻设置
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    setbit    SPn,setbit<=16
//
//----------------------------------------------------------------------------
// @Date          2008-6-21	 by liujia
//
//****************************************************************************
void SP_Tri_state(unsigned char setbit_H,unsigned char setbit_L,ubyte CS)
{
	 if(CS==1)
   {
	CS_MC33993_1 = 1;

	delay(5);
	CS_MC33993_1 = 0;						//片选信号激活（‘0’有效）

	delay(5);

	U2C0_SSC_vSendData(0x09);				    //command
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(setbit_H);			    //setbit:  1:高阻
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(setbit_L);			    //setbit:  1:高阻
	while(!U2C0_SSC_ubTxDataReady());
	
	delay(120);
	CS_MC33993_1 = 1;						

	delay(2);
		}

		 if(CS==2)
   {
	CS_MC33993_2 = 1;

	delay(5);
	CS_MC33993_2 = 0;						//片选信号激活（‘0’有效）

	delay(5);

	U2C0_SSC_vSendData(0x09);				    //command
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(setbit_H);			    //setbit:  1:高阻
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(setbit_L);			    //setbit:  1:高阻
	while(!U2C0_SSC_ubTxDataReady());
	
	delay(120);
	CS_MC33993_2 = 1;						

	delay(2);
		}
 }
//****************************************************************************
// @Function      ubyte Tri_state_SG(unsigned char setbit) 
//
//----------------------------------------------------------------------------
// @Description   高阻设置
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    setbit    SPn,setbit<=16
//
//----------------------------------------------------------------------------
// @Date          2008-6-21	 by liujia
//
//****************************************************************************
void SG_Tri_state(unsigned char setbit_H,unsigned char setbit_L,ubyte CS)
{
	if(CS==1)
	{
	CS_MC33993_1 = 1;

	delay(5);
	CS_MC33993_1 = 0;						//片选信号激活（‘0’有效）

	delay(5);

	U2C0_SSC_vSendData(0x0a);				    //command  0a
	while(!U2C0_SSC_ubTxDataReady());

	U2C0_SSC_vSendData(setbit_H);			    //setbit:  1:高阻
	while(!U2C0_SSC_ubTxDataReady());

	U2C0_SSC_vSendData(setbit_L);			    //setbit:  1:高阻
	while(!U2C0_SSC_ubTxDataReady());
	
	delay(120);
	CS_MC33993_1 = 1;						

	delay(2);
	}

		if(CS==2)
	{
	CS_MC33993_2 = 1;

	delay(5);
	CS_MC33993_2 = 0;						//片选信号激活（‘0’有效）

	delay(5);

	U2C0_SSC_vSendData(0x0a);				    //command  0a
	while(!U2C0_SSC_ubTxDataReady());

	U2C0_SSC_vSendData(setbit_H);			    //setbit:  1:高阻
	while(!U2C0_SSC_ubTxDataReady());

	U2C0_SSC_vSendData(setbit_L);			    //setbit:  1:高阻
	while(!U2C0_SSC_ubTxDataReady());
	
	delay(120);
	CS_MC33993_2 = 1;						

	delay(2);
	}

 }
//****************************************************************************
// @Function      ubyte Analog_Select(unsigned char setbit) 
//
//----------------------------------------------------------------------------
// @Description   模拟通道选择
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    setbit    SPn,setbit<=16
//
//----------------------------------------------------------------------------
// @Date          2008-6-21	 by liujia
//
//****************************************************************************
void Analog_Select(unsigned char anchannal_H,unsigned char anchannal_L,ubyte CS)
{
	 if(CS==1)
   {
	CS_MC33993_1 = 1;

	delay(5);
	CS_MC33993_1 = 0;						//片选信号激活（‘0’有效）

	delay(5);

	U2C0_SSC_vSendData(0x06);				    //command
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(anchannal_H);			//anchannal:选择用于模拟通道的输入，目前只能选择00，即无
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(anchannal_L);			//anchannal:选择用于模拟通道的输入，目前只能选择00，即无
	while(!U2C0_SSC_ubTxDataReady());
	
	delay(120);
	CS_MC33993_1 = 1;						

	delay(2);
	 }

	  if(CS==2)
   {
	CS_MC33993_2 = 1;

	delay(5);
	CS_MC33993_2 = 0;						//片选信号激活（‘0’有效）

	delay(5);

	U2C0_SSC_vSendData(0x06);				    //command
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(anchannal_H);			//anchannal:选择用于模拟通道的输入，目前只能选择00，即无
	while(!U2C0_SSC_ubTxDataReady());
	
	U2C0_SSC_vSendData(anchannal_L);			//anchannal:选择用于模拟通道的输入，目前只能选择00，即无
	while(!U2C0_SSC_ubTxDataReady());
	
	delay(120);
	CS_MC33993_2 = 1;						

	delay(2);
	 }

 }
