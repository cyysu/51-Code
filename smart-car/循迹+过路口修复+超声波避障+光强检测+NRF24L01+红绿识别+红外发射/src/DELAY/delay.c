//---����ͷ�ļ�---//
#include  "delay.h"

/********************************************************************
* ���� : Delay_1ms()
* ���� : ��ʱ�ӳ�����ʱʱ��Ϊ 1ms * x
* ���� : x (��ʱһ����ĸ���)
* ��� : ��
***********************************************************************/
void delay_ms(uint i)//1ms��ʱ
{
	uint x,j;
	for(j=0;j<i;j++)
	for(x=0;x<=148;x++); 
}
/*******************************************************************************
* �� �� ��         : Delay1ms
* ��������		   : ��ʱ2MS
* ��    ��         : c
* ��    ��         : ��
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

 void delay_us(uint z)			  //��ʱ�Ӻ���
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=400;y>0;y--);
}


void delay(uint z)			  //��ʱ�Ӻ���
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=114;y>0;y--);
}