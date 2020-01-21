#ifndef __DIALSWITCH_H
#define __DIALSWITCH_H

#include "stm32f0xx.h"

#define S1IN GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)

#define S2IN GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)

#define S3IN GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)

#define S4IN GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)


extern void dialswitch_init(void);
extern char dialswitch_read(void);
#endif
