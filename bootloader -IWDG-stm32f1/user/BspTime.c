#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#include "BspTime.h"

volatile int g_Tim2Array[(u16)eTimMax] = {0};



/*******************************************************************************
  * @函数名称: BspTim2Init
  * @函数说明：定时器初始化
  * @输入参数：无
  * @输出参数：无
  * @返回参数：无
  * @历史记录:     
     <作者>    <时间>      <修改记录>
*******************************************************************************/
void BspTim2Init(void)
{
    NVIC_InitTypeDef NvicInitdef;
    TIM_TimeBaseInitTypeDef timbase;	
    uc16 cnt = 1000;     // 1ms ′￥·￠

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	

    TIM_DeInit(TIM2); 
    timbase.TIM_CounterMode = TIM_CounterMode_Up;
    timbase.TIM_ClockDivision = TIM_CKD_DIV1;
    timbase.TIM_Period = cnt - 1;
    timbase.TIM_Prescaler = 72 - 1; 	// 72·??μ
    TIM_TimeBaseInit(TIM2, &timbase);

    NvicInitdef.NVIC_IRQChannel = TIM2_IRQn;
    NvicInitdef.NVIC_IRQChannelPreemptionPriority = 10;    //×?μíó??è??
    NvicInitdef.NVIC_IRQChannelSubPriority = 0;
    NvicInitdef.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NvicInitdef);

    TIM_SetCounter(TIM2, 0);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}
/*******************************************************************************
  * @函数名称：BspTim2Close
  * @函数说明：关闭定时器
  * @输入参数：无
  * @输出参数：无
  * @返回参数：无
  * @历史记录:     
     <作者>    <时间>      <修改记录>
*******************************************************************************/
void BspTim2Close(void)
{
    TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
    TIM_Cmd(TIM2, DISABLE);
}

/*******************************************************************************
  * @函数名称：TIM2_IRQHandler
  * @函数说明：中断服务函数
  * @输入参数：无
  * @输出参数：无
  * @返回参数：无
  * @历史记录:     
     <作者>    <时间>      <修改记录>
*******************************************************************************/
void TIM2_IRQHandler(void)
{
    u16 i = 0;

    if( SET == TIM_GetITStatus(TIM2,TIM_IT_Update) )
    {
        TIM_ClearITPendingBit( TIM2, TIM_IT_Update);

        for (i = 0; i < (u16)eTimMax; i++)
        {
            g_Tim2Array[i]++;
        }
    }
}


/********************** END ***************************************************/

