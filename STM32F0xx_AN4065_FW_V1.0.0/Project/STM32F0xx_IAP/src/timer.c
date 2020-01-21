#include "stm32f0xx_tim.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"

#include "timer.h"
#include "main.h"



void BspTim3Init(void)
{
    NVIC_InitTypeDef NvicInitdef;
    TIM_TimeBaseInitTypeDef timbase;	
    uint16_t cnt = 10000;     // 1ms ¡ä£¤¡¤¡é

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	

    TIM_DeInit(TIM3); 
    timbase.TIM_CounterMode = TIM_CounterMode_Up;
    timbase.TIM_ClockDivision = TIM_CKD_DIV1;
    timbase.TIM_Period = cnt - 1;
    timbase.TIM_Prescaler = 72 - 1; 	// 72¡¤??¦Ì
    TIM_TimeBaseInit(TIM3, &timbase);

    NvicInitdef.NVIC_IRQChannel = TIM3_IRQn;
    NvicInitdef.NVIC_IRQChannelPriority = 10;    //¡Á?¦Ì¨ª¨®??¨¨??
    NvicInitdef.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NvicInitdef);

    TIM_SetCounter(TIM3, 0);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
}

void BspTim3Close(void)
{
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    TIM_Cmd(TIM3, DISABLE);
}


void TIM3_IRQHandler(void)
{
	static uint8_t i;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 	
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
			i++;
			if(i==10)
			{
				i=0;
				COUNT++;
			}
		}
}


/********************** END ***************************************************/

