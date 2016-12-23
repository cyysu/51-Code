#ifndef __Car_Control_H
#define __Car_Control_H

//---包含头文件---//
#include  "common.h"

//---声明函数---//
#define MOTOR_GO_FORWARD   MOTOR_A_CON1= 1;MOTOR_A_CON2=0;MOTOR_B_CON1=1;MOTOR_B_CON2=0; //车体前进                                
#define MOTOR_GO_BACK	   MOTOR_A_CON1=0;MOTOR_A_CON2=1;MOTOR_B_CON1=0;MOTOR_B_CON2=1; //车体后退
#define MOTOR_GO_RIGHT	   MOTOR_A_CON1=0;MOTOR_A_CON2=1;MOTOR_B_CON1=1;MOTOR_B_CON2=0;//车体右转
#define MOTOR_GO_LEFT	   MOTOR_A_CON1=1;MOTOR_A_CON2=0;MOTOR_B_CON1=0;MOTOR_B_CON2=1;//车体左转
#define MOTOR_GO_STOP	   MOTOR_A_CON1=0;MOTOR_A_CON2=0;MOTOR_B_CON1=0;MOTOR_B_CON2=0; //车体停止

void Car_Init(void);
void FollowLine(void);
void Car_Check(void);
#endif 