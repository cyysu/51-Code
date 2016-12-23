#include "RC.h"
#include "NRF24L01.H"
#include "delay.h"
#include "uart.h"
#include "stdio.h"

uchar CheckSum(uchar *pbuf,uchar num);
void NRF24L01_transmit(uchar cmd)
{
   u8 tmp_buf[5]={0,0,0,0,0};
     tmp_buf[0]=0x55;
	 tmp_buf[1]=0xaa;
	  switch(cmd)
		{
		case Light_1:  	 tmp_buf[2]=0x49;//1等
											 tmp_buf[3]=0x68; 
			                 break;
		case Light_2:		 tmp_buf[2]=0x50;//2等
											 tmp_buf[3]=0x68;
			                 break;			
		case Light_3:		 tmp_buf[2]=0x51;//3等
											 tmp_buf[3]=0x68;
			                 break;			
		case Light_4:		 tmp_buf[2]=0x52;//4等
											 tmp_buf[3]=0x68;		    
			                 break;			
		case ZhaDa:			 tmp_buf[2]=0x84;//抬起
											 tmp_buf[3]=0x81; 
			                 break;			
		case Alert_led:  	 tmp_buf[2]=0x66;//警灯
											 tmp_buf[3]=0x68;
			                 break;	
		case Tunnel:		 tmp_buf[2]=0x46;//隧道
											 tmp_buf[3]=0x81;
							 break;
		default:        	 tmp_buf[2]=0x00;
											 tmp_buf[3]=0x00;
			                 break;		 												 
		}
	  	   tmp_buf[4]=CheckSum(tmp_buf,4);
		 if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
	    {   
			   uart_senddata(0x66) ;	 
		  } 
} 

/*
 函数功能：  校验和
 返回：      数组和取反的值
*/
uchar CheckSum(uchar *pbuf,uchar num)
{
	 uchar temp = 0;
		for(;num>0;num--)
		{
			 temp+=*pbuf++;			
		}
    temp=~temp;
   return (uchar)temp;
}

/**************************************************************************
函数功能：无线模块自检
入口参数：无
返回  值：无
**************************************************************************/
void NRF24L01_FindMyself(void)
{
		while(NRF24L01_Check())//检测不到24L01
	{
		   BEEP=!BEEP;//DS0闪烁
		   Delay500ms()	; 
	}
	 BEEP=1;
}

