/***************************************
 DHT11ʹ�÷�������
 ʹ�õ�Ƭ��STC12c5a60s2
 ����11.0592M
 ���뻷�� Keil uVision4
 Ӳ�����ߣ�DHT11��2��out��P4.7 DHT11��1�Ž�vcc DHT11��4�Ž�gnd
 ʱ�䣺2014��1��9��
***************************************/
#include "dth.h"
#include  "delay.h"
#include  "uart.h"

uchar  U8FLAG;

/**************************************
100us����ʱ x(us)	 12t��Ƭ��
**************************************/
/*void Delay_1(uint j)
{      
	uchar i;
    for(;j>0;j--)
  	{ 	
		for(i=0;i<27;i++);
  	}
} */

/**************************************
ms����ʱ x(ms)	   1t��Ƭ��
**************************************/
void Delay18ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 194;
	k = 159;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

/**************************************
10us����ʱ 	   12t��Ƭ��
**************************************/
/*void Delay_10us(void)	  
{
	uchar i;
	i--;
	i--;
	i--;
	i--;
	i--;
	i--;
}*/
/**************************************
10us����ʱ 	   1t��Ƭ��
**************************************/
void Delay_10us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 24;
	while (--i);
}



/**************************************
��ȡ��ʪ���м䴦����
**************************************/	
uchar COM(void)
{
	uchar  i,U8temp;
	uchar  U8comdata;  
	for(i=0;i<8;i++)	   
	{
	
	    U8FLAG=2;	
    	while((!DHT11_OUT)&&U8FLAG++);
		Delay_10us();
	    Delay_10us();
		Delay_10us();
		U8temp=0;
	    if(DHT11_OUT)U8temp=1;		   //����ߵ�ƽU8temp=1  �͵�ƽU8temp=0
	    U8FLAG=2;
	    while((DHT11_OUT)&&U8FLAG++);		  
		if(U8FLAG==1)break;	           //��ʱ������forѭ��		 
		U8comdata<<=1;
		U8comdata|=U8temp;        
	 }
	 return(U8comdata);
}
/**************************************
//-----��ʪ�ȶ�ȡ�ӳ���-----------
//----�¶ȸ�8λ== U8T_data_H------
//----�¶ȵ�8λ== U8T_data_L------
//----ʪ�ȸ�8λ== U8RH_data_H-----
//----ʪ�ȵ�8λ== U8RH_data_L-----
//----У�� 8λ == U8checkdata-----
**************************************/
uint DHT11(void)
{
   uchar  str[6]={"      "};
   uchar  U8T_data_H_temp,U8T_data_L_temp;
   uchar  U8RH_data_H_temp,U8RH_data_L_temp;
   uchar  U8checkdata_temp;
   uchar  U8temp1;
   uint  value_DHT11;

   DHT11_OUT=0;						  //��������18ms 
   Delay18ms();
   DHT11_OUT=1;						  //�ͷ�����
 
   Delay_10us();
   Delay_10us();				  //������������������ ������ʱ20us
   Delay_10us();
   Delay_10us();
   DHT11_OUT=1;						  //������Ϊ���� �жϴӻ���Ӧ�ź� 
 	  
   if(!DHT11_OUT)		  			   //�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������
   {
	   U8FLAG=2;
	 	 
	   while((!DHT11_OUT)&&U8FLAG++);   //�жϴӻ����� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����
	   U8FLAG=2;
	 
	   while((DHT11_OUT)&&U8FLAG++);	  //�жϴӻ����� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
	 	 				   	
	   U8RH_data_H_temp=COM();	   //���ݽ���״̬
	   U8RH_data_L_temp=COM();
	   U8T_data_H_temp=COM();
	   U8T_data_L_temp=COM();
	  
	   U8checkdata_temp=COM();
	   DHT11_OUT=1;
	 
	   U8temp1=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);	 //����У�� 
	   if(U8temp1==U8checkdata_temp)
	   {
	   	  str[0]=U8RH_data_H_temp;
	   	  str[1]=U8RH_data_L_temp;
		  str[2]=U8T_data_H_temp;
	   	  str[3]=U8T_data_L_temp;
	   	  str[4]=U8checkdata_temp;
		  value_DHT11=U8RH_data_H_temp*256+U8T_data_H_temp;
		  return(value_DHT11);
	   }
	   else return(0);										
   }
   else return(0);

}