#include "crc.h"

void crc_init()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
}

uint32_t crc_calculate(char *p,uint8_t num)
{
	uint8_t i;
	uint32_t data;
	CRC_ResetDR ();
		for(i=0;i<num;i++)
		{
				CRC->DR =*p++;
		}
		
		data=CRC->DR;
		return data; 		
}



