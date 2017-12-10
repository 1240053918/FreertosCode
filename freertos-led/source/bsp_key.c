#include "bsp.h"
#include "include.h"

void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5|GPIO_Pin_2|GPIO_Pin_3;//K1-K3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4


}

void EXTIX_Init(void)
{
 
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	KEY_Init();	 //	�����˿ڳ�ʼ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

	//GPIOC.5 �ж����Լ��жϳ�ʼ������   �½��ش���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

	EXTI_InitStructure.EXTI_Line=EXTI_Line5;	//K1
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	//GPIOC.2	  �ж����Լ��жϳ�ʼ������ �½��ش��� //K2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	//GPIOC.3	  �ж����Լ��жϳ�ʼ������  �½��ش���	//K3
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3);
	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�2�� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); 

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);


	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�2 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���


}
void EXTI9_5_IRQHandler(void)
{
		GPIO_ResetBits(GPIOB, GPIO_Pin_5); 
	EXTI_ClearITPendingBit(EXTI_Line5);  //���LINE2�ϵ��жϱ�־λ  
}

//�ⲿ�ж�2�������
//void EXTI2_IRQHandler(void)
//{
////	delay_ms(5);//����
//	if(KEY2==0)	  //����KEY2
//	{
//			vTaskDelete(xHandleTaskUART);
//	GPIO_SetBits(GPIOB, GPIO_Pin_5);

//	}		 
//	EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE2�ϵ��жϱ�־λ  
//}
//extern  TaskHandle_t xHandleTaskUART;
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
//	delay_ms(5);//����
	if(KEY1==0)	 //����KEY1
	{				 
		GPIO_SetBits(GPIOB, GPIO_Pin_5); 
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}

