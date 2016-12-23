#ifndef _1602_h
#define _1602_h

#include "commom.h"



void lcd_delay(int n); //LCD专用延时函数
void lcd_B(char f, uchar c, char t); //控制四线式接口LCD的7个脚
void lcd_init();//LCD1602 初始化
void lcd_cls(); //清屏
void lcd_cur0(); //隐藏光标
void lcd_goto1(uchar x);//设置DDRAM地址,第1行x位
void lcd_goto2(uchar x);//设置DDRAM地址,第2行x位
void lcd_putc(uchar d);//字符输出
void lcd_puts(uchar *s); //字串输出


#endif