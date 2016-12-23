#ifndef _common_H_
#define _common_H_

//---包含头文件---//
#include <STC12C5A60S2.H>
#include  <intrins.h>
#include  "stdio.h"	
//---重定义关键词---//

typedef unsigned int  uint16;
typedef unsigned int  UINT;
typedef unsigned int  uint;
typedef unsigned int  UINT16;
typedef unsigned int  WORD;
typedef unsigned int  word;
typedef int  int16;
typedef int  INT16;
typedef unsigned long  uint32;
typedef unsigned long  UINT32;
typedef unsigned long  DWORD;
typedef unsigned long  dword;
typedef long  int32;
typedef long  INT32;
typedef signed char  int8;
typedef signed char  INT8;
typedef unsigned char  byte;
typedef unsigned char  BYTE;
typedef unsigned char  uchar;
typedef unsigned char  uchar8;
typedef unsigned char  UINT8;
typedef unsigned char  uint8;
typedef unsigned char BOOL;
typedef unsigned char  u8;
typedef unsigned int   u16;
typedef unsigned long  u32;
#define BYTE  uchar 
#define WORD  uint

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif
//------关键字 宏定义-----------// 
#define FOSC 11059200L
#define pi 3.1415926 
//---声明常量---//

/* 直流电机管脚配置 */

sbit MOTOR_A_EN=P1^3;  
sbit MOTOR_A_CON1=P1^0;	   //IN1
sbit MOTOR_A_CON2=P1^1;	   //IN2
          
sbit MOTOR_B_CON1=P1^2;	   //IN3
sbit MOTOR_B_CON2=P1^5;	   //IN4
sbit MOTOR_B_EN=P1^4;
 
//---循迹端口---//
#define  xunji  P0 
 
/* NRF24L01管脚配置 */
sbit CE   = P2^0;  // Chip Enable pin signal (output)
sbit SCK  = P2^1;  // Master Out, Slave In pin (output)	 
sbit MISO = P2^2;  // Master In, Slave Out pin (input) 
sbit MOSI = P2^3;  // Serial Clock pin, (output)
sbit IRQ  = P3^2;  // Interrupt signal, from nRF24L01 (input)
sbit CSN  = P4^4;  // Slave Select pin, (output to CSN, nRF24L01)

/*蜂鸣器*/
sbit BEEP=P1^7;

/*按键定义*/
sbit K1=P2^7;
sbit K2=P2^6;
sbit K3=P2^5;
sbit K4=P2^4;
/*光强检测*/
sbit SCL=P4^6; //IIC时钟引脚定义
sbit SDA=P4^5;  //IIC数据引脚定义
//ADO 接GND

/**颜色传感器引脚定义**/  
//sbit out=P3^5;		//实际是接了P3^5
sbit s2=P2^4;         //TCS3200 S2 
sbit s3=P2^5;         //TCS3200 S3
					  //TCS3200 S0 模块内部默认上拉
					  //TCS3200 S1 模块内部默认上拉
					  //TCS3200 OE 模块内部接地
						  
/**温湿度传感器引脚定义**/  
sbit  DHT11_OUT = P1^6;	

/*红外发射控制定义*/
sbit control_send=P3^7;

/*超声波配置*/
sbit echo=P3^3;
sbit trig=P3^4;  //定义引脚

#endif