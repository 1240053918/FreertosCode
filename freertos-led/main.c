#include "include.h"







int main(void)
{
//	SystemInit();

	__set_PRIMASK(1);  
	
	/* 硬件初始化 */
	bsp_init();
//	GPIO_SetBits(GPIOB, GPIO_Pin_5); 	
	vSetupSysInfoTest();
	/* 任务创建 */
	AppTaskCreate();
	/* 创建任务同步信息 */
	AppObjCreate();
    /* 开启任务调度器 */
	vTaskStartScheduler();


	while(1);
}

