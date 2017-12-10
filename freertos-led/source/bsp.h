#ifndef __BSP_H
#define __BSP_H
//********************************************头文件*****************************************************************************************
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "stm32f10x_spi.h"              // Keil::Device:StdPeriph Drivers:SPI
#include "stm32f10x_dma.h"              // Keil::Device:StdPeriph Drivers:DMA
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI

#include "sdio_sdcard.h"
#include "malloc.h"	   
void LED_Config(void);


void bsp_init(void);

#define KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键0
#define KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)//读取按键1
#define KEY3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)//读取按键2 

void KEY_Init(void);
void EXTIX_Init(void);
//********************************************UART*****************************************************************************************
//printf只支持USART2,想要支持USART1,需要修改fputc函数

//UART引脚设置,默认使用GPIOA,使用GPIOB-GPIOD,需要修改
#define  UART1_TX_PORT    				GPIOA
#define  UART1_TX_PIN     				GPIO_Pin_9

#define  UART1_RX_PORT    				GPIOA
#define  UART1_RX_PIN     				GPIO_Pin_10

#define  UART2_TX_PORT    				GPIOA
#define  UART2_TX_PIN     				GPIO_Pin_2

#define  UART2_RX_PORT    				GPIOA
#define  UART2_RX_PIN     				GPIO_Pin_3
//USART函数声明
void USART_Config(USART_TypeDef* USARTx);
//********************************************SPI*****************************************************************************************

/* Select SPI FLASH: ChipSelect pin low  */
#define SPI1_CS_L()     GPIO_ResetBits(GPIOC, GPIO_Pin_4)
/* Deselect SPI FLASH: ChipSelect pin high */
#define SPI1_CS_H()    GPIO_SetBits(GPIOC, GPIO_Pin_4)

//SPI函数声明
void SPI1_Init(void);
uint8_t SPI1_SendByte(uint8_t byte);
uint8_t SPI1_ReadByte(void);
//********************************************IIC*****************************************************************************************
/******************STM32的硬件IIC接口是有问题的，所以这里使用的是GPIO模拟的IIC接口*********************************************************/
//IIC引脚设置
#define  RCC_APB2Periph_SCL  RCC_APB2Periph_GPIOB
#define  RCC_APB2Periph_SDA  RCC_APB2Periph_GPIOB

#define  IIC_SCL_PORT    				GPIOB
#define  IIC_SCL_PIN     				GPIO_Pin_6

#define  IIC_SDA_PORT    				GPIOB
#define  IIC_SDA_PIN     				GPIO_Pin_7

//IO方向设置，SDA引脚每换一次，此设置都要重新修改
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

//IO操作函数	 
#define IIC_SCL_H   	GPIO_SetBits(IIC_SCL_PORT, IIC_SCL_PIN)  //SCL置高
#define IIC_SCL_L     GPIO_ResetBits(IIC_SCL_PORT, IIC_SCL_PIN)//SCL置低

#define IIC_SDA_H     GPIO_SetBits(IIC_SDA_PORT, IIC_SDA_PIN)  //SDA置高	 
#define IIC_SDA_L     GPIO_ResetBits(IIC_SDA_PORT, IIC_SDA_PIN)//SDA置低	 

#define READ_SDA      GPIO_ReadInputDataBit(IIC_SDA_PORT, IIC_SDA_PIN)  //输入SDA 

//IIC函数声明
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
//********************************************DMA设置*****************************************************************************************
void DMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);
void DMA_Enable(DMA_Channel_TypeDef*DMA_CHx);
//********************************************延时函数*****************************************************************************************
void delay_init(void);
void delay_us(uint16_t xus);
void delay_ms(uint16_t xms);
//********************************************延时函数*****************************************************************************************
void Adc_Config(void);
uint16_t T_Get_Adc(uint8_t ch); 
uint16_t T_Get_Temp(void);
uint16_t T_Get_Adc_Average(uint8_t ch,uint8_t times);
short Get_Temprate(void);
#endif
