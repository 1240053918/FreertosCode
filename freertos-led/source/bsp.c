#include "bsp.h"
#include "ff.h"
#include "diskio.h"
#include <stdio.h>
//FILE *F;
char path_holter[]="xxx.dcm";//�ļ�·��
FATFS Fatfs;				/* File system specific */
FRESULT result;				/* FatFs function common result code */
UINT br, bw;				/* File read/write count */
DSTATUS resCard;			/* SDcard status */
FIL file;
FATFS *pfs;
DWORD fre_clust;
//#include "sdio_sdcard.h"   
#define SEND_BUF_SIZE 14	//�������ݳ���,��õ���sizeof(TEXT_TO_SEND)+2��������.

uint8_t SendBuff[SEND_BUF_SIZE]={0,1,2,3,4,5,6,7,8,9,10};	//�������ݻ�����
//ͨ�����ڴ�ӡSD�������Ϣ
void show_sdcard_info(void)
{
	switch(SDCardInfo.CardType)
	{
		case SDIO_STD_CAPACITY_SD_CARD_V1_1:printf("Card Type:SDSC V1.1\r\n");break;
		case SDIO_STD_CAPACITY_SD_CARD_V2_0:printf("Card Type:SDSC V2.0\r\n");break;
		case SDIO_HIGH_CAPACITY_SD_CARD:printf("Card Type:SDHC V2.0\r\n");break;
		case SDIO_MULTIMEDIA_CARD:printf("Card Type:MMC Card\r\n");break;
	}	
  printf("Card ManufacturerID:%d\r\n",SDCardInfo.SD_cid.ManufacturerID);	//������ID
 	printf("Card RCA:%d\r\n",SDCardInfo.RCA);								//����Ե�ַ
	printf("Card Capacity:%d MB\r\n",(u32)(SDCardInfo.CardCapacity>>20));	//��ʾ����
 	printf("Card BlockSize:%d\r\n\r\n",SDCardInfo.CardBlockSize);			//��ʾ���С
}	
uint8_t bufffer[512]={0,1,2,3,4,5,6,7,8,9,12}; 

void bsp_init(void)
{
	//�ж����ȼ���������Ϊ4��������0-15����ռʽ���ȼ���0�������ȼ����Ȳ����������ȼ���
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	uint8_t ss;
	uint32_t sd_size;
	
	LED_Config();//LED�������ó�ʼ��
	USART_Config(USART2);//���ڳ�ʼ��
  SPI1_Init();//SPI1��ʼ��
	DMA_Config(DMA1_Channel7,(u32)&USART2->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,����SEND_BUF_SIZE.   
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE); //ʹ�ܴ���1��DMA����      
	delay_init();//��ʱ������ʼ��
	Adc_Config();//adc��ʼ��
	EXTIX_Init();//�����жϳ�ʼ��
	 	while(SD_Init())//��ⲻ��SD��
	{
		printf("SD Card Error!");
		delay_ms(500);					
		printf("Please Check! ");
		delay_ms(500);
//		LED0=!LED0;//DS0��˸
	}
	if(disk_initialize(0))
	{}
		else
		{
		result = f_mount(&Fatfs,"",0);
		sprintf(path_holter,"%03d.dcm",001);
		result = f_open(&file, path_holter, FA_OPEN_EXISTING | FA_WRITE);
		
		}
//	show_sdcard_info();	//��ӡSD�������Ϣ
//// 	POINT_COLOR=BLUE;	//��������Ϊ��ɫ 
//	//���SD���ɹ� 											    
//	printf("SD Card OK    ");
//	printf("SD Card Size:     MB");

//				if(SD_ReadDisk(bufffer,9,1)==0)	//��ȡ0����������
//			{	

//				printf("SECTOR 0 DATA:\r\n");
//				for(sd_size=0;sd_size<512;sd_size++)printf("%x ",bufffer[sd_size]);//��ӡ0��������    	   
//				printf("\r\nDATA ENDED\r\n");

//			}
 
}


