#include "STM32Lib\\stm32f10x.h"
#include "Motor_TIM4.h"
#include "TIM4.h"

// ֹͣ
void Motor_Stop(void)
{
	Motor_L_IN1_Reset;
	Motor_L_IN2_Reset;
	Motor_R_IN1_Reset;
	Motor_R_IN2_Reset;  
}
//����PWM
void Motor_L_PWM(s16 speed_L)
{
	if(speed_L>0)
	{
		if(speed_L>TIM_T)
		{
			speed_L=TIM_T;
		} 	
		Motor_L_IN1_Set;
		Motor_L_IN2_Reset;
	
		Drv_PWM_L=(u16)speed_L;	
	}
	else
	{
		if(speed_L<(s16)(-TIM_T))
		{
			speed_L=(s16)(-TIM_T);
		}
		Motor_L_IN1_Reset;	
		Motor_L_IN2_Set;
	
		Drv_PWM_L=(u16)(-speed_L);	
	}	
	TIM_SetCompare1(TIM4,Drv_PWM_L);//ǰ�����ٶȿ��Կ�һ�㣬ת��ͺ��˵��ٶ���һЩ

}
//�ҵ��PWM
void Motor_R_PWM(s16 speed_R)
{
	if(speed_R>0)
	{
		if(speed_R>TIM_T)
		{
			speed_R=TIM_T;
		}
		Motor_R_IN1_Set;
		Motor_R_IN2_Reset;
		Drv_PWM_R=(u16)speed_R;	
	}
	else
	{
		if(speed_R<(s16)(-TIM_T))
		{
			speed_R=(s16)(-TIM_T);
		}
		Motor_R_IN1_Reset;	
		Motor_R_IN2_Set;
		
		Drv_PWM_R=(u16)(-speed_R);	
	}	
	TIM_SetCompare2(TIM4,Drv_PWM_R);//ǰ�����ٶȿ��Կ�һ�㣬ת��ͺ��˵��ٶ���һЩ

}
//������ƺ���
void Motor_Set(s16 LS,s16 RS)
{
	Motor_L_PWM(RS);
	Motor_R_PWM(LS);			
}


