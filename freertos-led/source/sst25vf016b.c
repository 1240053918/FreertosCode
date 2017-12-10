#include "bsp.h"

#include "sst25vf016b.h"




void wip(void);
void wen(void);
void wdis(void);
void wsr(void);
unsigned char rdsr(void);
void FlashReadID(void);
void sect_clr(unsigned long a1);  



/****************************************************************************
* ��    �ƣ�void wen(void)
* ��    �ܣ�дʹ��
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void wen(void){
	SPI1_CS_L();
	SPI1_SendByte(0x06);
	SPI1_CS_H();
}

/****************************************************************************
* ��    �ƣ�void wdis(void)
* ��    �ܣ�д��ֹ
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void wdis(void){

	SPI1_CS_L();
	SPI1_SendByte(0x04); 
	SPI1_CS_H();
	wip();
	
}	
/****************************************************************************
* ��    �ƣ�void wsr(void)
* ��    �ܣ�д״̬
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void wsr(void){	
	SPI1_CS_L();
	SPI1_SendByte(0x50);
	SPI1_CS_H(); 
	SPI1_CS_L();
	SPI1_SendByte(0x01);
	SPI1_SendByte(0x00); 
	SPI1_CS_H();
    wip();
}

/****************************************************************************
* ��    �ƣ�void wip(void)
* ��    �ܣ�æ���
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void wip(void){
	unsigned char a=1;
	while((a&0x01)==1) a=rdsr();	

}
/****************************************************************************
* ��    �ƣ�unsigned char rdsr(void)
* ��    �ܣ���״̬�Ĵ���
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
unsigned char rdsr(void){
	unsigned char busy;
	SPI1_CS_L();
	SPI1_SendByte(0x05);
	busy = SPI1_ReadByte();
	SPI1_CS_H();
	return(busy);
	
}

/****************************************************************************
* ��    �ƣ�void SST25_R_BLOCK(unsigned long addr, unsigned char *readbuff, unsigned int BlockSize)
* ��    �ܣ�ҳ��
* ��ڲ�����unsigned long addr--ҳ   unsigned char *readbuff--����   unsigned int BlockSize--����
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/  
void SST25_R_BLOCK(unsigned long addr, unsigned char *readbuff, unsigned int BlockSize){
	unsigned int i=0; 	
	SPI1_CS_L();
	SPI1_SendByte(0x0b);
	SPI1_SendByte((addr&0xffffff)>>16);
	SPI1_SendByte((addr&0xffff)>>8);
	SPI1_SendByte(addr&0xff);
	SPI1_SendByte(0);
	while(i<BlockSize){	
		readbuff[i]=SPI1_ReadByte();
		
		i++;
	}
	SPI1_CS_H();	 	
}
/****************************************************************************
* ��    �ƣ�void SST25_W_BLOCK(uint32_t addr, u8 *readbuff, uint16_t BlockSize)
* ��    �ܣ�ҳд
* ��ڲ�����uint32_t addr--ҳ   u8 *readbuff--����   uint16_t BlockSize--����    
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/  
void SST25_W_BLOCK(uint32_t addr, u8 *readbuff, uint16_t BlockSize){
	unsigned int i=0,a2;
	sect_clr(addr);   								  //ɾ��ҳ		  
	wsr();
  	wen();	
	SPI1_CS_L();    
	SPI1_SendByte(0xad);
	SPI1_SendByte((addr&0xffffff)>>16);
	SPI1_SendByte((addr&0xffff)>>8);
	SPI1_SendByte(addr&0xff);
  SPI1_SendByte(readbuff[0]);
	SPI1_SendByte(readbuff[1]);
	SPI1_CS_H();
	i=2;
	while(i<BlockSize){
		a2=120;
		while(a2>0) a2--;
		SPI1_CS_L();
		SPI1_SendByte(0xad);
		SPI1_SendByte(readbuff[i++]);
		SPI1_SendByte(readbuff[i++]);
		SPI1_CS_H();
	}
	
	a2=100;
	while(a2>0) a2--;
	wdis();	
	SPI1_CS_L();	
	wip();
}
/****************************************************************************
* ��    �ƣ�void sect_clr(unsigned long a1)
* ��    �ܣ�ҳ����
* ��ڲ�����unsigned long a1--ҳ   
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void sect_clr(unsigned long a1){
	wsr();
	wen();     
	SPI1_CS_L();	  
	SPI1_SendByte(0x20);
	SPI1_SendByte((a1&0xffffff)>>16);          //addh
	SPI1_SendByte((a1&0xffff)>>8);          //addl 
	SPI1_SendByte(a1&0xff);                 //wtt
	SPI1_CS_H();
	wip();
	
}
/****************************************************************************
* ��    �ƣ�void FlashReadID(void)
* ��    �ܣ��������뼰�ͺŵĺ���
* ��ڲ�����  
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
uint8_t dat;
void FlashReadID(void)
{
	SPI1_CS_L();	
  	SPI1_SendByte(0x90);
	dat=SPI1_SendByte(0x00);
	dat=SPI1_SendByte(0x00);
	dat=SPI1_SendByte(0x00);
  	//fac_id= SPI1_ReadByte();		          //BFH: ������SST
	//dev_id= SPI1_ReadByte();	              //41H: �����ͺ�SST25VF016B     
  	SPI1_CS_H();	
}
