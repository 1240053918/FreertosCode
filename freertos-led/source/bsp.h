#ifndef __BSP_H
#define __BSP_H
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART




void LED_Config(void);
void USART_Config(USART_TypeDef* USARTx);
void bsp_init(void);

#endif
