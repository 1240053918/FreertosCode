#include "include.h"


/*
*********************************************************************************************************
*
*	?��?��??3? : ?������?�¨���?��
*	???t??3? : SysInfoTest.c
*	��?    ��? : V1.0
*	?��    ?�� : ?a��???��?FreeRTOS��?��???D??���?D����a���?����????������?�¡�??a???������?�¦�?����???����????����a??����
*              ?�̨�3����?��?��???��?a?����?��?��?��???D??��2?��?����?��
*              ��????t����1?��?o����y??��?����2a��???��?��??D2??��????��?��������?��????��??-������D��?��?��o
*               1. FreeRTOS��??�̨�3?��o???��D??������???��y����??��?��?3?����?��?��
*               2. ?������?��?D??��?50us??��?��?��?��?����??����?��?�̨�3D??��?��
*              --------------------------------------------------------------------------------------
*              ��????t��1��?��?��?32??��?��?��������?50us��?��?��???��y?�̡�?��?�䨮?��3???��y����??��o
*              2^32 * 50us / 3600s = 59.6��??��?�꨺1��??D2a��?��?��?????DD??��yo����?????��??��3?1y��?59.6��??��??2?��?����?��
*
*	DT?????? :
*		��?��?o?    ��??��        ����??     ?��?��
*		V1.0    2015-08-19  Eric2013   ��������
*
*	Copyright (C), 2015-2020, ��2??��3��?���� www.armfly.com
*
*********************************************************************************************************
*/
#include "bsp.h"


/*��ʱ��Ƶ�� 50us�ж�һ��*/
#define  timerINTERRUPT_FREQUENCY	20000

/*�ж����ȼ�*/
#define  timerHIGHEST_PRIORITY		1

/*��freertosϵͳ���õĲ���*/
volatile uint32_t ulHighFrequencyTimerTicks = 0UL;

/*
*********************************************************************************************************
*�������ƣ� bsp_GetRCCofTIM
*����˵���� ���TIMx�õ���ӦRCC�Ĵ���
*��    �Σ� TIMx��ʱ����
*����ֵ  �� TIMx����ʱ����
*********************************************************************************************************
*/
uint32_t bsp_GetRCCofTIM(TIM_TypeDef* TIMx)
{
	uint32_t rcc = 0;

	/*
		APB1 ���� TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7, TIM12, TIM13, TIM14
		APB2 ���� TIM1, TIM8 ,TIM9, TIM10, TIM11
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
	/* ����Ϊ APB1ʱ��*/
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
*�������ƣ� bsp_SetTIMforInt
*����˵���� ��ʱ����ʼ�����ö�ʱ�����ڲ���ulHighFrequencyTimerTicks����
*��    �Σ� TIMx��ʱ����
						_ulFreq��ʱ��Ƶ��
						_PreemptionPriority�ж����ȼ�����
						_SubPriority�����ȼ�
*����ֵ  �� ��
*********************************************************************************************************
*/
void bsp_SetTIMforInt(TIM_TypeDef* TIMx, uint32_t _ulFreq, uint8_t _PreemptionPriority, uint8_t _SubPriority)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	uint16_t usPeriod;
	uint16_t usPrescaler;
	uint32_t uiTIMxCLK;

  	/* ʹ�ܶ�ʱ��ʱ�� */
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
		TIM_Cmd(TIMx, DISABLE);		/* �رն�ʱ�� */

		/* �رն�ʱ�������ж� (Update) */
		{
			NVIC_InitTypeDef NVIC_InitStructure;	
			uint8_t irq = 0;	/* �жϺ� ������stm32f4xx.h */

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

		APB1 ?������?�¨�D TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7, TIM12, TIM13,TIM14
		APB2 ?������?�¨�D TIM1, TIM8 ,TIM9, TIM10, TIM11

	----------------------------------------------------------------------- */
	if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM9) || (TIMx == TIM10) || (TIMx == TIM11))
	{
		/* APB2��ʱ��*/
		uiTIMxCLK = SystemCoreClock;
	}
	else	/* APB1��ʱ��*/
	{
		uiTIMxCLK = SystemCoreClock;	// SystemCoreClock / 2;
	}

	if (_ulFreq < 100)
	{
		usPrescaler = 10000 - 1;					/* ��Ƶ�� = 1000 */
		usPeriod =  (uiTIMxCLK / 10000) / _ulFreq  - 1;		/* �Զ���װֵ*/
	}
	else if (_ulFreq < 3000)
	{
		usPrescaler = 100 - 1;					/* ��Ƶ�� = 100 */
		usPeriod =  (uiTIMxCLK / 100) / _ulFreq  - 1;		/* �Զ���װֵ */
	}
	else	/* ����4kƵ�������Ƶ */
	{
		usPrescaler = 0;					/* ��Ƶ�� = 1 */
		usPeriod = uiTIMxCLK / _ulFreq - 1;	/* �Զ���װֵ */
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

	/* ���ö�ʱ�������ж�(Update) */
	{
		NVIC_InitTypeDef NVIC_InitStructure;	/* ?D???��11��??�� misc.h ?D?����? */
		uint8_t irq = 0;	/* ?D??o?, ?����??�� stm32f4xx.h */

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
*�������ƣ� vSetupSysInfoTest
*����˵���� ͬbsp_SetTIMforInt()��������һ��
*��    �Σ� ��
*����ֵ  �� ��
*********************************************************************************************************
*/
void vSetupSysInfoTest(void)
{
	bsp_SetTIMforInt(TIM6, timerINTERRUPT_FREQUENCY, timerHIGHEST_PRIORITY, 0);
}

/*
*********************************************************************************************************
*�������ƣ� TIM6_IRQHandler
*����˵���� ��ʱ���жϺ���������ulHighFrequencyTimerTicks����
*��    �Σ� ��
*����ֵ  �� ��
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






