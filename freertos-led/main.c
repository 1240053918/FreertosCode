#include "include.h"







int main(void)
{
//	SystemInit();

	__set_PRIMASK(1);  
	
	/* Ӳ����ʼ�� */
	bsp_init();
//	GPIO_SetBits(GPIOB, GPIO_Pin_5); 	
	vSetupSysInfoTest();
	/* ���񴴽� */
	AppTaskCreate();
	/* ��������ͬ����Ϣ */
	AppObjCreate();
    /* ������������� */
	vTaskStartScheduler();


	while(1);
}

