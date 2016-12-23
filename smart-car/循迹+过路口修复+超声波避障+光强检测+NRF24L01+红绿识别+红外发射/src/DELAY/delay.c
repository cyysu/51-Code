//---包含头文件---//
#include  "delay.h"

/********************************************************************
* 名称 : Delay_1ms()
* 功能 : 延时子程序，延时时间为 1ms * x
* 输入 : x (延时一毫秒的个数)
* 输出 : 无
***********************************************************************/
void delay_ms(uint i)//1ms延时
{
	uint x,j;
	for(j=0;j<i;j++)
	for(x=0;x<=148;x++); 
}
/*******************************************************************************
* 函 数 名         : Delay1ms
* 函数功能		   : 延时2MS
* 输    入         : c
* 输    出         : 无
********************************************/
void  delay_2us(unsigned int us)	  // @11.0592
{

	for(;us>0;us--)
	  {
	 	_nop_();
	  }
}

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 108;
	j = 144;
	do
	{
		while (--j);
	} while (--i);
}

 void delay_us(uint z)			  //延时子函数
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=400;y>0;y--);
}


void delay(uint z)			  //延时子函数
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=114;y>0;y--);
}