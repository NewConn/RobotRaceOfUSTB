#include "STM32Lib\\stm32f10x.h"
#include "TIM4.h"
u16 TIM_T=144;
u16 Drv_PWM_L=100;
u16 Drv_PWM_R=100;

//ͨ�ö�ʱ��4���ã�ʹ��ͨ��1��2���PWM
void TIM4_Configuration(void)
{	
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	TIM_OCInitTypeDef	TIM_OCInitStructure; 

	/* TIM4 clock enable */
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	/* Time base configuration */
 	TIM_TimeBaseStructure.TIM_Period = TIM_T;          
  	TIM_TimeBaseStructure.TIM_Prescaler = 4000;       
  	TIM_TimeBaseStructure.TIM_ClockDivision =  0x0;    
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
  
  	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);		  //��ʼTIM4

  	/* Channel 1 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 				//PWMģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	//����ͨ����Ч
	TIM_OCInitStructure.TIM_Pulse = Drv_PWM_L; 							//ռ��ʱ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 		//�������
	TIM_OC1Init(TIM4,&TIM_OCInitStructure); 					

	/* Channel 2 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 				//PWMģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	//����ͨ����Ч
	TIM_OCInitStructure.TIM_Pulse = Drv_PWM_R; 							//ռ��ʱ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 		//�������
	TIM_OC2Init(TIM4,&TIM_OCInitStructure); 					

	/* TIM4 counter enable */
	TIM_Cmd(TIM4,ENABLE);
	/* TIM4 Main Output Enable */
	TIM_CtrlPWMOutputs(TIM4,ENABLE);
}

