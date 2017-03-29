/***************************************************
**HAL.c
**��Ҫ����оƬӲ�����ڲ���Χ���ⲿ��Χ�ĳ�ʼ��������INIT����
**��MAIN�е��ã�ʹMAIN�����о�����Ӳ�����޹�
***************************************************/

#include "STM32Lib\\stm32f10x.h"
#include "hal.h"
#include "follow.h"

//�����ڲ�Ӳ��ģ������ú���
extern void RCC_Configuration(void);			//RCC
extern void GPIO_Configuration(void);			//GPIO

extern void TIM4_Configuration(void);            //TIM
extern void NVIC_Configuration(void);            //NVIC
/*******************************
**������:ChipHalInit()
**����:Ƭ��Ӳ����ʼ��
*******************************/
void  ChipHalInit(void)
{
	//��ʼ��ʱ��Դ
	RCC_Configuration();
	
	//��ʼ��GPIO
	GPIO_Configuration();
	
	//��ʼ��TIM
	TIM4_Configuration();

	NVIC_Configuration();
	
}


/*********************************
**������:ChipOutHalInit()
**����:Ƭ��Ӳ����ʼ��
*********************************/
void  ChipOutHalInit(void)
{
	GPIO_Follow();
}
