#include "u485.h"
#include "string.h"
#include "stm32f0xx.h"
#include "stdio.h"
#include "flash.h"
#include "crc.h"
#include "magnet.h"
#include "main.h"
uint8_t table[10]={0x41,0x44,0x1F,0x04,0x20,0x08,0x27,0x99,0x28,0x50};
uint8_t a,b,c,d;
enum { ADDR_BIT=0,CMD_BIT,DATA_BIT};
QUEUE_485_t Q_485;
char sendbuf[50];
volatile uint8_t U485_FLAG;
volatile uint16_t SUCTION_TIME;
volatile uint8_t OUTLOCK_FLAG;
volatile uint8_t OUTLOCK_TIME_FLAG;
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{  
  USART1->TDR = (uint8_t) ch; 
	while((USART1->ISR&0X40)==0);//循环发送,直到发送完毕   
 // USART1->TDR = (uint8_t) ch; 
	USART_ClearFlag(USART1, USART_FLAG_TC);	
	return ch;
}
#endif 


void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
      
        USART_SendData(pUSARTx,ch);
            
        while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET); 
				USART_ClearFlag(USART1, USART_FLAG_TC);
				
}

void Usart_SendString(USART_TypeDef * pUSARTx, uint8_t* p,uint8_t num)
{
	uint8_t i;
	for(i=0;i<num;i++)
	{
		Usart_SendByte( pUSARTx, *p++);
	}
} 
  
void u485_init(uint32_t bound)
{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 ,ENABLE);	//使能USART1，GPIOA时钟
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA,ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
 // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//浮空输入
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  //GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  
	
	//485 EN 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

   		

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=2 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
	USART_ClearITPendingBit(USART1, USART_IT_TC); 
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
	 USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

  USART_Cmd(USART1, ENABLE);                    //使能串口1 
}


void u485_queue_init(void)
{
	uint8_t i;
	for(i=0;i<Q_485.rx_len;i++)
	{
		Q_485.queue[i]=0;
	}
  Q_485.queue[0] = 0x00;
  Q_485.count = 0;
	Q_485.frame_ready=0;
	Q_485.rx_flag=1;
	Q_485.rx_len=0;
}
void USART1_IRQHandler(void)             
	{
	uint8_t Res,clr;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)   //RX Interrupt
		{
			
			Res =USART_ReceiveData(USART1);	
		
			if(Q_485.rx_flag==1)     //first data flag
			{
				Q_485.rx_flag=0;
				Q_485.count=0;
				Q_485.frame_ready=0;
				Q_485.rx_len=0;
			}
						
			Q_485.queue[Q_485.count]=Res; 
			Q_485.count++;
			
			if(Q_485.count>= RXBUF_485_MAX)
			{
					u485_queue_init();	
			}
     } 
	else if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)    //IDLE interrupt  
	{
	
			USART_ClearFlag(USART1, USART_FLAG_IDLE);
			Q_485.rx_flag=1;
			Q_485.frame_ready=1;
			Q_485.rx_len=Q_485.count;
			Q_485.count=0;
	}
}
	
void u485_send_crc(uint32_t crcdata,uint8_t *p,uint8_t len)
{
	U485_OUT;
  Usart_SendString(USART1,p,len);
  Usart_SendByte( USART1,(uint8_t)(crcdata>>24));
  Usart_SendByte( USART1,((uint8_t)(crcdata>>16))&0xff);
	Usart_SendByte( USART1,((uint8_t)(crcdata>>8))&0xff);
	Usart_SendByte( USART1,(uint8_t)(crcdata&0xff));
	printf("\r\n");
	U485_IN;	
}	

void u485_tick()
{  
	uint8_t i;
	uint32_t crc_data;

	if(Q_485.frame_ready==1)
	{		
		Q_485.frame_ready=0;
		
		if(Q_485.queue[ADDR_BIT]==STOREY_NUM)
		{
				crc_data=crc_calculate((char*)(Q_485.queue),Q_485.rx_len-4);			
	//		crc_data=crc_calculate(table,10);
		//	a=crc_data >> 24;
		//	b=((crc_data >> 16)&0xff); 
		//	c=((crc_data >> 8)&0xff);
		//	d=(crc_data & 0xff);
	
			if ((crc_data >> 24) ==Q_485.queue[Q_485.rx_len-4] &&
				 	((crc_data >> 16)&0xff) ==Q_485.queue[Q_485.rx_len-3] &&
				  ((crc_data >> 8)&0xff) == Q_485.queue[Q_485.rx_len-2] &&
         (crc_data & 0xff) ==Q_485.queue[Q_485.rx_len-1])
				{
				/*	if(STOREY_NUM=='E')
					{
						switch(Q_485.queue[CMD_BIT])
						{
							case 'L':M30open;
							sendbuf[0]=STOREY_NUM;
							snprintf(sendbuf,5,"%sDOK",sendbuf);
							crc_data=crc_calculate(sendbuf,4);						
							u485_send_crc(crc_data,(uint8_t*)sendbuf,4);					
							break;
							case 'M':M30close;
							sendbuf[0]=STOREY_NUM;
							snprintf(sendbuf,5,"%sDOK",sendbuf);
							crc_data=crc_calculate(sendbuf,4);						
							u485_send_crc(crc_data,(uint8_t*)sendbuf,4);					
							break;
							case 'X':OUTLOCK_FLAG=1;
							sendbuf[0]=STOREY_NUM;
							snprintf(sendbuf,5,"%sDOK",sendbuf);
							crc_data=crc_calculate(sendbuf,4);						
							u485_send_crc(crc_data,(uint8_t*)sendbuf,4);					
							break;
						}
					}*/
					switch(Q_485.queue[CMD_BIT])
					{
						case 'L':    //led on
						if(STOREY_NUM=='E')
						{
							 M39open;			
							 sendbuf[0]=STOREY_NUM;
							 snprintf(sendbuf,5,"%sDOK",sendbuf);
							 crc_data=crc_calculate(sendbuf,4);						
							 u485_send_crc(crc_data,(uint8_t*)sendbuf,4);										
						}
						break;
							
						case 'M':
						if(STOREY_NUM=='E')   //led off
						{
							
								M39close;
								sendbuf[0]=STOREY_NUM;
								snprintf(sendbuf,5,"%sDOK",sendbuf);
								crc_data=crc_calculate(sendbuf,4);						
								u485_send_crc(crc_data,(uint8_t*)sendbuf,4);												
						}							
						break;
							
						case 'X':     //magnet 
						if(STOREY_NUM=='E')
						{		
								OUTLOCK_FLAG=1;
								OUTLOCK_TIME_FLAG=1;
								sendbuf[0]=STOREY_NUM;
								snprintf(sendbuf,5,"%sDOK",sendbuf);
								crc_data=crc_calculate(sendbuf,4);						
								u485_send_crc(crc_data,(uint8_t*)sendbuf,4);												
						}
						break;			
							
						case 'D':  //gravity magnet  
						if(Q_485.rx_len>22)
						{
							U485_OUT;
							sendbuf[0]=STOREY_NUM;
							snprintf(sendbuf,12,"%sDNUMEXCEED",sendbuf);
						  printf("sendbuf\r\n");
							U485_IN;
							break;
						}
						if(Q_485.rx_len%2==0)
						{
							MAGNET_FLAG=1;						
							//U485_OUT;
							//printf("qaa\r\n");
							//U485_IN;
							sendbuf[0]=STOREY_NUM;
							snprintf(sendbuf,5,"%sDOK",sendbuf);
							crc_data=crc_calculate(sendbuf,4);						
							u485_send_crc(crc_data,(uint8_t*)sendbuf,4);					
						
							for(i=0;i<=Q_485.rx_len-7;i++)
							{
								magnet_buf[i]=Q_485.queue[i+2];
							}
			  		}
						else 
						{							
							sendbuf[0]=STOREY_NUM;
							snprintf(sendbuf,7,"%sDDERR",sendbuf);				
							crc_data=crc_calculate(sendbuf,6);						
							u485_send_crc(crc_data,(uint8_t*)sendbuf,6);						
						}
						break;       //Suction magnet
							
					/*	case 'S':
							SUCTION_TIME=	(uint16_t)(Q_485.queue[DATA_BIT]);
							STM32_FLASH_Wri   te(0x08009000,&SUCTION_TIME,1);
							snprintf(sendbuf, 3, "MS%x", Q_485.queue[DATA_BIT]);
							crc_data=crc_calculate(sendbuf,sizeof(sendbuf)-1);						
							u485_send_crc(crc_data,(uint8_t*)sendbuf,3);						
							break;       //set the time of suction magnet 	*/											
						case 'V': 
						U485_OUT;	
						printf("version 2/r/n magnet reorder/r/n 2019/11/13/r/n");	
						U485_IN;
						break;
						
						default:
							sendbuf[0]=STOREY_NUM;
							snprintf(sendbuf,9,"%sDCMDERR",sendbuf);		
							crc_data=crc_calculate(sendbuf,8);						
							u485_send_crc(crc_data,(uint8_t*)sendbuf,8);
							break;
					}			
				}			   
	   }		
		else if((Q_485.queue[ADDR_BIT]=='R')&&(Q_485.queue[1]=='E')&&(Q_485.queue[2]=='S')&&(Q_485.queue[3]=='E')&&(Q_485.queue[4]=='T'))
		{
				
				if(Q_485.queue[5]==STOREY_NUM)
				{
					U485_OUT;
					printf("MCURESET\r\n");
					U485_IN;
					NVIC_SystemReset();
				}
				else
				{
					U485_FLAG=1;
					USART_Cmd(USART1, DISABLE);    
				}
		}
		
		for(i=0;i<Q_485.rx_len;i++)
		{
			Q_485.queue[i]=0;
		}
	}
}

