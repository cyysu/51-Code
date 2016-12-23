#ifndef _uart_H_
#define _uart_H_

//---包含头文件---//
#include  "common.h"

//---声明函数---//
void InitUart();
void u8_SendData(u8 dat);
void u8Data_uart(u8 dat);
void u16Data_uart(u16 dat);
void PC_printf_uart(u16 num,u16 dat);
void UART_u8(uchar *p,uchar length) ;

void UartInit(void);    //19200bps@11.0592MHz
void uart_senddata(uchar ch);//向串口发送数据
void uart_BYTE (uchar *p,uchar length);
//--------------------------------------//
//	 URMD = 0  使用定时器2 作为波特率发生器
//			1  使用定时器1模式0 （16位自动重载）作为波特率发生器
//			2  使用定时器1模式2 （8位自动重载）作为波特率发生器
//----------------------------------------//
#define BAUD 9600

#define PARITYBIT  NONE_PARITY  // 选择工作模式	 校验方式

#define NONE_PARITY  0      //无校验位
#define ODD_PARITY   1   	//奇校验位
#define EVEN_PARITY  2   	//偶校验位
#define MARK_PARITY  3   
#define SPACE_PARITY 4
  
#endif 
