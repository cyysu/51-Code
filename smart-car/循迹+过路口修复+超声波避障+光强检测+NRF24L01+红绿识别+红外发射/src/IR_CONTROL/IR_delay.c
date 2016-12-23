#include <STC12C5A60S2.H>
#include "IR_delay.h"
#include <intrins.h>
void Delay560us()    	//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 7;
	j = 1;
	do
	{
		while (--j);
	} while (--i);
}

void Delay1693us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 19;
	j = 50;
	do
	{
		while (--j);
	} while (--i);
}

void Delay9ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 97;
	j = 206;
	do
	{
		while (--j);
	} while (--i);
}

void Delay4500us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 49;
	j = 101;
	do
	{
		while (--j);
	} while (--i);
}
