#ifndef _FOLLOW_H_
#define _FOLLOW_H_

//extern u8 Flag_L,Flag_R;

//#define SW_XJ()    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)	//��ȡѭ������״̬
#define Follow_L() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)	//��ȡ���ѭ��������״̬
#define Follow_M() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)	//��ȡ�м�ѭ��������״̬
#define Follow_R() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)	//��ȡ�Ҳ�ѭ��������״̬

extern void  Follow(void);
extern void  GPIO_Follow(void);

#endif

