#include "dialswitch.h"
#include "u485.h"
#include "main.h"

void dialswitch_init()
{	
	 GPIO_InitTypeDef  GPIO_InitStructure;
  
 /* Enable the GPIO_LED Clock */
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOF|RCC_AHBPeriph_GPIOA,ENABLE);


  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

char dialswitch_read()
{
	uint8_t num;
	num=0;
	if(S1IN==1)
	{
			num=num|0x01;
	}
	else
	{
			num=num&0xfe;
	}
	
		if(S2IN==1)
	{
			num=num|0x02;
	}
	else
	{
			num=num&0xfd;
	}
	
		if(S3IN==1)
	{
			num=num|0x04;
	}
	else
	{
			num=num&0xfb;
	}
	
		if(S4IN==1)
	{
			num=num|0x08;
	}
	else
	{
			num=num&0xf7;
	}
	
	switch(num)
	{
		case 1:  STOREY_NUM='A';break;
		case 2:  STOREY_NUM='B';break;
		case 3:  STOREY_NUM='C';break;
		case 4:  STOREY_NUM='D';break;
		case 5:  STOREY_NUM='E';break;
		
		case 6:  STOREY_NUM='F';break;
		case 7:  STOREY_NUM='G';break;
		case 8:  STOREY_NUM='H';break;
		case 9:  STOREY_NUM='I';break;
		case 10:  STOREY_NUM='J';break;
		
		case 11:  STOREY_NUM='K';break;
		case 12:  STOREY_NUM='L';break;
		case 13:  STOREY_NUM='M';break;
		case 14:  STOREY_NUM='N';break;
		case 15:  STOREY_NUM='O';break;
		
		default:

				U485_OUT;
				printf("ADSTOREYERR\r\n");
				U485_IN;
				return 'X';
				break;	
	}
//		U485_OUT;
//		printf("DATA:%d\r\n",num);
	//	U485_IN;
	
	return (char)num;
		
}


