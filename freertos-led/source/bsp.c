#include "bsp.h"
#include "ff.h"
#include "diskio.h"
#include <stdio.h>
//FILE *F;
char path_holter[]="xxx.dcm";//文件路径
FATFS Fatfs;				/* File system specific */
FRESULT result;				/* FatFs function common result code */
UINT br, bw;				/* File read/write count */
DSTATUS resCard;			/* SDcard status */
FIL file;
FATFS *pfs;
DWORD fre_clust;
//#include "sdio_sdcard.h"   
#define SEND_BUF_SIZE 14	//发送数据长度,最好等于sizeof(TEXT_TO_SEND)+2的整数倍.

uint8_t SendBuff[SEND_BUF_SIZE]={0,1,2,3,4,5,6,7,8,9,10};	//发送数据缓冲区
//通过串口打印SD卡相关信息
void show_sdcard_info(void)
{
	switch(SDCardInfo.CardType)
	{
		case SDIO_STD_CAPACITY_SD_CARD_V1_1:printf("Card Type:SDSC V1.1\r\n");break;
		case SDIO_STD_CAPACITY_SD_CARD_V2_0:printf("Card Type:SDSC V2.0\r\n");break;
		case SDIO_HIGH_CAPACITY_SD_CARD:printf("Card Type:SDHC V2.0\r\n");break;
		case SDIO_MULTIMEDIA_CARD:printf("Card Type:MMC Card\r\n");break;
	}	
  printf("Card ManufacturerID:%d\r\n",SDCardInfo.SD_cid.ManufacturerID);	//制造商ID
 	printf("Card RCA:%d\r\n",SDCardInfo.RCA);								//卡相对地址
	printf("Card Capacity:%d MB\r\n",(u32)(SDCardInfo.CardCapacity>>20));	//显示容量
 	printf("Card BlockSize:%d\r\n\r\n",SDCardInfo.CardBlockSize);			//显示块大小
}	
uint8_t bufffer[512]={0,1,2,3,4,5,6,7,8,9,12}; 

void bsp_init(void)
{
	//中断优先级分组设置为4，可配置0-15级抢占式优先级，0级子优先级，既不存在子优先级。
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	uint8_t ss;
	uint32_t sd_size;
	
	LED_Config();//LED引脚配置初始化
	USART_Config(USART2);//串口初始化
  SPI1_Init();//SPI1初始化
	DMA_Config(DMA1_Channel7,(u32)&USART2->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA1通道4,外设为串口1,存储器为SendBuff,长度SEND_BUF_SIZE.   
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE); //使能串口1的DMA发送      
	delay_init();//延时函数初始化
	Adc_Config();//adc初始化
	EXTIX_Init();//按键中断初始化
	 	while(SD_Init())//检测不到SD卡
	{
		printf("SD Card Error!");
		delay_ms(500);					
		printf("Please Check! ");
		delay_ms(500);
//		LED0=!LED0;//DS0闪烁
	}
	if(disk_initialize(0))
	{}
		else
		{
		result = f_mount(&Fatfs,"",0);
		sprintf(path_holter,"%03d.dcm",001);
		result = f_open(&file, path_holter, FA_OPEN_EXISTING | FA_WRITE);
		
		}
//	show_sdcard_info();	//打印SD卡相关信息
//// 	POINT_COLOR=BLUE;	//设置字体为蓝色 
//	//检测SD卡成功 											    
//	printf("SD Card OK    ");
//	printf("SD Card Size:     MB");

//				if(SD_ReadDisk(bufffer,9,1)==0)	//读取0扇区的内容
//			{	

//				printf("SECTOR 0 DATA:\r\n");
//				for(sd_size=0;sd_size<512;sd_size++)printf("%x ",bufffer[sd_size]);//打印0扇区数据    	   
//				printf("\r\nDATA ENDED\r\n");

//			}
 
}


