#ifndef __WDG_H
#define __WDG_H
#include "stm32f0xx.h"

extern void IWDG_Config(uint8_t prv,uint16_t rlv);
extern void IWDG_Feed(void);

#endif




