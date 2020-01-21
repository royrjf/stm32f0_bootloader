#include "magnet.h"
#include "stm32f0xx.h"
#include "main.h"
#include "u485.h"
#include "delay.h"
volatile uint8_t MAGNET_FLAG;
uint8_t magnet_buf[20];
uint8_t magnet_timer_flag[40];

void MAGNETInit()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOC|RCC_AHBPeriph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin = M11_Pin|M12_Pin|M25_Pin|M29_Pin|M30_Pin|M39_Pin|M40_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits (GPIOA, M11_Pin|M12_Pin|M25_Pin|M29_Pin|M30_Pin|M39_Pin|M40_Pin);
	
	GPIO_InitStructure.GPIO_Pin =M7_Pin|M8_Pin|M9_Pin|M10_Pin|M17_Pin|M18_Pin|M19_Pin|M22_Pin|M23_Pin|M24_Pin|M31_Pin|M32_Pin|M33_Pin|M34_Pin|M37_Pin|M38_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits (GPIOB, M7_Pin|M8_Pin|M9_Pin|M10_Pin|M17_Pin|M18_Pin|M19_Pin|M22_Pin|M23_Pin|M24_Pin|M31_Pin|M32_Pin|M33_Pin|M34_Pin|M37_Pin|M38_Pin);
	
  GPIO_InitStructure.GPIO_Pin = M1_Pin|M2_Pin|M4_Pin|M5_Pin|M6_Pin|M13_Pin|M14_Pin|M15_Pin|M16_Pin|M20_Pin|M21_Pin|M26_Pin|M27_Pin|M28_Pin|M35_Pin|M36_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits (GPIOC, M1_Pin|M2_Pin|M4_Pin|M5_Pin|M6_Pin|M13_Pin|M14_Pin|M15_Pin|M16_Pin|M20_Pin|M21_Pin|M26_Pin|M27_Pin|M28_Pin|M35_Pin|M36_Pin);
	
  GPIO_InitStructure.GPIO_Pin = M3_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits (GPIOD,  M3_Pin);
}


void MAGNET_Manage()
{
	 uint8_t i,j=1;
	 uint8_t magnet_num;
	 if(MAGNET_FLAG==1)
	 {
		 MAGNET_FLAG=0;
		for(i=0;i<Q_485.rx_len-6;i=i+2)
		 {
				magnet_num=magnet_buf[i];
				switch(magnet_num)
				{
					case 1: M1open;magnet_timer_flag[0]=1;SUCTION_T[0]=magnet_buf[i+1];if(SUCTION_T[0]>100){SUCTION_T[0]=100;}break;
					case 2: M2open;magnet_timer_flag[1]=1;SUCTION_T[1]=magnet_buf[i+1];if(SUCTION_T[1]>100){SUCTION_T[1]=100;}break;
					case 3: M3open;magnet_timer_flag[2]=1;SUCTION_T[2]=magnet_buf[i+1];if(SUCTION_T[2]>100){SUCTION_T[2]=100;}break;
					case 4: M4open;magnet_timer_flag[3]=1;SUCTION_T[3]=magnet_buf[i+1];if(SUCTION_T[3]>100){SUCTION_T[3]=100;}break;
					case 5: M5open;magnet_timer_flag[4]=1;SUCTION_T[4]=magnet_buf[i+1];if(SUCTION_T[4]>100){SUCTION_T[4]=100;}break;
					case 6: M6open;magnet_timer_flag[5]=1;SUCTION_T[5]=magnet_buf[i+1];if(SUCTION_T[5]>100){SUCTION_T[5]=100;}break;
					case 7: M7open;magnet_timer_flag[6]=1;SUCTION_T[6]=magnet_buf[i+1];if(SUCTION_T[6]>100){SUCTION_T[6]=100;}break;
					case 8: M8open;magnet_timer_flag[7]=1;SUCTION_T[7]=magnet_buf[i+1];if(SUCTION_T[7]>100){SUCTION_T[7]=100;}break;
					case 9: M9open;magnet_timer_flag[8]=1;SUCTION_T[8]=magnet_buf[i+1];if(SUCTION_T[8]>100){SUCTION_T[8]=100;}break;
					case 10: M10open;magnet_timer_flag[9]=1;SUCTION_T[9]=magnet_buf[i+1];if(SUCTION_T[9]>100){SUCTION_T[9]=100;}break;
						
					case 11: M11open;magnet_timer_flag[10]=1;SUCTION_T[10]=magnet_buf[i+1];if(SUCTION_T[10]>100){SUCTION_T[10]=100;}break;
					case 12: M12open;magnet_timer_flag[11]=1;SUCTION_T[11]=magnet_buf[i+1];if(SUCTION_T[11]>100){SUCTION_T[11]=100;}break;
					case 13: M13open;magnet_timer_flag[12]=1;SUCTION_T[12]=magnet_buf[i+1];if(SUCTION_T[12]>100){SUCTION_T[12]=100;}break;
					case 14: M14open;magnet_timer_flag[13]=1;SUCTION_T[13]=magnet_buf[i+1];if(SUCTION_T[13]>100){SUCTION_T[13]=100;}break;
					case 15: M15open;magnet_timer_flag[14]=1;SUCTION_T[14]=magnet_buf[i+1];if(SUCTION_T[14]>100){SUCTION_T[14]=100;}break;
					case 16: M16open;magnet_timer_flag[15]=1;SUCTION_T[15]=magnet_buf[i+1];if(SUCTION_T[15]>100){SUCTION_T[15]=100;}break;
					case 17: M17open;magnet_timer_flag[16]=1;SUCTION_T[16]=magnet_buf[i+1];if(SUCTION_T[16]>100){SUCTION_T[16]=100;}break;
					case 18: M18open;magnet_timer_flag[17]=1;SUCTION_T[17]=magnet_buf[i+1];if(SUCTION_T[17]>100){SUCTION_T[17]=100;}break;
					case 19: M19open;magnet_timer_flag[18]=1;SUCTION_T[18]=magnet_buf[i+1];if(SUCTION_T[18]>100){SUCTION_T[18]=100;}break;
					case 20: M20open;magnet_timer_flag[19]=1;SUCTION_T[19]=magnet_buf[i+1];;if(SUCTION_T[19]>100){SUCTION_T[19]=100;}break;
						
					case 21: M21open;magnet_timer_flag[20]=1;SUCTION_T[20]=magnet_buf[i+1];if(SUCTION_T[20]>100){SUCTION_T[20]=100;}break;
					case 22: M22open;magnet_timer_flag[21]=1;SUCTION_T[21]=magnet_buf[i+1];if(SUCTION_T[21]>100){SUCTION_T[21]=100;}break;
					case 23: M23open;magnet_timer_flag[22]=1;SUCTION_T[22]=magnet_buf[i+1];if(SUCTION_T[22]>100){SUCTION_T[22]=100;}break;
					case 24: M24open;magnet_timer_flag[23]=1;SUCTION_T[23]=magnet_buf[i+1];if(SUCTION_T[23]>100){SUCTION_T[23]=100;}break;
					case 25: M25open;magnet_timer_flag[24]=1;SUCTION_T[24]=magnet_buf[i+1];if(SUCTION_T[24]>100){SUCTION_T[24]=100;}break;
					case 26: M26open;magnet_timer_flag[25]=1;SUCTION_T[25]=magnet_buf[i+1];if(SUCTION_T[25]>100){SUCTION_T[25]=100;}break;
					case 27: M27open;magnet_timer_flag[26]=1;SUCTION_T[26]=magnet_buf[i+1];if(SUCTION_T[26]>100){SUCTION_T[26]=100;}break;
					case 28: M28open;magnet_timer_flag[27]=1;SUCTION_T[27]=magnet_buf[i+1];if(SUCTION_T[27]>100){SUCTION_T[27]=100;}break;
					case 29: M29open;magnet_timer_flag[28]=1;SUCTION_T[28]=magnet_buf[i+1];if(SUCTION_T[28]>100){SUCTION_T[28]=100;}break;
					case 30: M30open;magnet_timer_flag[29]=1;SUCTION_T[29]=magnet_buf[i+1];if(SUCTION_T[29]>100){SUCTION_T[29]=100;}break;
						
					case 31: M31open;magnet_timer_flag[30]=1;SUCTION_T[30]=magnet_buf[i+1];if(SUCTION_T[30]>100){SUCTION_T[30]=100;}break;
					case 32: M32open;magnet_timer_flag[31]=1;SUCTION_T[31]=magnet_buf[i+1];if(SUCTION_T[31]>100){SUCTION_T[31]=100;}break;
					case 33: M33open;magnet_timer_flag[32]=1;SUCTION_T[32]=magnet_buf[i+1];if(SUCTION_T[32]>100){SUCTION_T[32]=100;}break;
					case 34: M34open;magnet_timer_flag[33]=1;SUCTION_T[33]=magnet_buf[i+1];if(SUCTION_T[33]>100){SUCTION_T[33]=100;}break;
					case 35: M35open;magnet_timer_flag[34]=1;SUCTION_T[34]=magnet_buf[i+1];if(SUCTION_T[34]>100){SUCTION_T[34]=100;}break;
					case 36: M36open;magnet_timer_flag[35]=1;SUCTION_T[35]=magnet_buf[i+1];if(SUCTION_T[35]>100){SUCTION_T[35]=100;}break;
					case 37: M37open;magnet_timer_flag[36]=1;SUCTION_T[36]=magnet_buf[i+1];if(SUCTION_T[36]>100){SUCTION_T[36]=100;}break;
					case 38: M38open;magnet_timer_flag[37]=1;SUCTION_T[37]=magnet_buf[i+1];if(SUCTION_T[37]>100){SUCTION_T[37]=100;}break;
					case 39: M39open;magnet_timer_flag[38]=1;SUCTION_T[38]=magnet_buf[i+1];if(SUCTION_T[38]>100){SUCTION_T[38]=100;}break;
					case 40: M40open;magnet_timer_flag[39]=1;SUCTION_T[39]=magnet_buf[i+1];if(SUCTION_T[39]>100){SUCTION_T[39]=100;}break;			
					default:
						U485_OUT;
						printf("ADNUMERR");
						U485_IN;
						break;					
			}		
		}				
		}	 
}


void MAGNET_Test()
{	
	Q_485.rx_len=8;
	magnet_buf[0]=1;magnet_buf[1]=25;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);

	Q_485.rx_len=8;
	magnet_buf[0]=2;magnet_buf[1]=25;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);

	Q_485.rx_len=8;
	magnet_buf[0]=3;magnet_buf[1]=35;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);

	Q_485.rx_len=8;
	magnet_buf[0]=4;magnet_buf[1]=25;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);

	Q_485.rx_len=8;
		magnet_buf[0]=5;magnet_buf[1]=25;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);

	Q_485.rx_len=8;
		magnet_buf[0]=6;magnet_buf[1]=26;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);
	
	Q_485.rx_len=8;
		magnet_buf[0]=7;magnet_buf[1]=27;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);
Q_485.rx_len=8;
		magnet_buf[0]=8;magnet_buf[1]=28;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);

	Q_485.rx_len=8;
		magnet_buf[0]=9;magnet_buf[1]=29;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);

	Q_485.rx_len=8;
		magnet_buf[0]=10;magnet_buf[1]=30;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);

	Q_485.rx_len=8;
		magnet_buf[0]=11;magnet_buf[1]=31;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);

	Q_485.rx_len=8;
		magnet_buf[0]=12;magnet_buf[1]=32;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);

	Q_485.rx_len=12;
	magnet_buf[0]=13;magnet_buf[1]=32;magnet_buf[2]=14;magnet_buf[3]=32;magnet_buf[4]=15;magnet_buf[5]=32;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);
	
	Q_485.rx_len=16;
	magnet_buf[0]=16;magnet_buf[1]=32;magnet_buf[2]=17;magnet_buf[3]=32;magnet_buf[4]=18;magnet_buf[5]=32;magnet_buf[6]=19;magnet_buf[7]=32;magnet_buf[8]=20;magnet_buf[9]=32;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);
	
		Q_485.rx_len=16;
	magnet_buf[0]=21;magnet_buf[1]=32;magnet_buf[2]=22;magnet_buf[3]=32;magnet_buf[4]=23;magnet_buf[5]=32;magnet_buf[6]=24;magnet_buf[7]=32;magnet_buf[8]=25;magnet_buf[9]=32;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);
	
		Q_485.rx_len=16;
	magnet_buf[0]=26;magnet_buf[1]=32;magnet_buf[2]=27;magnet_buf[3]=32;magnet_buf[4]=28;magnet_buf[5]=32;magnet_buf[6]=29;magnet_buf[7]=32;magnet_buf[8]=30;magnet_buf[9]=32;
	MAGNET_FLAG=1;
	MAGNET_Manage();
	delay_ms(1000);


}


