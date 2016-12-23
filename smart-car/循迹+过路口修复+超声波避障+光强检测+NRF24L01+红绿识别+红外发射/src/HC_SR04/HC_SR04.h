#ifndef _HC_SR04_H_
#define _HC_SR04_H_

//---包含头文件---//
#include  "common.h"

//---声明函数---//
void  Start_hc_sr04();
void Stop_hc_sr04();
float Conut(void) ;
float ultrasound_check();
void HC_SR();
//---声明变量---//
//extern  float f ;
extern  u8 sr04_over_flag;
extern u8 ultra_check_flag;
//u8 ultra_check_flag = 0 ; 
//u8 sr04_over_flag  = 0 ;  
#endif 