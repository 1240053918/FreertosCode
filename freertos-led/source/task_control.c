#include "include.h"



//*****************任务句柄定义*****************//
static TaskHandle_t xHandleTaskLED;
static TaskHandle_t xHandleTaskUART;
static TaskHandle_t xHandleTaskSPIFLASH;
static EventGroupHandle_t xCreatedEventGroup = NULL;
uint16_t tem;
//*****************任务函数定义*****************//
static void vTaskLED(void *pvParameters)//LED任务
{
	for(;;){
//vTaskDelete(xHandleTaskSPIFLASH);
	tem=Get_Temprate();

	}
}
static void vTaskUART(void *pvParameters)//串口任务
{	

	for(;;){
	uint8_t pcWriteBuffer[500];		
 xEventGroupWaitBits(xCreatedEventGroup, /* 事件标志组句柄 */
	0x01, /* 等待 bit0 和 bit1 被设置 */
	pdTRUE, /* 退出前 bit0 和 bit1 被清除，这里是 bit0 和 bit1
	都被设置才表示“退出” */
	pdTRUE, /* 设置为 pdTRUE 表示等待 bit1 和 bit0 都被设置*/
	portMAX_DELAY); /* 等待延迟时间 */
	printf("=================================================\r\n");
	printf("任务名      任务状态 优先级  剩余栈 任务序号\r\n");
	vTaskList((char *)&pcWriteBuffer);
	printf("%s\r\n", pcWriteBuffer);

	printf("\r\n任务名       运行计数         使用率\r\n");
	vTaskGetRunTimeStats((char *)&pcWriteBuffer);
	printf("%s\r\n", pcWriteBuffer);
//			DMA_Enable(DMA1_Channel7);//开始一次DMA传输！	  
//	printf("\r\n您发送的消息为:\r\n\r\n");	

	}
}
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
unsigned char SST25_buffer[4096];
uint8_t TxBuffer1[] = "123456789J";
static void vTaskSPIFLASH(void *pvParameters)//串口任务
{
	for(;;){
		xEventGroupSetBits(xCreatedEventGroup,0x01);
		SST25_W_BLOCK(0, TxBuffer1,4096);	        //将册数数据写入到SST25VF016B的0页里
		Delay(0xffff);
		SST25_R_BLOCK(0, SST25_buffer,4096);	        //从SST25VF016B的0页里读出数据
//	vTaskSuspend(xHandleTaskUART);

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
	xTaskCreate( vTaskSPIFLASH,     		/* 任务函数  */
                 "vTaskSPIFLASH",   		/* 任务名    */
                 512,            		/* 任务堆栈大小，单位为字（4字节） */
                 NULL,           		/* 任务参数  */
                 4,              		/* 任务优先级*/
                 &xHandleTaskSPIFLASH );   /* 任务句柄  */	
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


/*
*********************************************************************************************************
*函数名称： vApplicationStackOverflowHook
*功能说明： 堆栈检测钩子函数
*形    参： xTask         发生堆栈溢出任务句柄
					  pcTaskName    发生堆栈溢出任务名字
*返回值  ： 无
*********************************************************************************************************
*/
void vApplicationStackOverflowHook( TaskHandle_t xTask, signed char *pcTaskName )
{
	printf("任务：%s 发现栈溢出\r\n", pcTaskName);
}


void EXTI2_IRQHandler(void)
{
	
BaseType_t xResult;
BaseType_t xHigherPriorityTaskWoken = pdFALSE;
//	delay_ms(5);//消抖
	if(KEY2==0)	  //按键KEY2
	{
//			xTaskResumeFromISR(xHandleTaskUART);
	/* 向任务 vTaskMsgPro 发送事件标志 */
//	xResult = xEventGroupSetBitsFromISR(xCreatedEventGroup, 0x01,&xHigherPriorityTaskWoken);
		/* 消息被成功发出 */
//if( xResult != pdFAIL )
//{
///* 如果 xHigherPriorityTaskWoken = pdTRUE，那么退出中断后切到当前最高优先级任务执行 */
//portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
//}
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
//printf("当前的系统时钟节拍数 = %d\r\n", xTaskGetTickCountFromISR());
	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE2上的中断标志位  
}


/*
*********************************************************************************************************
* 函 数 名: AppObjCreate
* 功能说明: 创建任务通信机制
* 形 参: 无
* 返 回 值: 无
*********************************************************************************************************
*/
void AppObjCreate (void)
{
/* 创建事件标志组 */
	xCreatedEventGroup = xEventGroupCreate();
	if(xCreatedEventGroup == NULL)
	{
	/* 没有创建成功，用户可以在这里加入创建失败的处理机制 */
	}
}




