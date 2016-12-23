#include  "HC_SR04.h"
#include  "delay.h"
#include  "uart.h"
#include  "Car_Control.h"

/******************启动模块**********************************/
void  Start_hc_sr04() 		         
{
	trig = 1;			                
	delay_2us(5) ;
	trig = 0;
}

/*********************换算**************测试距离=(高电平时间*声速(340M/S))/2;*************/
float Conut(void)
{
	unsigned int  time=0;
	float         S=0;
	time = TH1*256+TL1;
	TH1=0;
	TL1=0;				    //取完之后 对定时器寄存器清零	  
	S=(time*1.87)/100;     //算出来是CM
	return S ;
}
/*************************超声波检测******************************/
float ultrasound_check()
{
	float f = 0.0 ;
	sr04_over_flag = 0 ;
	Start_hc_sr04() ;
	while(!echo);		    //当RX为零时等待
	TR1 = 1;		        //定时器0开始计时
	while(echo);			//当RX为1计数并等待
	TR1 = 0;		        //定时器0停止计时

	if(sr04_over_flag==1)
	{
		f = 400 ;
	}
	else    
	{
		f = Conut();
	}
	return f ;
}

void HC_SR()
{     
	u8 i = 0  ;
	u8 count_direct = 0 ;
	u8 count_move = 0 ;
	u16 temp = 0 ;
	u8  u8temp = 0 ;  
	float distance =50.0 ;

	InitUart() ;
	ET0 = 1 ;
	ET1= 1 ;
	EA = 1 ;
	while (i<1)
	{
		distance =50.0 ;
		if(ultra_check_flag!=0)
		{
			ET0 = 0 ;
			distance = ultrasound_check();
			count_move++;
			ultra_check_flag = 0 ;
			ET0 = 1 ;
		}
		MOTOR_GO_FORWARD;
		if(distance <30 )
		{
			MOTOR_GO_STOP;
			BEEP=0;delay_ms(500);BEEP=1;delay_ms(500);
			delay_ms(8000);
			i++;
		}
		FollowLine();
	}
}
