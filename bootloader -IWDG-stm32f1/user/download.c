/*******************************************************************************
** �ļ���: 		download.c
** �汾��  		1.0
** ��������: 	RealView MDK-ARM 5.20
** ����: 		liupeng
** ��������: 	2016-03-20
** ����:		�ȴ��û�ѡ�����ļ�����,���߷��������Լ�һЩ��ʾ��Ϣ��
                ������ʵ�ִ��͵���ymodem��cԴ�ļ���
** ����ļ�:	common.h
** �޸���־��	2016-03-20   �����ĵ�
*******************************************************************************/

/* ����ͷ�ļ� *****************************************************************/
#include "common.h"

/* �������� ------------------------------------------------------------------*/
extern uint8_t file_name[FILE_NAME_LENGTH];
uint8_t tab_1024[1024] =
{
    0
};

/*******************************************************************************
  * @�������ƣ�SerialDownload
  * @����˵����ͨ�����ڽ���һ���ļ�
  * @�����������
  * @�������: ��
  * @���ز���: ��
  * @��ʷ��¼:     
     <����>    <ʱ��>      <�޸ļ�¼>
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

/*******************************�ļ�����***************************************/
