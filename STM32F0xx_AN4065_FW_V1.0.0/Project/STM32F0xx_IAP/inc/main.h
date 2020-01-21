/**
  ******************************************************************************
  * @file    STM32F0xx_IAP/inc/main.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    29-May-2012
  * @brief   Header for main.c module
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
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stm320518_eval.h"
#include <stdio.h>
#include "menu.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#define M1_Pin GPIO_Pin_3
#define M2_Pin GPIO_Pin_2
#define M3_Pin GPIO_Pin_2
#define M4_Pin GPIO_Pin_12
#define M5_Pin GPIO_Pin_11
#define M6_Pin GPIO_Pin_10
#define M7_Pin GPIO_Pin_6
#define M8_Pin GPIO_Pin_5
#define M9_Pin GPIO_Pin_4
#define M10_Pin GPIO_Pin_3

#define M11_Pin GPIO_Pin_0
#define M12_Pin GPIO_Pin_1
#define M13_Pin GPIO_Pin_15
#define M14_Pin GPIO_Pin_14
#define M15_Pin GPIO_Pin_0
#define M16_Pin GPIO_Pin_1
#define M17_Pin GPIO_Pin_7
#define M18_Pin GPIO_Pin_8
#define M19_Pin GPIO_Pin_9
#define M20_Pin GPIO_Pin_13

#define M21_Pin GPIO_Pin_6
#define M22_Pin GPIO_Pin_15
#define M23_Pin GPIO_Pin_14
#define M24_Pin GPIO_Pin_13
#define M25_Pin GPIO_Pin_8
#define M26_Pin GPIO_Pin_9
#define M27_Pin GPIO_Pin_8
#define M28_Pin GPIO_Pin_7
#define M29_Pin GPIO_Pin_7
#define M30_Pin GPIO_Pin_6

#define M31_Pin GPIO_Pin_2
#define M32_Pin GPIO_Pin_10
#define M33_Pin GPIO_Pin_11
#define M34_Pin GPIO_Pin_12
#define M35_Pin GPIO_Pin_4
#define M36_Pin GPIO_Pin_5
#define M37_Pin GPIO_Pin_0
#define M38_Pin GPIO_Pin_1
#define M39_Pin GPIO_Pin_4
#define M40_Pin GPIO_Pin_5

extern volatile uint8_t COUNT;
void Display_Init(void);
void Display(void);
#define U485_OUT		GPIO_SetBits (GPIOA, GPIO_Pin_11);
#define U485_IN	GPIO_ResetBits (GPIOA, GPIO_Pin_11);
#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

