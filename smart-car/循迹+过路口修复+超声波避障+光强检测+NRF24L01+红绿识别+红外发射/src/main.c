#include  "common.h"
#include  "stdio.h"	
#include  "delay.h"
#include  "PWM_PCA.h"  
#include  "Car_Control.h"
#include  "NRF24L01.h"
#include  "RC.h"
#include  "color_sensor.h"
#include  "uart.h"
#include  "IR_control.h"
#include  "BH1750.h"
#include  "HC_SR04.h"
char renwu_flag;
void main()
{  
    Car_Init(); 				//小车的初始化，NRF24L01也在其中初始化
    PWM_PCA_init();				//PWM_PCA初始化
    PWM_Set(60,60);    			//PWM使用FOSC作为时钟源所以PWM设置可以只执行一次
    delay_ms(2000);	

	P4SW|=0X70;        			//将 P4.4 P4.5 P4.6口设置成IO口
	P4M1&=~0X10;
	P4M0&=~0X10;
	BEEP=1;						//打开蜂鸣器
	init_NRF24L01();			//NRF24L01初始化
	NRF24L01_FindMyself();		//NRF24L01自检
	NRF24L01_TX_Mode(0x04,0x01);//将NRF24L01配置成发送模式   地址为{0x34,0x43,0x10,0x10,0x02}
	NRF24L01_transmit(0x00);
	NRF24L01_transmit(0x00);
    while(1)
		{	
			FollowLine();		//开始循迹
			switch(renwu_flag)	//路口检测
			{  
				case 1 :Car_Check();
						HC_SR();delay_ms(1800);
						Car_Check();
						renwu_flag=renwu_flag+1;	break;//外环绕圈第1个路口左转
				
				case 3 :Car_Check();
						MOTOR_GO_RIGHT;delay_ms(1800);
						Car_Check();
						renwu_flag=renwu_flag+1;	break;//外环绕圈第1个路口左转
				
				case 7 :Car_Check();
						MOTOR_GO_RIGHT;delay_ms(1800);
						MOTOR_GO_STOP;delay_ms(1000);
						NRF24L01_transmit(ZhaDa);			//NRF24L01控制闸道
						Car_Check();
						renwu_flag=renwu_flag+1; 	break;//第5个路口左转，延时过匝道
				
				case 11 :Car_Check();
						MOTOR_GO_STOP;delay_ms(3000);
						BH_Light();
						NRF24L01_transmit(Light_3);			//NRF24L01控制调光
						MOTOR_GO_BACK;delay_ms(4450);
						Car_Check();
						renwu_flag=renwu_flag+1;	break;//第9个路口，调光 退出接着左转
				case 12:Car_Check();
						MOTOR_GO_RIGHT;delay_ms(1800);
						Car_Check();
						renwu_flag=renwu_flag+1;	break;//第9个路口，调光 退出接着左转
				
				case 14:Car_Check();
						MOTOR_GO_STOP;delay_ms(800);
						Yanse();delay_ms(500);				//颜色检测，遇红灯时蜂鸣器响
						Car_Check();
						renwu_flag=renwu_flag+1; 	break;//第12个路口左转，红绿灯检测	
						
				case 16:Car_Check();
						NRF24L01_transmit(Tunnel);			//NRF24L01控制隧道排风
						MOTOR_GO_RIGHT;delay_ms(1800);
						Car_Check();
						renwu_flag=renwu_flag+1; 	break;//第14个路口，隧道排风 路口左转，
						
				case 18:Car_Check();
						MOTOR_GO_FORWARD;delay_ms(1650);
						MOTOR_GO_STOP;
						IR_DH();						//采集温度。通过红外射给旋转LED灯
						MOTOR_GO_FORWARD;delay_ms(550);
						MOTOR_GO_STOP;
						IR_DH();
						Car_Check();
						renwu_flag=renwu_flag+1; 	break;//第16个路口，红外发送温湿度
						
				case 20:Car_Check();
						MOTOR_GO_STOP;delay_ms(1000);
						NRF24L01_transmit(Alert_led);		//NRF24L01控制报警灯
//						MOTOR_GO_RIGHT;delay_ms(1500);
						MOTOR_GO_LEFT;delay_ms(1800);
						Car_Check();
						renwu_flag=renwu_flag+1;	break;//第18个路口，报警灯通信
						
				case 22:Car_Check();
						MOTOR_GO_RIGHT;delay_ms(1800);
						Car_Check();
						renwu_flag=renwu_flag+1; 	
						renwu_flag=0;				break;//第19个路口左转
						
//				case 20:MOTOR_GO_LEFT;delay_ms(1500);
//						renwu_flag=renwu_flag+1; 	
//						renwu_flag=0;				break;//第20个路右转
//						
//				case 21:
////						MOTOR_GO_LEFT;delay_ms(5000);		//旋转半圈
//						MOTOR_GO_STOP;						//后停止
//						renwu_flag=renwu_flag+1; 	break;//第21个路口左转	
//						
				default:break;
				}   
		}		
}