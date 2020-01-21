#ifndef __U485_H
#define __U485_H
#include "stm32f0xx.h"


#define U485_OUT		GPIO_SetBits (GPIOA, GPIO_Pin_11);
#define U485_IN	GPIO_ResetBits (GPIOA, GPIO_Pin_11);

#define RXBUF_485_MAX 100
typedef struct 
{
    uint8_t queue[RXBUF_485_MAX];
    volatile uint8_t count;    
		volatile uint8_t rx_flag;
		volatile uint8_t rx_len;  
    volatile uint8_t frame_ready; // frame ready flag 
} QUEUE_485_t;

extern QUEUE_485_t Q_485;
extern volatile uint8_t OUTLOCK_FLAG;
extern volatile uint16_t SUCTION_TIME;
extern volatile uint8_t U485_FLAG;
extern volatile uint8_t OUTLOCK_TIME_FLAG;
extern void u485_init(uint32_t bound);
extern void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
extern void u485_tick(void);
#endif
