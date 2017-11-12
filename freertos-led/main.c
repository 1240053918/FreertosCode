#include "include.h"


static TaskHandle_t xHandleTaskLED = NULL;
static void AppTaskCreate (void);
void LED_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD , ENABLE);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				     //LED1  V6	   //��V6,V7,V8 ����Ϊͨ���������  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���߷�ת�ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_3;		 //LED2, LED3	 V7 V8
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 			      //LCD�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD, GPIO_Pin_13);			              //LCD����ر�	

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
	
	/* ��2?t3?��??�� */
	LED_Config();
	
	/* ���?����??? */
	AppTaskCreate();
	
    /* ???���̡�?����??a��??��DD��??? */
    vTaskStartScheduler();

	/* 
	  ��?1??�̨�3?y3��???����?2??��??DD��??a��?��?��???DD��??a��???��D?��?����?��?����?������?�¨�????��?????D��???��?
	  heap????2?��??��3�����?������㨹��?��?��a?���䨮FreeRTOSConfig.h???t?D?����?��?heap�䨮D?��o
	  #define configTOTAL_HEAP_SIZE	      ( ( size_t ) ( 17 * 1024 ) )
	*/
	while(1);
}
/*
*********************************************************************************************************
*�������ƣ� AppTaskCreate
*����˵���� ���񴴽�
*��    �Σ� ��
*����ֵ  �� ��
*********************************************************************************************************
*/
static void AppTaskCreate (void)
{
//    xTaskCreate( vTaskTaskUserIF,   	/* ��???o����y  */
//                 "vTaskUserIF",     	/* ��?????    */
//                 512,               	/* ��?????�䨮D?��?�̣�??word��?��2?����?4��??�� */
//                 NULL,              	/* ��???2?��y  */
//                 1,                 	/* ��???��??��??*/
//                 &xHandleTaskUserIF );  /* ��?????����  */
//	
//	
//	xTaskCreate( vTaskLED,    		/* ��???o����y  */
//                 "vTaskLED",  		/* ��?????    */
//                 512,         		/* ��?????�䨮D?��?�̣�??word��?��2?����?4��??�� */
//                 NULL,        		/* ��???2?��y  */
//                 2,           		/* ��???��??��??*/
//                 &xHandleTaskLED ); /* ��?????����  */
//	
//	xTaskCreate( vTaskMsgPro,     		/* ��???o����y  */
//                 "vTaskMsgPro",   		/* ��?????    */
//                 512,             		/* ��?????�䨮D?��?�̣�??word��?��2?����?4��??�� */
//                 NULL,           		/* ��???2?��y  */
//                 3,               		/* ��???��??��??*/
//                 &xHandleTaskMsgPro );  /* ��?????����  */
	
	
	xTaskCreate( vTaskLED,     		/* ��???o����y  */
                 "vTaskLED",   		/* ��?????    */
                 512,            		/* ��?????�䨮D?��?�̣�??word��?��2?����?4��??�� */
                 NULL,           		/* ��???2?��y  */
                 4,              		/* ��???��??��??*/
                 &xHandleTaskLED );   /* ��?????����  */
}
