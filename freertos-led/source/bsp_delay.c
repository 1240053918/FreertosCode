#include "bsp.h"


void delay_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //Ê±ÖÓÊ¹ÄÜ



//	TIM3->CR1 = 0X00;
//	TIM3->CNT = 0x00;
//	TIM3->CR2 = 0X00;
}



void delay_us(uint16_t xus)
{
	TIM3->ARR = xus;
	TIM3->PSC = 0x47;
	TIM3->CR1 = 0X01;
	while((TIM3->CNT) != xus);
	
	TIM3->CR1 = 0X00;
//	TIM3->CNT = 0x00;
}


void delay_ms(uint16_t xms)
{
	
	TIM3->PSC = 0x8c9f;
	TIM3->ARR = xms*2;
	TIM3->CR1 = 0X0001;
	while((TIM3->CNT) != xms);//((TIM3->SR)&0x01) == 0
	
	TIM3->CR1 = 0X00;
//	TIM3->CNT = 0x00;
}
