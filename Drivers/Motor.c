/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "Motor.h"

/********************************************************************************************************
Function Name: MotorIOInit
Description  :
Inputs       : None
Outputs      : None
Notes        :
Revision     :
********************************************************************************************************/
void MotorIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = MOTOR1_PWM_PIN|MOTOR2_PWM_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MOTOR_GPIO, &GPIO_InitStructure);
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin  = MOTOR1_DIR_PIN|MOTOR2_DIR_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MOTOR_GPIO, &GPIO_InitStructure);
}

/********************************************************************************************************
Function Name: MotorTIMInit
Description  :
Inputs       : None
Outputs      : None
Notes        :
Revision     :
********************************************************************************************************/
void MotorTIMInit(void)
{
    TIM_TimeBaseInitTypeDef TIM2_TimeBaseStructure;
    TIM_OCInitTypeDef TIM2_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_DeInit(MOTOR_TIM);
    TIM2_TimeBaseStructure.TIM_Prescaler = 4;                               // ϵͳ  72MHz    TIMʱ��= 72MHz/5=14400000
    TIM2_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM2_TimeBaseStructure.TIM_Period = MOTOR_Period;                         // Frequency = 14400000 / 2000=7200
    TIM2_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    //TIM2_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(MOTOR_TIM, &TIM2_TimeBaseStructure);

    TIM2_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM2_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    //TIM2_OCInitStructure.TIM_OutputNState=TIM_OutputState_Disable;
    TIM2_OCInitStructure.TIM_Pulse = MOTOR_Period >> 1;                       // TIM2 dutycycle = 50%
    TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
//     TIM2_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
//     TIM2_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

    TIM_OC1Init(MOTOR_TIM, &TIM2_OCInitStructure);
    TIM_OC1PreloadConfig(MOTOR_TIM, TIM_OCPreload_Enable);

//     TIM2_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
//     TIM2_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//     //TIM2_OCInitStructure.TIM_OutputNState=TIM_OutputState_Disable;
//     TIM2_OCInitStructure.TIM_Pulse = MOTOR_Period >> 1;                       // TIM2 dutycycle = 50%
//     TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC3Init(MOTOR_TIM, &TIM2_OCInitStructure);
    TIM_OC3PreloadConfig(MOTOR_TIM, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(MOTOR_TIM,ENABLE);
    TIM_Cmd(MOTOR_TIM, ENABLE);
    //TIM_CtrlPWMOutputs(MOTOR_TIM,ENABLE);
}

/********************************************************************************************************
Function Name: MotorInit
Description  :
Inputs       : None
Outputs      : None
Notes        :
Revision     :
********************************************************************************************************/
void MotorInit(void)
{
    MotorIOInit();
    MotorTIMInit();
}

/********************************************************************************************************
Function Name: SetMotor1PWM
Description  :
Inputs       : xpwm
Outputs      : None
Notes        :
Revision     :
********************************************************************************************************/
void SetMotor1PWM(s16 xpwm)
{
    if(xpwm < 0)
    {
        MOTOR1_DIR_L;
        TIM_SetCompare1(MOTOR_TIM,0-xpwm);
    }
    else
    {
        MOTOR1_DIR_H;
        TIM_SetCompare1(MOTOR_TIM,2000-xpwm);
    }
}

/********************************************************************************************************
Function Name: SetMotor2PWM
Description  :
Inputs       : xpwm
Outputs      : None
Notes        :
Revision     :
********************************************************************************************************/
void SetMotor2PWM(s16 xpwm)
{
    if(xpwm < 0)
    {
        MOTOR2_DIR_L;
        TIM_SetCompare3(MOTOR_TIM,0-xpwm);
    }
    else
    {
        MOTOR2_DIR_H;
        TIM_SetCompare3(MOTOR_TIM,2000-xpwm);
    }
}
//===========================================  End Of File  ===========================================//
