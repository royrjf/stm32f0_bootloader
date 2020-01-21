#ifndef __WDG_H
#define __WDG_H	 
#include "common.h"

extern void IWDG_Config(uint8_t prv,uint16_t rlv);
extern void IWDG_Feed(void);
#include "stm32f10x_iwdg.h"

#endif
