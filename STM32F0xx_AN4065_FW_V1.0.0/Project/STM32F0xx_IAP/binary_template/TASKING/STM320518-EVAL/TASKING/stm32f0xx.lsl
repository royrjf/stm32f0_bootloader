///////////////////////////////////////////////////////////////////////////
//
//  File        :  stm32f0xx.lsl
//
//  Version     :  @(#)stm32f0xx.lsl    1.5  11/06/30
//
//  Description :  LSL file for the STMicroelectronics STM32F0xx
//
//  Copyright 2010-2011 Altium BV
//  
//  Macros specific to control this LSL file
//
//  __MEMORY            Define this macro to suppress definition of on-chip 
//                      memory. Must be defined when you want to define on-chip
//                      in your project's LSL file.
//  __FLASH_SIZE        Specifies the size of flash memory to be allocated
//  __SRAM_SIZE         Specifies the size of the SRAM memory to be allocated
//  __EEPROM_SIZE       Specifies the size of the EEPROM memory to be allocated
//  __NO_DEFAULT_AUTO_VECTORS
//                      When enabled the interrupt vector table will not be 
//                      generated
//  __VECTOR_TABLE_RAM_COPY
//                      Define this macro to enable copying the vector table 
//                      at startup from ROM to RAM.
//  __VECTOR_TABLE_ROM_ADDR
//                      Specify the vector table address in ROM
//  __VECTOR_TABLE_RAM_ADDR
//                      Specify the vector table address in RAM when the the
//                      it is copied from ROM to RAM (__VECTOR_TABLE_RAM_COPY)
//
//  See arm_arch.lsl for more available macros.
//
//  Notes:
//  In the STM32F0xx, 3 different boot modes can be selected
//  - User Flash memory is selected as boot space
//  - SystemMemory is selected as boot space
//  - Embedded SRAM is selected as boot space
//
//  This aliases the physical memory associated with each boot mode to Block
//  000 (0x00000000 boot memory). Even when aliased in the boot memory space,
//  the related memory (Flash memory or SRAM) is still accessible at its
//  original memory space.
//
////////////////////////////////////////////////////////////////////////////

#ifndef __NO_DEFAULT_AUTO_VECTORS
// Suppress the vectors as defined arm_arch.lsl, because we define our 
// own vectors for CMIS
#define __CMSIS_VECTORS                 1
#define __NO_DEFAULT_AUTO_VECTORS       1
#define __NR_OF_VECTORS                47
#endif

#ifndef __VECTOR_TABLE_ROM_ADDR
#  define __VECTOR_TABLE_ROM_ADDR       0x08003000
#endif

#ifndef __VECTOR_TABLE_RAM_ADDR
#  define __VECTOR_TABLE_RAM_ADDR       0x00000000
#endif


#ifndef __STACK
#  define __STACK                       4k
#endif

#ifndef __HEAP
#  define __HEAP                        2k
#endif

#include <arm_arch.lsl>

//
//  If no memory is defined yet use the following memory settings
//
#ifndef __MEMORY

// Specify default size for Flash and SRAM
#ifndef __FLASH_SIZE
#  define __FLASH_SIZE  64k
#endif
#ifndef __SRAM_SIZE
#  define __SRAM_SIZE   8k
#endif

memory STM32F0xx_Flash
{
    mau = 8;
    type = rom;
    size = __FLASH_SIZE - 8K;
    map ( size = __FLASH_SIZE - 8K, dest_offset=0x08003000, dest=bus:ARM:local_bus);
}

memory STM32F0xx_SRAM
{
    mau = 8;
    type = ram;
    size = __SRAM_SIZE;
    map ( size = __SRAM_SIZE, dest_offset=0x20000000, dest=bus:ARM:local_bus);
}

#endif /* __MEMORY */


//
// Custom vector table defines interrupts according to CMSIS standard
//
# if defined(__CPU_ARMV6M__)
section_setup ::linear
{
                // vector table with handler addresses
                vector_table "vector_table" ( vector_size = 4, size = __NR_OF_VECTORS, run_addr = __VECTOR_TABLE_RUN_ADDR,
                                              template = ".text.handler_address",
                                              template_symbol = "_lc_vector_handler",
                                              vector_prefix = "_vector_",
                                              __VECTOR_TABLE_COPY_ATTRIBUTE 
                                              fill = loop,
                                              no_inline
                                            )
                {
                        vector ( id = 0, fill = "_lc_ub_stack" );                               // Top of Stack
                        vector ( id = 1, fill = "_START" );                              // Reset Handler
                        vector ( id = 2, optional, fill = "NMI_Handler" );
                        vector ( id = 3, optional, fill = "HardFault_Handler" );
                        vector ( id = 11, optional, fill = "SVC_Handler" );
                        vector ( id = 14, optional, fill = "PendSV_Handler" );
                        vector ( id = 15, optional, fill = "SysTick_Handler" );

                        // External Interrupts :
                        vector ( id = 16, optional, fill = "WWDG_IRQHandler" );                 // Window Watchdog
                        vector ( id = 17, optional, fill = "PVD_IRQHandler" );                  // PVD through EXTI Line detect
                        vector ( id = 18, optional, fill = "RTC_IRQHandler" );                  // RTC
                        vector ( id = 19, optional, fill = "FLASH_IRQHandler" );                // Flash
                        vector ( id = 20, optional, fill = "RCC_IRQHandler" );                  // RCC
                        vector ( id = 21, optional, fill = "EXTI0_1_IRQHandler" );              // EXTI Line 0 and 1
                        vector ( id = 22, optional, fill = "EXTI2_3_IRQHandler" );              // EXTI Line 2 and 3
                        vector ( id = 23, optional, fill = "EXTI4_15_IRQHandler" );             // EXTI Line 4 to 15
                        vector ( id = 24, optional, fill = "TS_IRQHandler" );                   // TS
                        vector ( id = 25, optional, fill = "DMA1_Channel1_IRQHandler" );        // DMA1 Channel 1
                        vector ( id = 26, optional, fill = "DMA1_Channel2_3_IRQHandler" );      // DMA1 Channel 2 and Channel 3
                        vector ( id = 27, optional, fill = "DMA1_Channel4_5_IRQHandler" );      // DMA1 Channel 4 and Channel 5
                        vector ( id = 28, optional, fill = "ADC1_COMP_IRQHandler" );            // ADC1, COMP1 and COMP2
                        vector ( id = 29, optional, fill = "TIM1_BRK_UP_TRG_COM_IRQHandler" );  // TIM1 Break, Update, Trigger and Commutation
                        vector ( id = 30, optional, fill = "TIM1_CC_IRQHandler" );              // TIM1 Capture Compare
                        vector ( id = 31, optional, fill = "TIM2_IRQHandler" );                 // TIM2
                        vector ( id = 32, optional, fill = "TIM3_IRQHandler" );                 // TIM3
                        vector ( id = 33, optional, fill = "TIM6_DAC_IRQHandler" );             // TIM6 and DAC
                        vector ( id = 35, optional, fill = "TIM14_IRQHandler" );                //  TIM14
                        vector ( id = 36, optional, fill = "TIM15_IRQHandler" );                // TIM15
                        vector ( id = 37, optional, fill = "TIM16_IRQHandler" );                // TIM16
                        vector ( id = 38, optional, fill = "TIM17_IRQHandler" );                // TIM17
                        vector ( id = 39, optional, fill = "I2C1_IRQHandler" );                 // I2C1
                        vector ( id = 40, optional, fill = "I2C2_IRQHandler" );                 // I2C2
                        vector ( id = 41, optional, fill = "SPI1_IRQHandler" );                 // SPI1
                        vector ( id = 42, optional, fill = "SPI2_IRQHandler" );                 // SPI2
                        vector ( id = 43, optional, fill = "USART1_IRQHandler" );               // USART1
                        vector ( id = 44, optional, fill = "USART2_IRQHandler" );               // USART2
                        vector ( id = 46, optional, fill = "CEC_IRQHandler" );                  // CEC
                                              
                }
}
# endif
