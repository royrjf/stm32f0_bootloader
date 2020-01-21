/*******************************************************************************
** 文件名: 		common.c
** 版本：  		1.0
** 工作环境: 	RealView MDK-ARM 5.20
** 作者: 		liupeng
** 生成日期: 	2016-03-20
** 功能:		显示主菜单。主菜单上显示一系列操作，如加载二进制文件、
                执行应用程序以及禁止写保护(如果事先Flash被写保护)。
** 相关文件:	common.h，ymodem.h
** 修改日志：	2016-03-20   创建文档
*******************************************************************************/

/* 包含头文件 *****************************************************************/
#include "common.h"
#include "ymodem.h"
#include "BspTime.h"
#include "wdg.h"
/* 变量 ----------------------------------------------------------------------*/
pFunction Jump_To_Application;
uint32_t JumpAddress;
uint32_t BlockNbr = 0, UserMemoryMask = 0;
__IO uint32_t FlashProtection = 0;
extern uint32_t FlashDestination;


/*******************************************************************************
  * @函数名称：Int2Str
  * @函数说明：整形数据转到字符串
  * @输入参数：intnum:数据
  * @输出参数：str：转换为的字符串
  * @返回参数：无
  * @历史记录:     
     <作者>    <时间>      <修改记录>
*******************************************************************************/
void Int2Str(uint8_t* str, int32_t intnum)
{
    uint32_t i, Div = 1000000000, j = 0, Status = 0;

    for (i = 0; i < 10; i++)
    {
        str[j++] = (intnum / Div) + 48;

        intnum = intnum % Div;
        Div /= 10;
        if ((str[j-1] == '0') & (Status == 0))
        {
            j = 0;
        }
        else
        {
            Status++;
        }
    }
}

/*******************************************************************************
  * @函数名称：Int2Str
  * @函数说明：字符串转到数据
  * @输入参数：inputstr:需转换的字符串
  * @输出参数：intnum：转好的数据
  * @返回参数：转换结果
               1：正确
               0：错误
  * @历史记录:     
     <作者>    <时间>      <修改记录>
*******************************************************************************/
uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum)
{
    uint32_t i = 0, res = 0;
    uint32_t val = 0;

    if (inputstr[0] == '0' && (inputstr[1] == 'x' || inputstr[1] == 'X'))
    {
        if (inputstr[2] == '\0')
        {
            return 0;
        }
        for (i = 2; i < 11; i++)
        {
            if (inputstr[i] == '\0')
            {
                *intnum = val;
                //返回1
                res = 1;
                break;
            }
            if (ISVALIDHEX(inputstr[i]))
            {
                val = (val << 4) + CONVERTHEX(inputstr[i]);
            }
            else
            {
                //无效输入返回0
                res = 0;
                break;
            }
        }

        if (i >= 11)
        {
            res = 0;
        }
    }
    else//最多10为2输入
    {
        for (i = 0; i < 11; i++)
        {
            if (inputstr[i] == '\0')
            {
                *intnum = val;
                //返回1
                res = 1;
                break;
            }
            else if ((inputstr[i] == 'k' || inputstr[i] == 'K') && (i > 0))
            {
                val = val << 10;
                *intnum = val;
                res = 1;
                break;
            }
            else if ((inputstr[i] == 'm' || inputstr[i] == 'M') && (i > 0))
            {
                val = val << 20;
                *intnum = val;
                res = 1;
                break;
            }
            else if (ISVALIDDEC(inputstr[i]))
            {
                val = val * 10 + CONVERTDEC(inputstr[i]);
            }
            else
            {
                //无效输入返回0
                res = 0;
                break;
            }
        }
        //超过10位无效，返回0
        if (i >= 11)
        {
            res = 0;
        }
    }

    return res;
}

/*******************************************************************************
  * @函数名称：Int2Str
  * @函数说明：字符串转到数据
  * @输入参数：inputstr:需转换的字符串
  * @输出参数：intnum：转好的数据
  * @返回参数：转换结果
               1：正确
               0：错误
  * @历史记录:     
     <作者>    <时间>      <修改记录>
*******************************************************************************/
/**
  * @brief  Get an integer from the HyperTerminal
  * @param  num: The inetger
  * @retval 1: Correct
  *         0: Error
  */
uint32_t GetIntegerInput(int32_t * num)
{
    uint8_t inputstr[16];

    while (1)
    {
        GetInputString(inputstr);
        if (inputstr[0] == '\0') continue;
        if ((inputstr[0] == 'a' || inputstr[0] == 'A') && inputstr[1] == '\0')
        {
            SerialPutString("User Cancelled \r\n");
            return 0;
        }

        if (Str2Int(inputstr, num) == 0)
        {
            SerialPutString("Error, Input again: \r\n");
        }
        else
        {
            return 1;
        }
    }
}

/*******************************************************************************
  * @函数名称：SerialKeyPressed
  * @函数说明：测试超级终端是否有按键按下
  * @输入参数：key:按键
  * @输出参数：无
  * @返回参数：1：正确
               0：错误
  * @历史记录:     
     <作者>    <时间>      <修改记录>
*******************************************************************************/
uint32_t SerialKeyPressed(uint8_t *key)
{

    if ( USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
    {
        *key = (uint8_t)USART1->DR;
        return 1;
    }
    else
    {
        return 0;
    }
}

/*******************************************************************************
  * @函数名称：GetKey
  * @函数说明：通过超级中断回去键码
  * @输入参数：无
  * @输出参数：无
  * @返回参数：按下的键码
  * @历史记录:     
     <作者>    <时间>      <修改记录>
*******************************************************************************/
uint8_t GetKey(void)
{
    uint8_t key = 0;

    //等待按键按下
    while (IS_TIMEOUT_1MS(eTim2, 3000))
    {
        if (SerialKeyPressed((uint8_t*)&key)) break;
    }
    return key;

}

/*******************************************************************************
  * @函数名称：SerialPutChar
  * @函数说明：串口发送一个字符
  * @输入参数：C:需发送的字符
  * @输出参数：无
  * @返回参数：无
  * @历史记录:     
     <作者>    <时间>      <修改记录>
*******************************************************************************/
void SerialPutChar(uint8_t c)
{
    //USART_SendData(USART1, c);
    //while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
    //{
   // }
	
	     GPIO_SetBits(GPIOC,GPIO_Pin_6);             //???????

        USART_SendData(USART1, c);    
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);                
        GPIO_ResetBits(GPIOC,GPIO_Pin_6);                              //???????
}

/*******************************************************************************
  * @函数名称：SerialPutChar
  * @函数说明：串口发送一个字符串
  * @输入参数：*s:需发送的字符串
  * @输出参数：无
  * @返回参数：无
  * @历史记录:     
     <作者>    <时间>      <修改记录>
*******************************************************************************/
void Serial_PutString(uint8_t *s)
{
    while (*s != '\0')
    {
        SerialPutChar(*s);
        s++;
    }
}


/*******************************************************************************
  * @函数名称：GetInputString
  * @函数说明：从串口获取一个字符串
  * @输入参数：*s:存字符串的地址
  * @输出参数：无
  * @返回参数：无
  * @历史记录:     
     <作者>    <时间>      <修改记录>
*******************************************************************************/
void GetInputString (uint8_t * buffP)
{
    uint32_t bytes_read = 0;
    uint8_t c = 0;
    do
    {
        c = GetKey();
        if (c == '\r')
            break;
        if (c == '\b')// Backspace 按键  
        {
            if (bytes_read > 0)
            {
                SerialPutString("\b \b");
                bytes_read --;
            }
            continue;
        }
        if (bytes_read >= CMD_STRING_SIZE )
        {
            SerialPutString("Command string size overflow\r\n");
            bytes_read = 0;
            continue;
        }
        if (c >= 0x20 && c <= 0x7E)
        {
            buffP[bytes_read++] = c;
            SerialPutChar(c);
        }
    }
    while (1);
    SerialPutString(("\n\r"));
    buffP[bytes_read] = '\0';
}

/*******************************************************************************
  * @函数名称：FLASH_PagesMask
  * @函数说明：计算Falsh页
  * @输入参数：Size:文件长度
  * @输出参数：无
  * @返回参数：页的数量
  * @历史记录:     
     <作者>    <时间>      <修改记录>
*******************************************************************************/
uint32_t FLASH_PagesMask(__IO uint32_t Size)
{
    uint32_t pagenumber = 0x0;
    uint32_t size = Size;

    if ((size % PAGE_SIZE) != 0)
    {
        pagenumber = (size / PAGE_SIZE) + 1;
    }
    else
    {
        pagenumber = size / PAGE_SIZE;
    }
    return pagenumber;

}

/*******************************************************************************
  * @函数名称：FLASH_DisableWriteProtectionPages
  * @函数说明：接触Flash写保护
  * @输入参数：无
  * @输出参数：无
  * @返回参数：无
  * @历史记录:     
     <作者>    <时间>      <修改记录>
*******************************************************************************/
void FLASH_DisableWriteProtectionPages(void)
{
    uint32_t useroptionbyte = 0, WRPR = 0;
    uint16_t var1 = OB_IWDG_SW, var2 = OB_STOP_NoRST, var3 = OB_STDBY_NoRST;
    FLASH_Status status = FLASH_BUSY;

    WRPR = FLASH_GetWriteProtectionOptionByte();

    //测试是否写保护
    if ((WRPR & UserMemoryMask) != UserMemoryMask)
    {
        useroptionbyte = FLASH_GetUserOptionByte();

        UserMemoryMask |= WRPR;

        status = FLASH_EraseOptionBytes();

        if (UserMemoryMask != 0xFFFFFFFF)
        {
            status = FLASH_EnableWriteProtection((uint32_t)~UserMemoryMask);
        }
        //用处选项字是否有编程
        if ((useroptionbyte & 0x07) != 0x07)
        {
            //重新保存选项字
            if ((useroptionbyte & 0x01) == 0x0)
            {
                var1 = OB_IWDG_HW;
            }
            if ((useroptionbyte & 0x02) == 0x0)
            {
                var2 = OB_STOP_RST;
            }
            if ((useroptionbyte & 0x04) == 0x0)
            {
                var3 = OB_STDBY_RST;
            }

            FLASH_UserOptionByteConfig(var1, var2, var3);
        }

        if (status == FLASH_COMPLETE)
        {
            SerialPutString("Write Protection disabled...\r\n");

            SerialPutString("...and a System Reset will be generated to re-load the new option bytes\r\n");
            //系统复位重新加载选项字
            NVIC_SystemReset();
        }
        else
        {
            SerialPutString("Error: Flash write unprotection failed...\r\n");
        }
    }
    else
    {
        SerialPutString("Flash memory not write protected\r\n");
    }
}

/*******************************************************************************
  * @函数名称：Main_Menu
  * @函数说明：显示菜单栏在超级终端
  * @输入参数：无
  * @输出参数：无
  * @返回参数：无
  * @历史记录:     
     <作者>    <时间>      <修改记录>
*******************************************************************************/
void Main_Menu(void)
{
    uint8_t key = 0;
    static uint8_t uStatus = 0;
    BlockNbr = (FlashDestination - 0x08000000) >> 12;

 
#if defined (STM32F10X_MD) || defined (STM32F10X_MD_VL)
    UserMemoryMask = ((uint32_t)~((1 << BlockNbr) - 1));
#else /* USE_STM3210E_EVAL */
    if (BlockNbr < 62)
    {
        UserMemoryMask = ((uint32_t)~((1 << BlockNbr) - 1));
    }
    else
    {
        UserMemoryMask = ((uint32_t)0x80000000);
    }
#endif /* (STM32F10X_MD) || (STM32F10X_MD_VL) */

    if ((FLASH_GetWriteProtectionOptionByte() & UserMemoryMask) != UserMemoryMask)
    {
        FlashProtection = 1;
    }
    else
    {
        FlashProtection = 0;
    }

    while (IS_TIMEOUT_1MS(eTim2, 300))
    {
       switch(uStatus)
        {
            case 0:
						GPIO_SetBits(GPIOC , GPIO_Pin_6);
            SerialPutString("\r*********************************************************\r\n");
          //  SerialPutString( "1.更新应用区程序；\r\n");  
           // SerialPutString( "2.运行APP程序。\r\n");
            SerialPutString( "*********************************************************\r\n");
						 SerialPutString( "aaaaa\r\n");
           // SerialPutString( "请选择:\r\n");
						delay(200);
						GPIO_ResetBits(GPIOC , GPIO_Pin_6);
            uStatus = 1;
            break;
            case 1:
							GPIO_SetBits(GPIOC , GPIO_Pin_6);
						//SerialPutString( "bbb\r\n");//
						delay(200);
						GPIO_ResetBits(GPIOC , GPIO_Pin_6);
						key = GetKey();
            if (key == 0x31)
            {	
							IWDG_Config(IWDG_Prescaler_64,3125);  //1s 	
							GPIO_SetBits(GPIOC , GPIO_Pin_6);
						SerialPutString( "ccc\r\n");//
							delay(200);
						GPIO_ResetBits(GPIOC , GPIO_Pin_6);
                /* Download user application in the Flash */
                SerialDownload();
							GPIO_SetBits(GPIOC , GPIO_Pin_6);
							  SerialPutString( "\rok\n\r");//
							delay(200);
							GPIO_ResetBits(GPIOC , GPIO_Pin_6);              
							
            }
            else if (key == 0x32)
            {
							GPIO_SetBits(GPIOC , GPIO_Pin_6);
							SerialPutString( "ddd\r\n");//
              SerialPutString("working...\r\n");        
							delay(200);
							GPIO_ResetBits(GPIOC , GPIO_Pin_6);
							
                BspTim2Close();
                JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);

                /* Jump to user application */
                Jump_To_Application = (pFunction) JumpAddress;
                /* Initialize user application's Stack Pointer */
                __set_MSP(*(__IO uint32_t*) ApplicationAddress);
                Jump_To_Application();
            }   
						GPIO_SetBits(GPIOC , GPIO_Pin_6);
						SerialPutString( "\rworkok\n\r");//
						delay(200);
						GPIO_ResetBits(GPIOC , GPIO_Pin_6);
					

            default:
            break;
        }  
//        else
//        {
//            if (FlashProtection == 0)
//            {
//                SerialPutString("Invalid Number ! ==> The number should be either 1, 2 or 3\r");
//            }
//            else
//            {
//                SerialPutString("Invalid Number ! ==> The number should be either 1, 2, 3 or 4\r");
//            }
//        }
    }
}


/*******************************文件结束***************************************/
