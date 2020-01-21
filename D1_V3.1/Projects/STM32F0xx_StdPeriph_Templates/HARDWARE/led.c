#include "led.h" 
#include "stm32f0xx.h"
void LEDInit()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
 /* Enable the GPIO_LED Clock */
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOF|RCC_AHBPeriph_GPIOC|RCC_AHBPeriph_GPIOA,ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
	
}

void LEDToggle()
{
  GPIOF->ODR ^= GPIO_Pin_7;
}
