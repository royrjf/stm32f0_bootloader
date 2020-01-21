#ifndef __CRC__H
#define __CRC__H

#include "stm32f0xx.h"

extern void crc_init(void);
extern uint32_t crc_calculate(char *p,uint8_t num);

#endif

