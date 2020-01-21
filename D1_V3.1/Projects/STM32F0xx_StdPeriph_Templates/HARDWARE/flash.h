#ifndef __FLASH_H
#define __FLASH_H
#include "stm32f0xx.h"

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
//�û������Լ�����Ҫ����
#define STM32_FLASH_SIZE 64 	 //��ѡSTM32��FLASH������С(��λΪK)

//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH����ʼ��ַ
 
extern vu16 STM32_FLASH_ReadHalfWord(u32 faddr); 
extern void STM32_FLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
extern void STM32_FLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����
					   


#endif
