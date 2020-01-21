#include "timer.h"
#include "magnet.h"
#include "u485.h"
#include "main.h"


void TIM3_Int_Init(uint16_t arr,uint16_t psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;  //先占优先级0级

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}


void TIM3_IRQHandler(void)   //TIM3中断
{
	static uint8_t i;
	static uint8_t j;
	static uint16_t t;
	static uint8_t count1,count2,count3,count4,count5,count6,count7,count8,count9,count10;
	static uint8_t count11,count12,count13,count14,count15,count16,count17,count18,count19,count20;
	static uint8_t count21,count22,count23,count24,count25,count26,count27,count28,count29,count30;
	static uint8_t count31,count32,count33,count34,count35,count36,count37,count38,count39,count40;
	static uint16_t u485_time;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
		
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		i++;
		
		if(U485_FLAG==1)
		{
			u485_time++;
			if(u485_time==3000)
			{
				u485_time=0;
				U485_FLAG=0;
				USART_Cmd(USART1, ENABLE);    
			}
		}
		
		if(OUTLOCK_TIME_FLAG==1)
		{
			t=0;
		}
		if(OUTLOCK_FLAG==1)
		{ 
			OUTLOCK_TIME_FLAG=0;
			t++;
			if(t<100)
			{
				M37open;
			}
			else if(j<=8)
			{
				j++;
				M37open;
			}
		 else if(j>8)
			{
				j++;
				if(j>10)
				{
					j=0;
				}
				M37close;
			}
			if(t>16000)
			{
				OUTLOCK_FLAG=0;
				t=0;
				j=0;
				M37close;
			}
		}
		if(i==200)
		{
			i=0;
			GPIOF->ODR ^= GPIO_Pin_7;
		}
		
		if(magnet_timer_flag[0]==1)
		{
				count1++;
				if(count1==SUCTION_T[0])
				{
					magnet_timer_flag[0]=0;
					count1=0;
					M1close;
				}
		}
		
		if(magnet_timer_flag[1]==1)
		{
				count2++;
				if(count2==SUCTION_T[1])
				{
					magnet_timer_flag[1]=0;
					count2=0;
					M2close;
				}
		}
		
		if(magnet_timer_flag[2]==1)
		{
				count3++;
				if(count3==SUCTION_T[2])
				{
					magnet_timer_flag[2]=0;
					count3=0;
					M3close;
				}
		}
		
		if(magnet_timer_flag[3]==1)
		{
				count4++;
				if(count4==SUCTION_T[3])
				{
					magnet_timer_flag[3]=0;
					count4=0;
					M4close;
				}
		}
		
		if(magnet_timer_flag[4]==1)
		{
				count5++;
				if(count5==SUCTION_T[4])
				{
					magnet_timer_flag[4]=0;
					count5=0;
					M5close;
				}
		}
		
		if(magnet_timer_flag[5]==1)
		{
				count6++;
				if(count6==SUCTION_T[5])
				{
					
					magnet_timer_flag[5]=0;
					count6=0;
					M6close;
				}
		}
		
		if(magnet_timer_flag[6]==1)
		{
				count7++;
				if(count7==SUCTION_T[6])
				{
					
					magnet_timer_flag[6]=0;
					count7=0;
					M7close;
				}
		}
		
		if(magnet_timer_flag[7]==1)
		{
				count8++;
				if(count8==SUCTION_T[7])
				{
					
					magnet_timer_flag[7]=0;
					count8=0;
					M8close;
				}
		}
		
		if(magnet_timer_flag[8]==1)
		{
				count9++;
				if(count9==SUCTION_T[8])
				{
					
					magnet_timer_flag[8]=0;
					count9=0;
					M9close;
				}
		}
		if(magnet_timer_flag[9]==1)
		{
				count10++;
				if(count10==SUCTION_T[9])
				{
					
					magnet_timer_flag[9]=0;
					count10=0;
					M10close;
				}
		}
		
		
		if(magnet_timer_flag[10]==1)
		{
				count11++;
				if(count11==SUCTION_T[10])
				{
					magnet_timer_flag[10]=0;
					count11=0;
					M11close;
				}
		}
		
		if(magnet_timer_flag[11]==1)
		{
				count12++;
				if(count12==SUCTION_T[11])
				{
					magnet_timer_flag[11]=0;
					count12=0;
					M12close;
				}
		}
		
		if(magnet_timer_flag[12]==1)
		{
				count13++;
				if(count13==SUCTION_T[12])
				{
					magnet_timer_flag[12]=0;
					count13=0;
					M13close;
				}
		}
		
		if(magnet_timer_flag[13]==1)
		{
				count14++;
				if(count14==SUCTION_T[13])
				{
					magnet_timer_flag[13]=0;
					count14=0;
					M14close;
				}
		}
		
		if(magnet_timer_flag[14]==1)
		{
				count15++;
				if(count15==SUCTION_T[14])
				{
					magnet_timer_flag[14]=0;
					count15=0;
					M15close;
				}
		}
		
		if(magnet_timer_flag[15]==1)
		{
				count16++;
				if(count16==SUCTION_T[15])
				{
					
					magnet_timer_flag[15]=0;
					count16=0;
					M16close;
				}
		}
		
		if(magnet_timer_flag[16]==1)
		{
				count17++;
				if(count17==SUCTION_T[16])
				{
					
					magnet_timer_flag[16]=0;
					count17=0;
					M17close;
				}
		}
		
		if(magnet_timer_flag[17]==1)
		{
				count18++;
				if(count18==SUCTION_T[17])
				{
					
					magnet_timer_flag[17]=0;
					count18=0;
					M18close;
				}
		}
		
		if(magnet_timer_flag[18]==1)
		{
				count19++;
				if(count19==SUCTION_T[18])
				{
					
					magnet_timer_flag[18]=0;
					count19=0;
					M19close;
				}
		}
		if(magnet_timer_flag[19]==1)
		{
				count20++;
				if(count20==SUCTION_T[19])
				{
					
					magnet_timer_flag[19]=0;
					count20=0;
					M20close;
				}
		}
		
		
		
		if(magnet_timer_flag[20]==1)
		{
				count21++;
				if(count21==SUCTION_T[20])
				{
					magnet_timer_flag[20]=0;
					count21=0;
					M21close;
				}
		}
		
		if(magnet_timer_flag[21]==1)
		{
				count22++;
				if(count22==SUCTION_T[21])
				{
					magnet_timer_flag[21]=0;
					count22=0;
					M22close;
				}
		}
		
		if(magnet_timer_flag[22]==1)
		{
				count23++;
				if(count23==SUCTION_T[22])
				{
					magnet_timer_flag[22]=0;
					count23=0;
					M23close;
				}
		}
		
		if(magnet_timer_flag[23]==1)
		{
				count24++;
				if(count24==SUCTION_T[23])
				{
					magnet_timer_flag[23]=0;
					count24=0;
					M24close;
				}
		}
		
		if(magnet_timer_flag[24]==1)
		{
				count25++;
				if(count25==SUCTION_T[24])
				{
					magnet_timer_flag[24]=0;
					count25=0;
					M25close;
				}
		}
		
		if(magnet_timer_flag[25]==1)
		{
				count26++;
				if(count26==SUCTION_T[25])
				{
					
					magnet_timer_flag[25]=0;
					count26=0;
					M26close;
				}
		}
		
		if(magnet_timer_flag[26]==1)
		{
				count27++;
				if(count27==SUCTION_T[26])
				{
					
					magnet_timer_flag[26]=0;
					count27=0;
					M27close;
				}
		}
		
		if(magnet_timer_flag[27]==1)
		{
				count28++;
				if(count28==SUCTION_T[27])
				{
					
					magnet_timer_flag[27]=0;
					count28=0;
					M28close;
				}
		}
		
		if(magnet_timer_flag[28]==1)
		{
				count29++;
				if(count29==SUCTION_T[28])
				{
					
					magnet_timer_flag[28]=0;
					count29=0;
					M29close;
				}
		}
		if(magnet_timer_flag[29]==1)
		{
				count30++;
				if(count30==SUCTION_T[29])
				{
					
					magnet_timer_flag[29]=0;
					count30=0;
					M30close;
				}
		}
		
		
		
		if(magnet_timer_flag[30]==1)
		{
				count31++;
				if(count31==SUCTION_T[30])
				{
					magnet_timer_flag[30]=0;
					count31=0;
					M31close;
				}
		}
		
		if(magnet_timer_flag[31]==1)
		{
				count32++;
				if(count32==SUCTION_T[31])
				{
					magnet_timer_flag[31]=0;
					count32=0;
					M32close;
				}
		}
		
		if(magnet_timer_flag[32]==1)
		{
				count33++;
				if(count33==SUCTION_T[32])
				{
					magnet_timer_flag[32]=0;
					count33=0;
					M33close;
				}
		}
		
		if(magnet_timer_flag[33]==1)
		{
				count34++;
				if(count34==SUCTION_T[33])
				{
					magnet_timer_flag[33]=0;
					count34=0;
					M34close;
				}
		}
		
		if(magnet_timer_flag[34]==1)
		{
				count35++;
				if(count35==SUCTION_T[34])
				{
					magnet_timer_flag[34]=0;
					count35=0;
					M35close;
				}
		}
		
		if(magnet_timer_flag[35]==1)
		{
				count36++;
				if(count36==SUCTION_T[35])
				{
					
					magnet_timer_flag[35]=0;
					count36=0;
					M36close;
				}
		}
		
		if(magnet_timer_flag[36]==1)
		{
				count37++;
				if(count37==SUCTION_T[36])
				{
					
					magnet_timer_flag[36]=0;
					count37=0;
					M37close;
				}
		}
		
		if(magnet_timer_flag[37]==1)
		{
				count38++;
				if(count38==SUCTION_T[37])
				{
					
					magnet_timer_flag[37]=0;
					count38=0;
					M38close;
				}
		}
		
		if(magnet_timer_flag[38]==1)
		{
				count39++;
				if(count39==SUCTION_T[38])
				{
					
					magnet_timer_flag[38]=0;
					count39=0;
					M39close;
				}
		}
		if(magnet_timer_flag[39]==1)
		{
				count40++;
				if(count40==SUCTION_T[39])
				{
					
					magnet_timer_flag[39]=0;
					count40=0;
					M40close;
				}
		}
	
		
	
		
	
	}
}
