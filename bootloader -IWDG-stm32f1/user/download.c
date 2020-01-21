/*******************************************************************************
** 文件名: 		download.c
** 版本：  		1.0
** 工作环境: 	RealView MDK-ARM 5.20
** 作者: 		liupeng
** 生成日期: 	2016-03-20
** 功能:		等待用户选择传送文件操作,或者放弃操作以及一些提示信息，
                但真正实现传送的是ymodem．c源文件。
** 相关文件:	common.h
** 修改日志：	2016-03-20   创建文档
*******************************************************************************/

/* 包含头文件 *****************************************************************/
#include "common.h"

/* 变量声明 ------------------------------------------------------------------*/
extern uint8_t file_name[FILE_NAME_LENGTH];
uint8_t tab_1024[1024] =
{
    0
};

/*******************************************************************************
  * @函数名称：SerialDownload
  * @函数说明：通过串口接收一个文件
  * @输入参数：无
  * @输出参数: 无
  * @返回参数: 无
  * @历史记录:     
     <作者>    <时间>      <修改记录>
*******************************************************************************/
void SerialDownload(void)
{
    uint8_t Number[10] = "          ";
    int32_t Size = 0;
		GPIO_SetBits(GPIOC , GPIO_Pin_6);
    SerialPutString("Waiting for the file to be sent ... (press 'a' to abort)\n\r");
		GPIO_ResetBits(GPIOC , GPIO_Pin_6);
    Size = Ymodem_Receive(&tab_1024[0]);
    if (Size > 0)
    {
				GPIO_SetBits(GPIOC , GPIO_Pin_6);
        SerialPutString("\n\n\r Programming Completed Successfully!\n\r--------------------------------\r\n Name: ");
        SerialPutString(file_name);
			delay(200);
				GPIO_ResetBits(GPIOC , GPIO_Pin_6);
        Int2Str(Number, Size);
				GPIO_SetBits(GPIOC , GPIO_Pin_6);
        SerialPutString("\n\r Size: ");
        SerialPutString(Number);
        SerialPutString(" Bytes\r\n");
        SerialPutString("-------------------\n");
			delay(200);
				GPIO_ResetBits(GPIOC , GPIO_Pin_6);
    }
    else if (Size == -1)
    {
				GPIO_SetBits(GPIOC , GPIO_Pin_6);
        SerialPutString("\n\n\rThe image size is higher than the allowed space memory!\n\r");
			delay(200);
			GPIO_ResetBits(GPIOC , GPIO_Pin_6);
    }
    else if (Size == -2)
    {
			GPIO_SetBits(GPIOC , GPIO_Pin_6);
        SerialPutString("\n\n\rVerification failed!\n\r");
			delay(200);
			GPIO_ResetBits(GPIOC , GPIO_Pin_6);
    }
    else if (Size == -3)
    {
				GPIO_SetBits(GPIOC , GPIO_Pin_6);
        SerialPutString("\r\n\nAborted by user.\n\r");
			delay(200);
			GPIO_ResetBits(GPIOC , GPIO_Pin_6);
    }
    else
    {	
			GPIO_SetBits(GPIOC , GPIO_Pin_6);
        SerialPutString("\n\rFailed to receive the file!\n\r");
			delay(200);
			GPIO_ResetBits(GPIOC , GPIO_Pin_6);
    }
}

/*******************************文件结束***************************************/
