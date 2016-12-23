#include "common.h"
#include "IR_control.h"
#include "Infrared_emission.h"
#include "delay.h"
#include "dth.h"
#include "uart.h"
/*
采集温度通过红外发送
*/

void IR_DH(void)
{
    uchar  t=0;
    uint  temp;	
	uchar k=0,i=0;
	Multiple_sendIRdata(1,0x00,0x45);//开启LED显示屏
	delay_ms(500);
	Multiple_sendIRdata(2,0xf2,0x12);//发送固定温度
	while(t<5)	
	{
		while(i<3)
		{
			k=0;
			temp=DHT11();
			k=temp&0x00ff;
			delay_ms(500);
			i++;
			
		}
		Multiple_sendIRdata(1,0xf2,k);//发送温度
//		Multiple_sendIRdata(1,0xf2,temp);//发送温度
		t++;
	}
	
}