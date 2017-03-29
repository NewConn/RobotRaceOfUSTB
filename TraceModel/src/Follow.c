#include "STM32Lib\\stm32f10x.h"
#include "hal.h"
#include "Follow.h"
#include "Motor_TIM4.h"

//u8 Flag_L=0,Flag_R=0;
///******************************************************************************************
///*��ʱ����,�Ǿ�ȷ��ʱ
///******************************************************************************************/
void delay1us(int n)
{
    u32 i;
	while(n--)
	{
 	   i=2;
 	   while(i--);
    }
} 

void GPIO_Follow(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;

		/*ѭ������������PA6->Follow_L,PA7->Follow_R */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//�޺���������ߵ�ƽ����ʱ����͵�ƽ
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		/* ����IO�ڵ��ж��� */
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);
	
	
		/*PA6��PA7��PA8Ϊ�½��ش���*/
		EXTI_InitStructure.EXTI_Line = EXTI_Line6|EXTI_Line7|EXTI_Line8;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger =  EXTI_Trigger_Rising_Falling;	  
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);	
}

void  Follow(void)
{
	//if(SW_XJ())
	//{
		s8 temp=0x00,State=0x00, LL=0,RR=0;
		temp = Follow_L();
		temp = (temp<<1)|Follow_M();
		temp = (temp<<1)|Follow_R();
		State= temp&0x07;
		switch(State)
		{
			//û��⵽����ʱ��ԭ�ش�ת
			case 0x07:  
			{
				Motor_Set(-48,48);
				break;
			}
			
			//���ұ߼�⵽����ʱ���Ҵ�ת��������ת���ҵ����ת��
			case 0x06:  
			{
				Motor_Set(108,48);
				LL=1;
				break;
			}
			
			//���м��⵽����ʱ�����������ҵ������ת
			case 0x05:  
			{
				Motor_Set(108,108);
				break;
			}
			
			//�м��Լ��ұ߼�⵽����ʱ����Сת��������ת���ҵ����ת��
			case 0x04:  
			{
					
				Motor_Set(108,72);
				LL=1;
				break;
			}
			
			//����߼�⵽����ʱ�����ת��������ת���ҵ����ת��
			case 0x03:  
			{
				Motor_Set(48,108);
				RR=1;
				break;
			}
			
			//�����ܳ��ִ����
			case 0x02:  
				break;  
			
			//�м��Լ���߼�⵽����ʱ����Сת��������ת���ҵ����ת��
			case 0x01:  
			{
					
				Motor_Set(72,108);
				RR=1;
				break;
			}	
			
				//�м䣬���ұ߶���⵽����ʱ������
			case 0x00:  
			{
				Motor_Set(0,0);
				break;
			}
		}


		/*�ܳ��ܵ������ �ص��ܵ��� */
		if(State==0x06&&LL==1||State==0x04&&LL==1)
		{
		 	RR=0;
			Motor_Set(72,-36);
		}
		if(State==0x03&&RR==1||State==0x02&&RR==1)
		{
		 	LL=0;
			Motor_Set(-36,72);
		}
	//else
	//{
	//	Motor_Set(0,0);
//	}
	
}


