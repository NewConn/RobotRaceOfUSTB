#include "STM32Lib\\stm32f10x.h" 

//�������е��ж�����
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* �����ж�ʹ�����1*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	
	/* EXTI6��7��8*/
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);



}
