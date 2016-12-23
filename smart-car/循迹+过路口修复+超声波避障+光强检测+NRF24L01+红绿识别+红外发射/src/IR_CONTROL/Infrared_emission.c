#include "Infrared_emission.h"
#include "IR_delay.h"
#include "delay.h"

 void SendIRdata_BYTE(unsigned char irdata)
 {
      unsigned char i;
	 for(i=0;i<8;i++)
	 {	
	     control_send=0;  //先发送0.56ms的38KHZ红外波（即编码中0.56ms的高电平）
	 	 Delay560us();
	  //停止发送红外信号（即编码中的低电平）
		if(irdata&1)      //判断最低位为1还是0。   低位先发送！！
	 	 { control_send=1;  //1为宽电平，1.693ms
	 	  Delay1693us();}
		else {control_send=1;  //0为窄电平，0.56ms
	 	      Delay560us();}
	     irdata=irdata>>1;     
    }
}

/*
g_iraddr1:地址
p_irdata：发送的数据
*/
void SendIRdata(unsigned char g_iraddr1,unsigned char p_irdata)
{
   //发送9ms的起始码，高电平有38KHZ载波
	control_send=0; 
    Delay9ms();
   //发送4.5ms的结果码，低电平无38KHZ载波
  control_send=1; 
	Delay4500us();
	
//	0x55   0101 0101
//  0xaa   1010 1010
	//发送十六位地址
	SendIRdata_BYTE(g_iraddr1);
	SendIRdata_BYTE(~g_iraddr1);
    //发送8位数据
	SendIRdata_BYTE(p_irdata);
    //发送8位数据的反码
	SendIRdata_BYTE(~p_irdata);
   
  control_send=0; 
	   Delay560us();
	control_send=1; 
} 
 /*
count  ：    发送的次数
ir_adress:   红外数据接收/发送的地址
dat：        发送的数据
*/
void Multiple_sendIRdata(u8 count,u8 ir_adress,u8 dat)
{
			uchar i;
			for(i=0;i<count;i++)
			{
		    SendIRdata(ir_adress,dat);//发送数据
			Delay500ms();	//@11.0592MHz
			}
} 
 
 
