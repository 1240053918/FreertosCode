#include "include.h"


static TaskHandle_t xHandleTaskLED = NULL;
static void AppTaskCreate (void);
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
static void vTaskLED(void *pvParameters)
{
	for(;;){
	GPIO_SetBits(GPIOB, GPIO_Pin_5); 
	}
}
int main(void)
{
//	SystemInit();

	__set_PRIMASK(1);  
	
	/* ó2?t3?ê??ˉ */
	LED_Config();
	
	/* ′′?¨è??? */
	AppTaskCreate();
	
    /* ???ˉμ÷?è￡??aê??′DDè??? */
    vTaskStartScheduler();

	/* 
	  è?1??μí3?y3￡???ˉê?2??á??DDμ??aà?μ?￡???DDμ??aà???óD?é?üê?ó?óú?¨ê±?÷è????ò?????Dè???μ?
	  heap????2?×??ì3é′′?¨ê§°ü￡?′?òa?ó′óFreeRTOSConfig.h???t?D?¨ò?μ?heap′óD?￡o
	  #define configTOTAL_HEAP_SIZE	      ( ( size_t ) ( 17 * 1024 ) )
	*/
	while(1);
}
/*
*********************************************************************************************************
*函数名称： AppTaskCreate
*功能说明： 任务创建
*形    参： 无
*返回值  ： 无
*********************************************************************************************************
*/
static void AppTaskCreate (void)
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
	
	
	xTaskCreate( vTaskLED,     		/* è???oˉêy  */
                 "vTaskLED",   		/* è?????    */
                 512,            		/* è?????′óD?￡?μ￥??word￡?ò2?íê?4×??ú */
                 NULL,           		/* è???2?êy  */
                 4,              		/* è???ó??è??*/
                 &xHandleTaskLED );   /* è?????±ú  */
}
