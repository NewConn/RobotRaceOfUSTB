/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "Encoder.h"

/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/
s32 Speed_L_Get = 0;
s32 Speed_R_Get = 0;
s32 Last_Speed_L_Get = 0;
s32 Last_Speed_R_Get = 0;
s32 R_Sum_Step = 0;
s32 L_Sum_Step = 0;
s32 Sum_Step = 0;

/********************************************************************************************************
Function Name: EncoderIOInit
Description  :
Inputs       : None
Outputs      : None
Notes        : Encoder IO��ʼ��
Revision     :
********************************************************************************************************/
void EncoderIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = ENCODER1_A_PIN|ENCODER1_B_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(ENCODER1_GPIO, &GPIO_InitStructure);
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = ENCODER2_A_PIN|ENCODER2_B_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(ENCODER2_GPIO, &GPIO_InitStructure);  
}

/********************************************************************************************************
Function Name: EncoderTIMInit
Description  :
Inputs       : None
Outputs      : None
Notes        : Encoder TIME��ʼ��
Revision     :
********************************************************************************************************/
void EncoderTIMInit(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

    /***********************   ENCODER2  *************************/
    TIM_DeInit(ENCODER_R_TIMER);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0;  // No prescaling
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(ENCODER_R_TIMER, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(ENCODER_R_TIMER, TIM_EncoderMode_TI12,
                               TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);	  //  ������������ʽ
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = ICx_FILTER;	 //   �˲���
    TIM_ICInit(ENCODER_R_TIMER, &TIM_ICInitStructure);
    ENCODER_R_TIMER->CNT = COUNTER_RESET;
    TIM_Cmd(ENCODER_R_TIMER, ENABLE);

    /**********************  ENCODER1  *************************/
    TIM_DeInit(ENCODER_L_TIMER);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0;  // No prescaling
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(ENCODER_L_TIMER, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(ENCODER_L_TIMER, TIM_EncoderMode_TI12,
                               TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);	//ѡ��T1��T2ͬʱ����ģʽ�������ؼ���
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = ICx_FILTER;
    TIM_ICInit(ENCODER_L_TIMER, &TIM_ICInitStructure);
    ENCODER_L_TIMER->CNT = COUNTER_RESET;
    TIM_Cmd(ENCODER_L_TIMER, ENABLE);

}

/********************************************************************************************************
Function Name: EncoderInit
Description  :
Inputs       : None
Outputs      : None
Notes        : Encoder��ʼ��
Revision     :
********************************************************************************************************/
void EncoderInit(void)
{
    EncoderIOInit();
    EncoderTIMInit();
}

/********************************************************************************************************
Function Name: GetSpeed
Description  :
Inputs       : None
Outputs      : None
Notes        :
Revision     :
********************************************************************************************************/
void GetSpeed(void)
{
	
	  Speed_L_Get = TIM_GetCounter(ENCODER_L_TIMER);		//�ɼ������ٶ�
    ENCODER_L_TIMER->CNT = COUNTER_RESET;			//����������
    if ((ENCODER_L_TIMER->CR1 & (1 << 4)))
    {
        Speed_L_Get = Speed_L_Get - 65536;
    }
    Speed_L_Get = -Speed_L_Get;							//���ݵ�·���ķ���

	
	
	
    Speed_R_Get = TIM_GetCounter(ENCODER_R_TIMER);		//�ɼ������ٶ�
    ENCODER_R_TIMER->CNT = COUNTER_RESET;			//����������

    if ((ENCODER_R_TIMER->CR1 & (1 << 4)))
    {
        Speed_R_Get = Speed_R_Get - 65536;
    }
    Speed_R_Get = -Speed_R_Get;

    



    if(Speed_L_Get > 400 || Speed_L_Get < -400)
    {
        Speed_L_Get = Last_Speed_L_Get;
    }
    if(Speed_R_Get > 400 || Speed_R_Get < -400)
    {
        Speed_R_Get = Last_Speed_R_Get;
    }


    Last_Speed_L_Get = Speed_L_Get;
    Last_Speed_R_Get = Speed_R_Get;			//�����ϴε��ٶ�ֵ

    L_PID.vi_FeedBack = Speed_L_Get;
    R_PID.vi_FeedBack = Speed_R_Get;


    if(Speed_L_Get > 1 || Speed_L_Get < -1)
    {
        L_Sum_Step += Speed_L_Get;
    }

    if(Speed_R_Get > 1 || Speed_R_Get < -1)
    {

        R_Sum_Step += Speed_R_Get;
    }
    Sum_Step = (R_Sum_Step + L_Sum_Step)>> 1;
}
/*----------------------------------------  F U N C T I O N S  ----------------------------------------*/

//===========================================  End Of File  ===========================================//