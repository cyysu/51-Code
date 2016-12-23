#include "led.h"
#include "type.h"
#include <STC12C5A60S2.H>
#include <intrins.h>

sbit LED_SCK = P0^2;    		  //74HC595显示控制		  led
sbit LED_SER = P0^7;
sbit LED_rck= P0^1;

uchar SMG_D[]={0x03,0x9f,0x25,0x0d,0x99,0x49,0x41,0x1f,0x01,0x09,0xff}; //共阳数码管段码 0123456789_
uchar LED_BUF[10] = {0xFF,0xFF,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE};//LED显示数组 012345678 0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x00  

/******************************
			延时函数
******************************/
void SMG_delay(int n){ //LCD专用延时函数
  int i,j;
	if(n<0)              //10us延时
	{ 
		  for(i=2;i>0;i--);
			return; 
	} 
	if(n== 0) 						//200us延时
	{  
		 for(i=1;i>0;i--)
        for(j=88;j>0;j--);
		 return; 
	} 
  for(;n;n--)						//n毫秒延时
	{ 	  
			for(i=4;i>0;i--)
        for(j=113;j>0;j--);   
  } 
}

/******************************
W595写数据函数,用于两个595级联的情况
******************************/
void W_595(uchar dat1)  //dat1写到第一个595，dat2写到第二个595
{
    uchar i=0,j=0;
	  SCK=0;
	  rck=0;
	  for(i=0;i<8;i++)	   //写入dat2
	  {
		    SCK=0;
		    SER=dat1&0x80;
		    dat1<<=1;				
		    SCK=1;
	  }
	  rck=0;     //给LATCH端一个上升沿，锁存输出，两个595即输出dat1和dat2
      _nop_();	   //要求的时间为几十纳秒
	  _nop_();		
      rck=1;		
}  	

 void LED_show(uchar n)//第 n盏灯亮
{
	uchar temp,i;
	temp=0x7f;
	for(i=1;i<n;i++)
   {
      temp=temp>>1|0x80;
	}
    W_595(temp); 

}
