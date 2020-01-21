#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#include "BspTime.h"

volatile int g_Tim2Array[(u16)eTimMax] = {0};



/*******************************************************************************
  * @��������: BspTim2Init
  * @����˵������ʱ����ʼ��
  * @�����������
  * @�����������
  * @���ز�������
  * @��ʷ��¼:     
     <����>    <ʱ��>      <�޸ļ�¼>
*******************************************************************************/
void BspTim2Init(void)
{
    NVIC_InitTypeDef NvicInitdef;
    TIM_TimeBaseInitTypeDef timbase;	
    uc16 cnt = 1000;     // 1ms �䣤����

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	

    TIM_DeInit(TIM2); 
    timbase.TIM_CounterMode = TIM_CounterMode_Up;
    timbase.TIM_ClockDivision = TIM_CKD_DIV1;
    timbase.TIM_Period = cnt - 1;
    timbase.TIM_Prescaler = 72 - 1; 	// 72��??��
    TIM_TimeBaseInit(TIM2, &timbase);

    NvicInitdef.NVIC_IRQChannel = TIM2_IRQn;
    NvicInitdef.NVIC_IRQChannelPreemptionPriority = 10;    //��?�̨���??��??
    NvicInitdef.NVIC_IRQChannelSubPriority = 0;
    NvicInitdef.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NvicInitdef);

    TIM_SetCounter(TIM2, 0);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}
/*******************************************************************************
  * @�������ƣ�BspTim2Close
  * @����˵�����رն�ʱ��
  * @�����������
  * @�����������
  * @���ز�������
  * @��ʷ��¼:     
     <����>    <ʱ��>      <�޸ļ�¼>
*******************************************************************************/
void BspTim2Close(void)
{
    TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
    TIM_Cmd(TIM2, DISABLE);
}

/*******************************************************************************
  * @�������ƣ�TIM2_IRQHandler
  * @����˵�����жϷ�����
  * @�����������
  * @�����������
  * @���ز�������
  * @��ʷ��¼:     
     <����>    <ʱ��>      <�޸ļ�¼>
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

