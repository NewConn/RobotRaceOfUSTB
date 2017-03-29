#include "STM32Lib\\stm32f10x.h"
#include "Motor_TIM4.h"
/*******************************************************************************
* Function Name  : GPIO_Configuration
* ����PA2~PA7,PB0~PB1Ϊ���LED��
*******************************************************************************/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*��������CLOCK,��ʹ��GPIO֮ǰ����������Ӧ�˵�ʱ��.
	��STM32����ƽǶ���˵,û������Ķ˽�������ʱ��,Ҳ�Ͳ������,
	����STM32���ܵ�һ�ּ���,*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
/**********************************************************************************
**************************���Ȳ���  PA9************************************************
***********************************************************************************/
	/*����Beep->PA9 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOA,GPIO_Pin_9);

/**********************************************************************************
**************************ѭ�����ϲ���*************************************************
***********************************************************************************/	
	/*ѭ����⿪��  SW_XJ()->PB1  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*���ϼ�⿪��  SW_	BZ()->PB1  */
/*	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);		*/

/**********************************************************************************
**************************�������*************************************************
***********************************************************************************/
	/* GPIOB Configuration:TIM4 Channel1, 2in Output */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*Motor_Enable:
		Motor_L_IN1	->	(PB14,27)
		Motor_L_IN2 ->	(PB15,28)	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	//GPIO�������ٶ�
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//��ʼ��ʱ�򣬹رյ������,��IN1=0;IN2=0;
	Motor_L_IN1_Reset;				//����1Ϊ�͵�ƽ
	Motor_L_IN2_Reset;				//����2Ϊ�͵�ƽ

	/*Motor_Enable:
		Motor_R_IN1	->	(PB10,21)
		Motor_R_IN2 ->	(PB11,22)	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	//GPIO�������ٶ�
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//��ʼ��ʱ�򣬹رյ������,��IN1=0;IN2=0;
	Motor_R_IN1_Reset;				//����1Ϊ�͵�ƽ
	Motor_R_IN2_Reset;				//����2Ϊ�͵�ƽ

}


