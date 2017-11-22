#include "bsp.h"




void LED_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD , ENABLE);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				     //LED1  V6	   //将V6,V7,V8 配置为通用推挽输出  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //口线翻转速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_3;		 //LED2, LED3	 V7 V8
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 			      //LCD背光控制
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD, GPIO_Pin_13);			              //LCD背光关闭	

}
