#include "include.h"

//*****************任务句柄定义*****************//
static TaskHandle_t xHandleTaskLED;
static TaskHandle_t xHandleTaskUART;


//*****************任务函数定义*****************//
static void vTaskLED(void *pvParameters)//LED任务
{
	for(;;){
	GPIO_SetBits(GPIOB, GPIO_Pin_5); 


	}
}
static void vTaskUART(void *pvParameters)//串口任务
{
	for(;;){

	printf("\r\n您发送的消息为:\r\n\r\n");	

	}
}
/*
*********************************************************************************************************
*函数名称： AppTaskCreate
*功能说明： 任务创建
*形    参： 无
*返回值  ： 无
*********************************************************************************************************
*/
void AppTaskCreate (void)
{
//    xTaskCreate( vTaskTaskUserIF,   	/* è???oˉêy  */
//                 "vTaskUserIF",     	/* è?????    */
//                 512,               	/* è?????′óD?￡?μ￥??word￡?ò2?íê?4×??ú */
//                 NULL,              	/* è???2?êy  */
//                 1,                 	/* è???ó??è??*/
//                 &xHandleTaskUserIF );  /* è?????±ú  */
//	
//	
//	xTaskCreate( vTaskLED,    		/* è???oˉêy  */
//                 "vTaskLED",  		/* è?????    */
//                 512,         		/* è?????′óD?￡?μ￥??word￡?ò2?íê?4×??ú */
//                 NULL,        		/* è???2?êy  */
//                 2,           		/* è???ó??è??*/
//                 &xHandleTaskLED ); /* è?????±ú  */
//	
//	xTaskCreate( vTaskMsgPro,     		/* è???oˉêy  */
//                 "vTaskMsgPro",   		/* è?????    */
//                 512,             		/* è?????′óD?￡?μ￥??word￡?ò2?íê?4×??ú */
//                 NULL,           		/* è???2?êy  */
//                 3,               		/* è???ó??è??*/
//                 &xHandleTaskMsgPro );  /* è?????±ú  */
	xTaskCreate( vTaskUART,     		/* 任务函数  */
                 "vTaskUART",   		/* 任务名    */
                 512,            		/* 任务堆栈大小，单位为字（4字节） */
                 NULL,           		/* 任务参数  */
                 4,              		/* 任务优先级*/
                 &xHandleTaskUART );   /* 任务句柄  */	
	
	xTaskCreate( vTaskLED,     		/* 任务函数  */
                 "vTaskLED",   		/* 任务名    */
                 512,            		/* 任务堆栈大小，单位为字（4字节） */
                 NULL,           		/* 任务参数  */
                 4,              		/* 任务优先级*/
                 &xHandleTaskLED );   /* 任务句柄  */
}












