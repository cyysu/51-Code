#ifndef _COLOR_SENSOR_H
#define _COLOR_SENSOR_H

#include  "common.h"

 /*******************************************
* 函数名称: t0_init()
* 函数功能: 定时器0初始化 10ms     定时器1计数模式   P3.5
* 入口参数: 无
* 出口参数: 无
/********************************************/
void t0_init();
void Yanse();
extern  uint red_dat,green_dat,blue_dat;
#endif