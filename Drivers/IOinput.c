/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "IOinput.h"

u16 InPinTable[17]= {0, IN1_PIN, IN2_PIN, IN3_PIN, IN4_PIN, IN5_PIN, IN6_PIN,
                     IN7_PIN, IN8_PIN, IN9_PIN, IN10_PIN, IN11_PIN, IN12_PIN,
                     IN13_PIN, IN14_PIN, IN15_PIN, IN16_PIN
                    };
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/
/********************************************************************************************************
Function Name: InputIOInit
Description  :
Inputs       : None
Outputs      : None
Notes        :
Revision     :
********************************************************************************************************/
void InputIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = IN1_PIN|IN9_PIN|IN13_PIN|IN14_PIN|IN15_PIN|IN16_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // importance
    GPIO_Init(IN1_16_GPIO, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = IN2_PIN|IN3_PIN|IN4_PIN|IN5_PIN|IN6_PIN|IN7_PIN|IN8_PIN|IN10_PIN|IN11_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IN2_11_GPIO, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = IN12_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IN12_GPIO, &GPIO_InitStructure);
}

/*----------------------------------------  F U N C T I O N S  ----------------------------------------*/
/********************************************************************************************************
Function Name: GetKeyState
Description  :
Inputs       : UINT8 keynum -- 1,2,3.......16
Outputs      : UINT8 Temp   -- Start key or Again key state
Notes        :
Revision     :
********************************************************************************************************/
UINT8 GetKeyState(UINT8 keynum)
{
    UINT8 Temp = 0;

    if(keynum == 1||keynum == 9||keynum == 13||keynum == 14|| \
            keynum == 15||keynum == 16)
    {
        Temp = GPIO_ReadInputDataBit(IN1_16_GPIO, InPinTable[keynum]);
    }
    else if(keynum == 2||keynum == 3||keynum == 4||keynum == 5|| \
            keynum == 6||keynum == 7||keynum == 8||keynum == 10|| \
            keynum == 11)
    {
        Temp = GPIO_ReadInputDataBit(IN2_11_GPIO, InPinTable[keynum]);
    }
    else if(keynum == 12)
    {
        Temp = GPIO_ReadInputDataBit(IN12_GPIO, InPinTable[keynum]);
    }
    return(Temp);
}

//===========================================  End Of File  ===========================================//

