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
    Car_Init(); 				//С���ĳ�ʼ����NRF24L01Ҳ�����г�ʼ��
    PWM_PCA_init();				//PWM_PCA��ʼ��
    PWM_Set(60,60);    			//PWMʹ��FOSC��Ϊʱ��Դ����PWM���ÿ���ִֻ��һ��
    delay_ms(2000);	

	P4SW|=0X70;        			//�� P4.4 P4.5 P4.6�����ó�IO��
	P4M1&=~0X10;
	P4M0&=~0X10;
	BEEP=1;						//�򿪷�����
	init_NRF24L01();			//NRF24L01��ʼ��
	NRF24L01_FindMyself();		//NRF24L01�Լ�
	NRF24L01_TX_Mode(0x04,0x01);//��NRF24L01���óɷ���ģʽ   ��ַΪ{0x34,0x43,0x10,0x10,0x02}
	NRF24L01_transmit(0x00);
	NRF24L01_transmit(0x00);
    while(1)
		{	
			FollowLine();		//��ʼѭ��
			switch(renwu_flag)	//·�ڼ��
			{  
				case 1 :Car_Check();
						HC_SR();delay_ms(1800);
						Car_Check();
						renwu_flag=renwu_flag+1;	break;//�⻷��Ȧ��1��·����ת
				
				case 3 :Car_Check();
						MOTOR_GO_RIGHT;delay_ms(1800);
						Car_Check();
						renwu_flag=renwu_flag+1;	break;//�⻷��Ȧ��1��·����ת
				
				case 7 :Car_Check();
						MOTOR_GO_RIGHT;delay_ms(1800);
						MOTOR_GO_STOP;delay_ms(1000);
						NRF24L01_transmit(ZhaDa);			//NRF24L01����բ��
						Car_Check();
						renwu_flag=renwu_flag+1; 	break;//��5��·����ת����ʱ���ѵ�
				
				case 11 :Car_Check();
						MOTOR_GO_STOP;delay_ms(3000);
						BH_Light();
						NRF24L01_transmit(Light_3);			//NRF24L01���Ƶ���
						MOTOR_GO_BACK;delay_ms(4450);
						Car_Check();
						renwu_flag=renwu_flag+1;	break;//��9��·�ڣ����� �˳�������ת
				case 12:Car_Check();
						MOTOR_GO_RIGHT;delay_ms(1800);
						Car_Check();
						renwu_flag=renwu_flag+1;	break;//��9��·�ڣ����� �˳�������ת
				
				case 14:Car_Check();
						MOTOR_GO_STOP;delay_ms(800);
						Yanse();delay_ms(500);				//��ɫ��⣬�����ʱ��������
						Car_Check();
						renwu_flag=renwu_flag+1; 	break;//��12��·����ת�����̵Ƽ��	
						
				case 16:Car_Check();
						NRF24L01_transmit(Tunnel);			//NRF24L01��������ŷ�
						MOTOR_GO_RIGHT;delay_ms(1800);
						Car_Check();
						renwu_flag=renwu_flag+1; 	break;//��14��·�ڣ�����ŷ� ·����ת��
						
				case 18:Car_Check();
						MOTOR_GO_FORWARD;delay_ms(1650);
						MOTOR_GO_STOP;
						IR_DH();						//�ɼ��¶ȡ�ͨ�����������תLED��
						MOTOR_GO_FORWARD;delay_ms(550);
						MOTOR_GO_STOP;
						IR_DH();
						Car_Check();
						renwu_flag=renwu_flag+1; 	break;//��16��·�ڣ����ⷢ����ʪ��
						
				case 20:Car_Check();
						MOTOR_GO_STOP;delay_ms(1000);
						NRF24L01_transmit(Alert_led);		//NRF24L01���Ʊ�����
//						MOTOR_GO_RIGHT;delay_ms(1500);
						MOTOR_GO_LEFT;delay_ms(1800);
						Car_Check();
						renwu_flag=renwu_flag+1;	break;//��18��·�ڣ�������ͨ��
						
				case 22:Car_Check();
						MOTOR_GO_RIGHT;delay_ms(1800);
						Car_Check();
						renwu_flag=renwu_flag+1; 	
						renwu_flag=0;				break;//��19��·����ת
						
//				case 20:MOTOR_GO_LEFT;delay_ms(1500);
//						renwu_flag=renwu_flag+1; 	
//						renwu_flag=0;				break;//��20��·��ת
//						
//				case 21:
////						MOTOR_GO_LEFT;delay_ms(5000);		//��ת��Ȧ
//						MOTOR_GO_STOP;						//��ֹͣ
//						renwu_flag=renwu_flag+1; 	break;//��21��·����ת	
//						
				default:break;
				}   
		}		
}