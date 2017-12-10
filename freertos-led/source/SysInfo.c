#include "include.h"


/*
*********************************************************************************************************
*
*	?￡?é??3? : ?¨ê±?÷ê±?ù
*	???t??3? : SysInfoTest.c
*	°?    ±? : V1.0
*	?μ    ?÷ : ?aá???è?FreeRTOSμ?è???D??￠￡?Dèòa′′?¨ò????¨ê±?÷￡??a???¨ê±?÷μ?ê±???ù×????èòa??óú
*              ?μí3ê±?ó?ú???￡?a?ùμ?μ?μ?è???D??￠2?×?è·?￡
*              ±????tìá1?μ?oˉêy??ó?óú2aê???μ?￡??D2??é????ó?óúêμ?ê????￡??-òòóDá?μ?￡o
*               1. FreeRTOSμ??μí3?úo???óD??×üμ???êyê±??×?ò?3?±￡?¤?￡
*               2. ?¨ê±?÷?D??ê?50us??è?ò?′?￡?±è??ó°?ì?μí3D??ü?￡
*              --------------------------------------------------------------------------------------
*              ±????tê1ó?μ?ê?32??±?á?à′±￡′?50usò?′?μ???êy?μ￡?×?′ó?§3???êyê±??￡o
*              2^32 * 50us / 3600s = 59.6·??ó?￡ê1ó??D2aê?μ?è?????DD??êyoíè?????ó??ê3?1yá?59.6·??ó??2?×?è·?￡
*
*	DT?????? :
*		°?±?o?    è??ú        ×÷??     ?μ?÷
*		V1.0    2015-08-19  Eric2013   ê×·￠
*
*	Copyright (C), 2015-2020, °2??à3μ?×ó www.armfly.com
*
*********************************************************************************************************
*/
#include "bsp.h"


/*定时器频率 50us中断一次*/
#define  timerINTERRUPT_FREQUENCY	20000

/*中断优先级*/
#define  timerHIGHEST_PRIORITY		1

/*被freertos系统调用的参数*/
volatile uint32_t ulHighFrequencyTimerTicks = 0UL;

/*
*********************************************************************************************************
*函数名称： bsp_GetRCCofTIM
*功能说明： 获得TIMx得到对应RCC寄存器
*形    参： TIMx定时器号
*返回值  ： TIMx外设时钟名
*********************************************************************************************************
*/
uint32_t bsp_GetRCCofTIM(TIM_TypeDef* TIMx)
{
	uint32_t rcc = 0;

	/*
		APB1 包括 TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7, TIM12, TIM13, TIM14
		APB2 包括 TIM1, TIM8 ,TIM9, TIM10, TIM11
	*/
	if (TIMx == TIM1)
	{
		rcc = RCC_APB2Periph_TIM1;
	}
	else if (TIMx == TIM8)
	{
		rcc = RCC_APB2Periph_TIM8;
	}
	else if (TIMx == TIM9)
	{
		rcc = RCC_APB2Periph_TIM9;
	}
	else if (TIMx == TIM10)
	{
		rcc = RCC_APB2Periph_TIM10;
	}
	else if (TIMx == TIM11)
	{
		rcc = RCC_APB2Periph_TIM11;
	}
	/* 下面为 APB1时钟*/
	else if (TIMx == TIM2)
	{
		rcc = RCC_APB1Periph_TIM2;
	}
	else if (TIMx == TIM3)
	{
		rcc = RCC_APB1Periph_TIM3;
	}
	else if (TIMx == TIM4)
	{
		rcc = RCC_APB1Periph_TIM4;
	}
	else if (TIMx == TIM5)
	{
		rcc = RCC_APB1Periph_TIM5;
	}
	else if (TIMx == TIM6)
	{
		rcc = RCC_APB1Periph_TIM6;
	}
	else if (TIMx == TIM7)
	{
		rcc = RCC_APB1Periph_TIM7;
	}
	else if (TIMx == TIM12)
	{
		rcc = RCC_APB1Periph_TIM12;
	}
	else if (TIMx == TIM13)
	{
		rcc = RCC_APB1Periph_TIM13;
	}
	else if (TIMx == TIM14)
	{
		rcc = RCC_APB1Periph_TIM14;
	}

	return rcc;
}
/*
*********************************************************************************************************
*函数名称： bsp_SetTIMforInt
*功能说明： 定时器初始化，该定时器用于产生ulHighFrequencyTimerTicks计数
*形    参： TIMx定时器号
						_ulFreq定时器频率
						_PreemptionPriority中断优先级分组
						_SubPriority子优先级
*返回值  ： 无
*********************************************************************************************************
*/
void bsp_SetTIMforInt(TIM_TypeDef* TIMx, uint32_t _ulFreq, uint8_t _PreemptionPriority, uint8_t _SubPriority)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	uint16_t usPeriod;
	uint16_t usPrescaler;
	uint32_t uiTIMxCLK;

  	/* 使能定时器时钟 */
	if ((TIMx == TIM1) || (TIMx == TIM8))
	{
		RCC_APB2PeriphClockCmd(bsp_GetRCCofTIM(TIMx), ENABLE);
	}
	else
	{
		RCC_APB1PeriphClockCmd(bsp_GetRCCofTIM(TIMx), ENABLE);
	}

	if (_ulFreq == 0)
	{
		TIM_Cmd(TIMx, DISABLE);		/* 关闭定时器 */

		/* 关闭定时器更新中断 (Update) */
		{
			NVIC_InitTypeDef NVIC_InitStructure;	
			uint8_t irq = 0;	/* 中断号 定义在stm32f4xx.h */

			if (TIMx == TIM1)
				irq = TIM1_UP_IRQn;
			else if (TIMx == TIM2)
				irq = TIM2_IRQn;
			else if (TIMx == TIM3)
				irq = TIM3_IRQn;
			else if (TIMx == TIM4)
				irq = TIM4_IRQn;
			else if (TIMx == TIM5)
				irq = TIM5_IRQn;
			else if (TIMx == TIM6)
				irq = TIM6_IRQn;
			else if (TIMx == TIM7)
				irq = TIM7_IRQn;
			else if (TIMx == TIM8)
				irq = TIM8_UP_IRQn;

			NVIC_InitStructure.NVIC_IRQChannel = irq;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = _PreemptionPriority;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = _SubPriority;
			NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
			NVIC_Init(&NVIC_InitStructure);
		}		
		return;
	}

    /*-----------------------------------------------------------------------
		system_stm32f4xx.c ???t?D static void SetSysClockToHSE(void) 

			//HCLK = SYSCLK 
			RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
			  
			//PCLK2 = HCLK
			RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
			
			//PCLK1 = HCLK
			RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;

		APB1 ?¨ê±?÷óD TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7, TIM12, TIM13,TIM14
		APB2 ?¨ê±?÷óD TIM1, TIM8 ,TIM9, TIM10, TIM11

	----------------------------------------------------------------------- */
	if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM9) || (TIMx == TIM10) || (TIMx == TIM11))
	{
		/* APB2定时器*/
		uiTIMxCLK = SystemCoreClock;
	}
	else	/* APB1定时器*/
	{
		uiTIMxCLK = SystemCoreClock;	// SystemCoreClock / 2;
	}

	if (_ulFreq < 100)
	{
		usPrescaler = 10000 - 1;					/* 分频比 = 1000 */
		usPeriod =  (uiTIMxCLK / 10000) / _ulFreq  - 1;		/* 自动重装值*/
	}
	else if (_ulFreq < 3000)
	{
		usPrescaler = 100 - 1;					/* 分频比 = 100 */
		usPeriod =  (uiTIMxCLK / 100) / _ulFreq  - 1;		/* 自动重装值 */
	}
	else	/* 大于4k频率无需分频 */
	{
		usPrescaler = 0;					/* 分频比 = 1 */
		usPeriod = uiTIMxCLK / _ulFreq - 1;	/* 自动重装值 */
	}

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = usPeriod;
	TIM_TimeBaseStructure.TIM_Prescaler = usPrescaler;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

	TIM_ARRPreloadConfig(TIMx, ENABLE);

	/* TIM Interrupts enable */
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);

	/* TIMx enable counter */
	TIM_Cmd(TIMx, ENABLE);

	/* 配置定时器更新中断(Update) */
	{
		NVIC_InitTypeDef NVIC_InitStructure;	/* ?D???á11ì??ú misc.h ?D?¨ò? */
		uint8_t irq = 0;	/* ?D??o?, ?¨ò??ú stm32f4xx.h */

		if (TIMx == TIM1)
			irq = TIM1_UP_IRQn;
		else if (TIMx == TIM2)
			irq = TIM2_IRQn;
		else if (TIMx == TIM3)
			irq = TIM3_IRQn;
		else if (TIMx == TIM4)
			irq = TIM4_IRQn;
		else if (TIMx == TIM5)
			irq = TIM5_IRQn;
		else if (TIMx == TIM6)
			irq = TIM6_IRQn;
		else if (TIMx == TIM7)
			irq = TIM7_IRQn;
		else if (TIMx == TIM8)
			irq = TIM8_UP_IRQn;

		NVIC_InitStructure.NVIC_IRQChannel = irq;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = _PreemptionPriority;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = _SubPriority;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
}
/*
*********************************************************************************************************
*函数名称： vSetupSysInfoTest
*功能说明： 同bsp_SetTIMforInt()函数功能一样
*形    参： 无
*返回值  ： 无
*********************************************************************************************************
*/
void vSetupSysInfoTest(void)
{
	bsp_SetTIMforInt(TIM6, timerINTERRUPT_FREQUENCY, timerHIGHEST_PRIORITY, 0);
}

/*
*********************************************************************************************************
*函数名称： TIM6_IRQHandler
*功能说明： 定时器中断函数，用于ulHighFrequencyTimerTicks计数
*形    参： 无
*返回值  ： 无
*********************************************************************************************************
*/
void TIM6_IRQHandler( void )
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
	{
		ulHighFrequencyTimerTicks++;
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
	}
}






