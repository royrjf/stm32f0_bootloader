#include "main.h"
#include "led.h"
#include "u485.h"
#include "delay.h"
#include "timer.h"
#include "magnet.h"
#include "wdg.h"
#include "crc.h"
#include "dialswitch.h"
#include "string.h"
volatile char STOREY_NUM;  
uint8_t SUCTION_T[40];

int main(void)
{	
	
	memcpy((void*)0x20000000, (void*)0x08004000, 0xc0);
	SYSCFG_MemoryRemapConfig(SYSCFG_MemoryRemap_SRAM);
	
	MAGNETInit();
	TIM3_Int_Init(4999,71);     //5ms	
  u485_init(115200);
	LEDInit();
  dialswitch_init();
	crc_init();	
	
	IWDG_Config(IWDG_Prescaler_256,500);  //1s 	 
	
	while(dialswitch_read()=='X')
	{		
			IWDG_Feed();
			delay_ms(10);
	}

  while(1)
  {	
		if(1)
		{
			u485_tick();
		}
		if(1)
		{
		   MAGNET_Manage();
		}
		if(1)
		{
			IWDG_Feed();
		}
  }
}

