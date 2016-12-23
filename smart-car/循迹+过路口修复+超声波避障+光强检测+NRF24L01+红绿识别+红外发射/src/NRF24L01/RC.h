#ifndef _IR_RC_H_
#define _IR_RC_H_
#include "common.h"
//      光照等级
#define Light_1  1
//1等        1D    49 68 
#define Light_2  2
// 2等       2D    50 68  
#define Light_3  3
//3等        3D    51 68 
#define Light_4  5
//4等        4D    52 68 
#define ZhaDa  6
//闸道       TQ    84 81 
#define Alert_led  7
// 警灯      BJ    66 68 
#define  Tunnel    	8
/*警示灯	 PF	   48 69*/
extern uchar Repeat_count;
void NRF24L01_FindMyself(void);
void NRF24L01_transmit(uchar cmd);
#endif