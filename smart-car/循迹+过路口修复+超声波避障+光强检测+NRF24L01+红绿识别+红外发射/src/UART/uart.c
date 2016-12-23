#include  "uart.h"
#include  "delay.h"
// 8EH AUXR  T0x12 T1x12 UART_12/2 T2R T2_C/T T2x12 EXTRAN  S1ST2 
//    		   0	 1	   0		0	  0		 0	  0		  0
//------初始化串口------//
void InitUart()
{
/*
**选择工作模式
*/
// 98H SCON  SM0  SM1 SM2 REN TB8 RB8 TI RI 
//		0X50   0   1   0  1   0   0   0  0
//		0XDA   1   1   0  1	  1	  0	  1	 0
//		0XD2   1   1   0  1	  0	  0	  1	 0
#if(PARITYBIT == NONE_PARITY) //8位 可变波特率
   SCON = 0x50 ;	//工作方式1 8位 
#elif(PARITYBIT == ODD_PARITY)||(PARITYBIT == EVEN_PARITY)||(PARITYBIT == MARK_PARITY)
   SCON = 0Xda ;	//工作方式3 9位  包含一位校验位
#elif(PARITYBIT == SPACE_PARITY)
   SCON = 0XD2 ;    //工作方式3 9位  
#endif 
////**设置波特率  使用独立波特率发生器 	 //9600bps@11.0592MHz
	PCON &= 0x7F;		//波特率不倍速

	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
	BRT = 0xDC;		    //设定独立波特率发生器重装值
	AUXR |= 0x01;		//串口1选择独立波特率发生器为波特率发生器
	AUXR |= 0x10;		//启动独立波特率发生器
/*
////**设置波特率  使用定时器1作为波特率发生器 
////*/
//////--------------------设定定时器1为8位自动重装方式-----------------------------//
////	PCON |= 0x80;		//使能波特率倍速位SMOD	 BAUD= 2^SMOD/32 * T1 溢出率
////	AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
////	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
////	TMOD &= 0x0F;		//清除定时器1模式位
////	TMOD |= 0x20;		////设置计数器工作方式2 定时器1为8位自动重装方式	
////	TH1=(256-FOSC/16/12/BAUD); //计数器初始值设置，注意波特率是4800的
////	TL1=(256-FOSC/16/12/BAUD);
////	ET1 = 0;		//禁止定时器1中断
////	TR1 = 1;		//启动定时?
}

//-----发送串口数据--------//
void u8_SendData(u8 dat)
{
  SBUF = dat ;
  while(!TI);		 //TI=0时等待  ;  TI=1 写入新数据（TI=1 SBUF空闲）
  TI = 0;
}
//-----0-256发送串口数据--------//
void u8Data_uart(u8 dat)
{
	u8_SendData('0'+dat%1000/100);
	u8_SendData('0'+dat%100/10);
	u8_SendData('0'+dat%10);
	u8_SendData(0x0d);
}
//-----0-65535发送串口数据--------//
void u16Data_uart(u16 dat)
{
	u8_SendData('0'+dat%100000/10000);
	u8_SendData('0'+dat%10000/1000);
	u8_SendData('0'+dat%1000/100);
	u8_SendData('0'+dat%100/10);
	u8_SendData('0'+dat%10);
	u8_SendData(0x0d);
}
//-----t通过串口 在PC端显示 指定输入值 dat-------//
/**************编程知识****************************/
//在Keil C51中用printf输出一个单字节变量时要使用%bd
//b h l 定义输出长度分别为8位 16位 32位
//%d 有符号十进制输出 %u 无符号十进制输出 %c 字符输出	
//在keil中 使用printf 向PC传送数据时 需要对 TI置1 （串口）
/**************************************************/    
void PC_printf_uart(u16 num,u16 dat)
{
  	     TI = 1	;		
	     printf("num%hu:%hu \n",num,dat) ;
		 while(!TI) ;		//等待1字节发送完成
	     TI = 0 ;
}

void Uart_u8(uchar *p,uchar length)
{
	  while(length!=0)
	  {
	  	u8_SendData(*p);
		p++;
		length--;
	  }
}





void UartInit(void)		//9600bps@11.0592MHz
{
  PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
	BRT = 0xDC;		//设定独立波特率发生器重装值
	AUXR |= 0x01;		//串口1选择独立波特率发生器为波特率发生器
	AUXR |= 0x10;		//启动独立波特率发生器
  TI=1;
}


void uart_senddata(uchar ch)//向串口发送数据
{

   SBUF=ch;
   while(TI==0); //等待发送完成
	TI=0;
}

void uart_BYTE (uchar *p,uchar length)
{
	  while(length!=0)
	  {
	  	uart_senddata(*p);
		p++;
		length--;
	  }
}


