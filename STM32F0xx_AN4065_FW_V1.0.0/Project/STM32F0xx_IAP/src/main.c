/**
  ******************************************************************************
  * @file    STM32F0xx_IAP/src/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    29-May-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "common.h"
#include "timer.h"
#include "wdg.h"
/** @addtogroup STM32F0xx_IAP
  * @{
  */
#define U485_OUT		GPIO_SetBits (GPIOA, GPIO_Pin_11);
#define U485_IN	GPIO_ResetBits (GPIOA, GPIO_Pin_11);
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern pFunction Jump_To_Application;
extern uint32_t JumpAddress;

/* Private function prototypes -----------------------------------------------*/
static void IAP_Init(void);
volatile uint8_t COUNT;
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

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
void u485_init()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
 /* Enable the GPIO_LED Clock */
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA,ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	U485_IN;
}

int main(void)
{
	uint8_t button1,button2,button3;	
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */ 
  
  /* Initialize Key Button mounted on STM320518-EVAL board */       
  STM_EVAL_PBInit(BUTTON_KEY, BUTTON_MODE_GPIO);   
	IAP_Init();
	MAGNETInit();
	u485_init();
	BspTim3Init();
	U485_OUT;
  SerialPutString("\r\n================== Main Menu ============================\r\n\n");
	U485_IN;
  /* Test if Key push-button on STM320518-EVAL Board is pressed */
	
	while((SerialKeyPressed(&button1)==0)&&(COUNT<=20))
	{
			
	}			
	
	if(COUNT>20)
	{
		button1=0x40;
	}
	
	COUNT=0;
	while((SerialKeyPressed(&button2)==0)&&(COUNT<=10))
	{
			
	}			
	if(COUNT>10)
	{
		button2=0x40;
	}
	
	//while((SerialKeyPressed(&button3)==0)&&(COUNT<=5))
	//{
			
	//}			
//	if(COUNT>20)
	//{
	//	button3=0x40;
	//}
	IWDG_Config(IWDG_Prescaler_256,500);
 // if (STM_EVAL_PBGetState(BUTTON_KEY) == 0x00)
	if((button1==0x31)&&(button2==0x32))//&&(button3==0x33))
  { 
    /* If Key is pressed, execute the IAP driver in order to re-program the Flash */
 //   IAP_Init();
    
    /* Display main menu */
    Main_Menu ();
  }  
  else
  {/* Keep the user application running */

    /* Test if user code is programmed starting from address "APPLICATION_ADDRESS" */
    if (((*(__IO uint32_t*)APPLICATION_ADDRESS) & 0x2FFE0000 ) == 0x20000000)
    { 
      /* Jump to user application */
      JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
      Jump_To_Application = (pFunction) JumpAddress;
      
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
      
      /* Jump to application */
      Jump_To_Application();
    }
  }

  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  Initialize the IAP.
  * @param  None
  * @retval None
  */
void IAP_Init(void)
{
 USART_InitTypeDef USART_InitStructure;

  /* Unlock the Flash Program Erase controller */
  FLASH_If_Init();

  /* USART resources configuration (Clock, GPIO pins and USART registers) ----*/
  /* USART configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  STM_EVAL_COMInit(COM1, &USART_InitStructure);
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
