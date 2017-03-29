#ifndef _MOTOR_TIM4_H_
#define _MOTOR_TIM4_H_


#define Motor_L_IN1_Set GPIO_SetBits(GPIOB,GPIO_Pin_14);		//����1Ϊ�ߵ�ƽ
#define Motor_L_IN1_Reset GPIO_ResetBits(GPIOB,GPIO_Pin_14);	//����1Ϊ�͵�ƽ
#define Motor_L_IN2_Set GPIO_SetBits(GPIOB,GPIO_Pin_15);		//����2Ϊ�ߵ�ƽ
#define Motor_L_IN2_Reset GPIO_ResetBits(GPIOB,GPIO_Pin_15);	//����2Ϊ�͵�ƽ

#define Motor_R_IN1_Set GPIO_SetBits(GPIOB,GPIO_Pin_10);		//����1Ϊ�ߵ�ƽ
#define Motor_R_IN1_Reset GPIO_ResetBits(GPIOB,GPIO_Pin_10);	//����1Ϊ�͵�ƽ
#define Motor_R_IN2_Set GPIO_SetBits(GPIOB,GPIO_Pin_11);		//����2Ϊ�ߵ�ƽ
#define Motor_R_IN2_Reset GPIO_ResetBits(GPIOB,GPIO_Pin_11);	//����2Ϊ�͵�ƽ

extern void Motor_PWM_EN(void);
extern void Motor_Set(s16 LS,s16 RS);

#endif
