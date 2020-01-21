#include <stm32f10x.h>   
#include "BspTime.h"
#include "common.h"


/*************�ⲿ����****************/
extern pFunction Jump_To_Application;
extern uint32_t JumpAddress;
/***********************************/
void delay(uint8_t num)
{
	u8 i;
	if(i>10)
	{
		i++;
	while(num--);
		num=200;
	}
}
void GPIO_Configuration(void)
{
	//IO�����óɹ�ָʾ��
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC , ENABLE); 						 					 
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA , GPIO_Pin_12);
//	//GPIO_SetBits(GPIOB , GPIO_Pin_15);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC , GPIO_Pin_6);

   //��������
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
    // ���� USART1 Tx (PA.09) ��Ϊ�������Ų��������ģʽ
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

    //���� USART1 Tx (PA.10) ��Ϊ�������Ų��Ǹ�������ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}



void UART_Init(void)
{
    USART_InitTypeDef USART_InitStructure;

    /* USART1 ���� ------------------------------------------------------------
         USART1 ��������:
          - ������      = 115200 baud
          - �ֳ�        = 8 Bits
          - һ��ֹͣλ
          - ��У��
          - ��Ӳ��������
          - ���ܺͷ���ʹ��
    --------------------------------------------------------------------------*/
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    GPIO_Configuration();
	
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

int main(void) 	
{   
	SystemInit(); 
	GPIO_Configuration();		  
	//GPIO_SetBits(GPIOB , GPIO_Pin_13);
	//GPIO_SetBits(GPIOB , GPIO_Pin_15);
	FLASH_Unlock();
	UART_Init();
	BspTim2Init();
	GPIO_SetBits(GPIOC , GPIO_Pin_6);
  SerialPutString("bootloader\r\n");
	delay(200);
	GPIO_ResetBits(GPIOC , GPIO_Pin_6);
  Main_Menu ();
	 
	if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)
            {
//                SerialPutString("Execute user Program\r\n\n");
                BspTim2Close();
                //��ת���û�����
                JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
                Jump_To_Application = (pFunction) JumpAddress;

                //��ʼ���û�����Ķ�ջָ��
                __set_MSP(*(__IO uint32_t*) ApplicationAddress);
                Jump_To_Application();
            }
            else
            {
                SerialPutString("no user Program\r\n\n");
            }
	
  while(1); 
}
