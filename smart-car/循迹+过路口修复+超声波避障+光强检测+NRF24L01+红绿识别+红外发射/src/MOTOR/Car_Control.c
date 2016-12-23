#include  "Car_Control.h"
#include  "delay.h"
#include  "PWM_PCA.h" 
/**Car 初始化**/
void Car_Init(void)
{
    MOTOR_A_EN=0;
	MOTOR_B_EN=0;
	MOTOR_GO_STOP;
}

/**小车循迹程序**/
extern volatile char renwu_flag;

void FollowLine(void)
{
	switch(xunji)
	 {
			case 0x1F:
			case 0x2f:
			case 0x3f:
			case 0x4f:
			case 0x5f:
			case 0x6f:
			case 0x7F:
			case 0x8f:
			case 0x9f:
			case 0xaf:
			case 0xbf:
			case 0xcf:						
			case 0xdF:
			case 0xEF:MOTOR_GO_RIGHT;  break;	
										
			case 0xF1:
			case 0xf2:
			case 0xf3:
			case 0xf4:
			case 0xf5:
			case 0xf6:
			case 0xF7:
			case 0xf8:
			case 0xf9:
			case 0xfa:
			case 0xfb:
			case 0xfc:						
			case 0xFd:
			case 0xFe:MOTOR_GO_LEFT;break; 	
			
			case 0xE7:MOTOR_GO_FORWARD; break;	   				
			case 0xFF:MOTOR_GO_STOP;   break;
			case 0x00:MOTOR_GO_STOP;
					  delay_ms(1200);
					  renwu_flag=renwu_flag+1;break;
			
			default:MOTOR_GO_FORWARD;  break;	
	 } 
  		
}

void Car_Check(void)//检测是否停止
{
	if(P0==0xff)
	{
		MOTOR_GO_BACK;delay_ms(500);
	}
}