/***************************************
 DHT11使用范例程序
 使用单片机STC12c5a60s2
 晶振：11.0592M
 编译环境 Keil uVision4
 硬件接线：DHT11的2脚out接P4.7 DHT11的1脚接vcc DHT11的4脚接gnd
 时间：2014年1月9日
***************************************/
#include "dth.h"
#include  "delay.h"
#include  "uart.h"

uchar  U8FLAG;

/**************************************
100us级延时 x(us)	 12t单片机
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
ms级延时 x(ms)	   1t单片机
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
10us级延时 	   12t单片机
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
10us级延时 	   1t单片机
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
读取温湿度中间处理函数
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
	    if(DHT11_OUT)U8temp=1;		   //如果高电平U8temp=1  低电平U8temp=0
	    U8FLAG=2;
	    while((DHT11_OUT)&&U8FLAG++);		  
		if(U8FLAG==1)break;	           //超时则跳出for循环		 
		U8comdata<<=1;
		U8comdata|=U8temp;        
	 }
	 return(U8comdata);
}
/**************************************
//-----温湿度读取子程序-----------
//----温度高8位== U8T_data_H------
//----温度低8位== U8T_data_L------
//----湿度高8位== U8RH_data_H-----
//----湿度低8位== U8RH_data_L-----
//----校验 8位 == U8checkdata-----
**************************************/
uint DHT11(void)
{
   uchar  str[6]={"      "};
   uchar  U8T_data_H_temp,U8T_data_L_temp;
   uchar  U8RH_data_H_temp,U8RH_data_L_temp;
   uchar  U8checkdata_temp;
   uchar  U8temp1;
   uint  value_DHT11;

   DHT11_OUT=0;						  //主机拉低18ms 
   Delay18ms();
   DHT11_OUT=1;						  //释放总线
 
   Delay_10us();
   Delay_10us();				  //总线由上拉电阻拉高 主机延时20us
   Delay_10us();
   Delay_10us();
   DHT11_OUT=1;						  //主机设为输入 判断从机响应信号 
 	  
   if(!DHT11_OUT)		  			   //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行
   {
	   U8FLAG=2;
	 	 
	   while((!DHT11_OUT)&&U8FLAG++);   //判断从机发出 80us 的低电平响应信号是否结束
	   U8FLAG=2;
	 
	   while((DHT11_OUT)&&U8FLAG++);	  //判断从机发出 80us 的高电平，如发出则进入数据接收状态
	 	 				   	
	   U8RH_data_H_temp=COM();	   //数据接收状态
	   U8RH_data_L_temp=COM();
	   U8T_data_H_temp=COM();
	   U8T_data_L_temp=COM();
	  
	   U8checkdata_temp=COM();
	   DHT11_OUT=1;
	 
	   U8temp1=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);	 //数据校验 
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