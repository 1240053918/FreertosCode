#include "include.h"







int main(void)
{
//	SystemInit();

	__set_PRIMASK(1);  
	
	/* 硬件初始化 */
	bsp_init();
//	GPIO_SetBits(GPIOB, GPIO_Pin_5); 	
	/* 任务创建 */
	AppTaskCreate();
	
    /* 开启任务调度器 */
	vTaskStartScheduler();


	while(1);
}

