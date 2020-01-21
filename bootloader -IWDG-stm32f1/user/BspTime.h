#ifndef _DrvTime2_h_
#define _DrvTime2_h_

#include "stm32f10x.h"


#ifndef NULL
#define NULL        ((void *)0)
#endif





enum {
    eTim1,
    eTim2,
    eTimUpdata,
    eTimYModem,
    eTimMax,
};



//��?1?index??��|��?����??3?������???��?2�顤��??1��??��3?��������??0
#define IS_TIMEOUT_1MS(index, count)    ((g_Tim2Array[(uint16_t)(index)] <= (count))?  \
                                        1: 0)


extern volatile int g_Tim2Array[(uint16_t)eTimMax];

void BspTim2Init(void);
void BspTim2Close(void);




#endif
/*********************************** END **************************************/


