#ifndef __MAGNET_H
#define __MAGNET_H

#include "stm32f0xx.h"

extern void MAGNETInit(void);
extern void MAGNET_Manage(void);
extern void MAGNET_Test(void);

extern volatile uint8_t MAGNET_FLAG;
extern uint8_t magnet_buf[20];
extern uint8_t magnet_timer_flag[40];


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

#define M1open GPIO_SetBits(GPIOC,GPIO_Pin_3)
#define M1close GPIO_ResetBits(GPIOC,GPIO_Pin_3)

#define M2open GPIO_SetBits(GPIOA,GPIO_Pin_0)
#define M2close GPIO_ResetBits(GPIOA,GPIO_Pin_0)

#define M3open  GPIO_SetBits(GPIOC,GPIO_Pin_2)
#define M3close  GPIO_ResetBits(GPIOC,GPIO_Pin_2)

#define M4open   GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define M4close  GPIO_ResetBits(GPIOA,GPIO_Pin_1)

#define M5open GPIO_SetBits(GPIOD,GPIO_Pin_2)                                    //M3
#define M5close  GPIO_ResetBits(GPIOD,GPIO_Pin_2)

#define M6open GPIO_SetBits(GPIOC,GPIO_Pin_14) //M13
#define M6close  GPIO_ResetBits(GPIOC,GPIO_Pin_14)

#define M7open GPIO_SetBits(GPIOC,GPIO_Pin_12)              //M4
#define M7close GPIO_ResetBits(GPIOC,GPIO_Pin_12)

#define M8open  GPIO_SetBits(GPIOC,GPIO_Pin_15)        //M14                                  
#define M8close GPIO_ResetBits(GPIOC,GPIO_Pin_15)

#define M9open GPIO_SetBits(GPIOC,GPIO_Pin_11)    //M5
#define M9close  GPIO_ResetBits(GPIOC,GPIO_Pin_11)

#define M10open GPIO_SetBits(GPIOC,GPIO_Pin_0)//M15
#define M10close GPIO_ResetBits(GPIOC,GPIO_Pin_0)

#define M11open  GPIO_SetBits(GPIOC,GPIO_Pin_10)//M6
#define M11close  GPIO_ResetBits(GPIOC,GPIO_Pin_10)
 
#define M12open  GPIO_SetBits(GPIOC,GPIO_Pin_1)//M16
#define M12close GPIO_ResetBits(GPIOC,GPIO_Pin_1)

#define M13open GPIO_SetBits(GPIOB,GPIO_Pin_6)    //M7
#define M13close GPIO_ResetBits(GPIOB,GPIO_Pin_6)

#define M14open GPIO_SetBits(GPIOB,GPIO_Pin_7)   //M17
#define M14close GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define M15open GPIO_SetBits(GPIOB,GPIO_Pin_5) //  M8
#define M15close GPIO_ResetBits(GPIOB,GPIO_Pin_5)

#define M16open GPIO_SetBits(GPIOB,GPIO_Pin_8)//M18
#define M16close GPIO_ResetBits(GPIOB,GPIO_Pin_8)

#define M17open GPIO_SetBits(GPIOB,GPIO_Pin_4)//M9
#define M17close GPIO_ResetBits(GPIOB,GPIO_Pin_4)

#define M18open GPIO_SetBits(GPIOB,GPIO_Pin_9)//M19
#define M18close GPIO_ResetBits(GPIOB,GPIO_Pin_9)

#define M19open GPIO_SetBits(GPIOB,GPIO_Pin_3)   //M10
#define M19close GPIO_ResetBits(GPIOB,GPIO_Pin_3)

#define M20open GPIO_SetBits(GPIOC,GPIO_Pin_13)//
#define M20close GPIO_ResetBits(GPIOC,GPIO_Pin_13)

#define M21open GPIO_SetBits(GPIOC,GPIO_Pin_6)
#define M21close GPIO_ResetBits(GPIOC,GPIO_Pin_6)

#define M22open GPIO_SetBits(GPIOB,GPIO_Pin_2)//M31
#define M22close GPIO_ResetBits(GPIOB,GPIO_Pin_2)

#define M23open GPIO_SetBits(GPIOB,GPIO_Pin_15)//M22
#define M23close GPIO_ResetBits(GPIOB,GPIO_Pin_15)

#define M24open GPIO_SetBits(GPIOB,GPIO_Pin_10)//M32
#define M24close  GPIO_ResetBits(GPIOB,GPIO_Pin_10)

#define M25open GPIO_SetBits(GPIOB,GPIO_Pin_14) //M23
#define M25close GPIO_ResetBits(GPIOB,GPIO_Pin_14) 

#define M26open GPIO_SetBits(GPIOB,GPIO_Pin_11)//M33
#define M26close GPIO_ResetBits(GPIOB,GPIO_Pin_11)

#define M27open GPIO_SetBits(GPIOB,GPIO_Pin_13)//M24 
#define M27close GPIO_ResetBits(GPIOB,GPIO_Pin_13) 

#define M28open GPIO_SetBits(GPIOB,GPIO_Pin_12)  //M34
#define M28close GPIO_ResetBits(GPIOB,GPIO_Pin_12)

#define M29open  GPIO_SetBits(GPIOA,GPIO_Pin_8)//M25
#define M29close  GPIO_ResetBits(GPIOA,GPIO_Pin_8)

#define M30open  GPIO_SetBits(GPIOC,GPIO_Pin_4)//M35
#define M30close GPIO_ResetBits(GPIOC,GPIO_Pin_4)

#define M31open GPIO_SetBits(GPIOC,GPIO_Pin_9) //M26
#define M31close GPIO_ResetBits(GPIOC,GPIO_Pin_9) 

#define M32open GPIO_SetBits(GPIOC,GPIO_Pin_5)//M36
#define M32close GPIO_ResetBits(GPIOC,GPIO_Pin_5)

#define M33open GPIO_SetBits(GPIOC,GPIO_Pin_8)  //M27
#define M33close GPIO_ResetBits(GPIOC,GPIO_Pin_8)  

#define M34open GPIO_SetBits(GPIOB,GPIO_Pin_0)//M37
#define M34close GPIO_ResetBits(GPIOB,GPIO_Pin_0)

#define M35open  GPIO_SetBits(GPIOC,GPIO_Pin_7)//M28
#define M35close GPIO_ResetBits(GPIOC,GPIO_Pin_7)

#define M36open  GPIO_SetBits(GPIOB,GPIO_Pin_1)//M38
#define M36close GPIO_ResetBits(GPIOB,GPIO_Pin_1)

#define M37open  GPIO_SetBits(GPIOA,GPIO_Pin_7) //M29
#define M37close GPIO_ResetBits(GPIOA,GPIO_Pin_7) 

#define M38open  GPIO_SetBits(GPIOA,GPIO_Pin_4)//M39
#define M38close GPIO_ResetBits(GPIOA,GPIO_Pin_4)

#define M39open GPIO_SetBits(GPIOA,GPIO_Pin_6) //M30
#define M39close GPIO_ResetBits(GPIOA,GPIO_Pin_6) 

#define M40open GPIO_SetBits(GPIOA,GPIO_Pin_5)
#define M40close GPIO_ResetBits(GPIOA,GPIO_Pin_5)



#endif
