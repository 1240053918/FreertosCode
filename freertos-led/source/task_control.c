#include "include.h"



//*****************����������*****************//
static TaskHandle_t xHandleTaskLED;
static TaskHandle_t xHandleTaskUART;
static TaskHandle_t xHandleTaskSPIFLASH;
static EventGroupHandle_t xCreatedEventGroup = NULL;
uint16_t tem;
//*****************����������*****************//
static void vTaskLED(void *pvParameters)//LED����
{
	for(;;){
//vTaskDelete(xHandleTaskSPIFLASH);
	tem=Get_Temprate();

	}
}
static void vTaskUART(void *pvParameters)//��������
{	

	for(;;){
	uint8_t pcWriteBuffer[500];		
 xEventGroupWaitBits(xCreatedEventGroup, /* �¼���־���� */
	0x01, /* �ȴ� bit0 �� bit1 ������ */
	pdTRUE, /* �˳�ǰ bit0 �� bit1 ������������� bit0 �� bit1
	�������òű�ʾ���˳��� */
	pdTRUE, /* ����Ϊ pdTRUE ��ʾ�ȴ� bit1 �� bit0 ��������*/
	portMAX_DELAY); /* �ȴ��ӳ�ʱ�� */
	printf("=================================================\r\n");
	printf("������      ����״̬ ���ȼ�  ʣ��ջ �������\r\n");
	vTaskList((char *)&pcWriteBuffer);
	printf("%s\r\n", pcWriteBuffer);

	printf("\r\n������       ���м���         ʹ����\r\n");
	vTaskGetRunTimeStats((char *)&pcWriteBuffer);
	printf("%s\r\n", pcWriteBuffer);
//			DMA_Enable(DMA1_Channel7);//��ʼһ��DMA���䣡	  
//	printf("\r\n�����͵���ϢΪ:\r\n\r\n");	

	}
}
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
unsigned char SST25_buffer[4096];
uint8_t TxBuffer1[] = "123456789J";
static void vTaskSPIFLASH(void *pvParameters)//��������
{
	for(;;){
		xEventGroupSetBits(xCreatedEventGroup,0x01);
		SST25_W_BLOCK(0, TxBuffer1,4096);	        //����������д�뵽SST25VF016B��0ҳ��
		Delay(0xffff);
		SST25_R_BLOCK(0, SST25_buffer,4096);	        //��SST25VF016B��0ҳ���������
//	vTaskSuspend(xHandleTaskUART);

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
	xTaskCreate( vTaskSPIFLASH,     		/* ������  */
                 "vTaskSPIFLASH",   		/* ������    */
                 512,            		/* �����ջ��С����λΪ�֣�4�ֽڣ� */
                 NULL,           		/* �������  */
                 4,              		/* �������ȼ�*/
                 &xHandleTaskSPIFLASH );   /* ������  */	
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


/*
*********************************************************************************************************
*�������ƣ� vApplicationStackOverflowHook
*����˵���� ��ջ��⹳�Ӻ���
*��    �Σ� xTask         ������ջ���������
					  pcTaskName    ������ջ�����������
*����ֵ  �� ��
*********************************************************************************************************
*/
void vApplicationStackOverflowHook( TaskHandle_t xTask, signed char *pcTaskName )
{
	printf("����%s ����ջ���\r\n", pcTaskName);
}


void EXTI2_IRQHandler(void)
{
	
BaseType_t xResult;
BaseType_t xHigherPriorityTaskWoken = pdFALSE;
//	delay_ms(5);//����
	if(KEY2==0)	  //����KEY2
	{
//			xTaskResumeFromISR(xHandleTaskUART);
	/* ������ vTaskMsgPro �����¼���־ */
//	xResult = xEventGroupSetBitsFromISR(xCreatedEventGroup, 0x01,&xHigherPriorityTaskWoken);
		/* ��Ϣ���ɹ����� */
//if( xResult != pdFAIL )
//{
///* ��� xHigherPriorityTaskWoken = pdTRUE����ô�˳��жϺ��е���ǰ������ȼ�����ִ�� */
//portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
//}
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
//printf("��ǰ��ϵͳʱ�ӽ����� = %d\r\n", xTaskGetTickCountFromISR());
	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE2�ϵ��жϱ�־λ  
}


/*
*********************************************************************************************************
* �� �� ��: AppObjCreate
* ����˵��: ��������ͨ�Ż���
* �� ��: ��
* �� �� ֵ: ��
*********************************************************************************************************
*/
void AppObjCreate (void)
{
/* �����¼���־�� */
	xCreatedEventGroup = xEventGroupCreate();
	if(xCreatedEventGroup == NULL)
	{
	/* û�д����ɹ����û�������������봴��ʧ�ܵĴ������ */
	}
}




