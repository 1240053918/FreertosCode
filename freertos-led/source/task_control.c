#include "include.h"

//*****************����������*****************//
static TaskHandle_t xHandleTaskLED;
static TaskHandle_t xHandleTaskUART;


//*****************����������*****************//
static void vTaskLED(void *pvParameters)//LED����
{
	for(;;){
	GPIO_SetBits(GPIOB, GPIO_Pin_5); 


	}
}
static void vTaskUART(void *pvParameters)//��������
{
	for(;;){

	printf("\r\n�����͵���ϢΪ:\r\n\r\n");	

	}
}
/*
*********************************************************************************************************
*�������ƣ� AppTaskCreate
*����˵���� ���񴴽�
*��    �Σ� ��
*����ֵ  �� ��
*********************************************************************************************************
*/
void AppTaskCreate (void)
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
	xTaskCreate( vTaskUART,     		/* ������  */
                 "vTaskUART",   		/* ������    */
                 512,            		/* �����ջ��С����λΪ�֣�4�ֽڣ� */
                 NULL,           		/* �������  */
                 4,              		/* �������ȼ�*/
                 &xHandleTaskUART );   /* ������  */	
	
	xTaskCreate( vTaskLED,     		/* ������  */
                 "vTaskLED",   		/* ������    */
                 512,            		/* �����ջ��С����λΪ�֣�4�ֽڣ� */
                 NULL,           		/* �������  */
                 4,              		/* �������ȼ�*/
                 &xHandleTaskLED );   /* ������  */
}












