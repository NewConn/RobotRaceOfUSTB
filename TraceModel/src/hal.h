#ifndef HAL_H
#define HAL_H

//Ӳ����ʼ��
extern void  ChipHalInit(void);
extern void  ChipOutHalInit(void);

#define Beep() GPIO_SetBits(GPIOA,GPIO_Pin_9);	//������

#endif

