#ifndef __Timer_H
#define __Timer_H

//---包含头文件---//
#include  "common.h"


//---声明函数---//
void InitTimer0();
void InitTimer1();
void server_T0();

//---声明变量---//
//--------------------------------------//
//     T0/1_MD = 0  方式0   13位计数器
//		 	   1  方式1   16位计数器
//			   2  方式2 （8位自动重载） 可作为波特率发生器
//         T0  3  方式3   T0用作两个8位计数器 标志位为TF0 TF1
//		   T1	  方式3   只能作为波特率发生器
//----------------------------------------//
#define T0_MD 1		   //  设置T0 工作模式 
#define T1_MD 1	   //  设置T1 工作模式 
#define TIMER0_REGULAR  1000L			   //定时单位为 us
#define TIMER1_REGULAR  1000L			   //定时单位为 us

extern volatile u8 ultra_check_flag ;
//extern volatile float f ;
extern volatile u8 sr04_over_flag;


#endif 