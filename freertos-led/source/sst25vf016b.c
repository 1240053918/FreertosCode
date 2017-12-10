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
* 名    称：void wen(void)
* 功    能：写使能
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void wen(void){
	SPI1_CS_L();
	SPI1_SendByte(0x06);
	SPI1_CS_H();
}

/****************************************************************************
* 名    称：void wdis(void)
* 功    能：写禁止
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void wdis(void){

	SPI1_CS_L();
	SPI1_SendByte(0x04); 
	SPI1_CS_H();
	wip();
	
}	
/****************************************************************************
* 名    称：void wsr(void)
* 功    能：写状态
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
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
* 名    称：void wip(void)
* 功    能：忙检测
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void wip(void){
	unsigned char a=1;
	while((a&0x01)==1) a=rdsr();	

}
/****************************************************************************
* 名    称：unsigned char rdsr(void)
* 功    能：读状态寄存器
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
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
* 名    称：void SST25_R_BLOCK(unsigned long addr, unsigned char *readbuff, unsigned int BlockSize)
* 功    能：页读
* 入口参数：unsigned long addr--页   unsigned char *readbuff--数组   unsigned int BlockSize--长度
* 出口参数：无
* 说    明：
* 调用方法：无 
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
* 名    称：void SST25_W_BLOCK(uint32_t addr, u8 *readbuff, uint16_t BlockSize)
* 功    能：页写
* 入口参数：uint32_t addr--页   u8 *readbuff--数组   uint16_t BlockSize--长度    
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/  
void SST25_W_BLOCK(uint32_t addr, u8 *readbuff, uint16_t BlockSize){
	unsigned int i=0,a2;
	sect_clr(addr);   								  //删除页		  
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
* 名    称：void sect_clr(unsigned long a1)
* 功    能：页擦除
* 入口参数：unsigned long a1--页   
* 出口参数：无
* 说    明：
* 调用方法：无 
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
* 名    称：void FlashReadID(void)
* 功    能：读工厂码及型号的函数
* 入口参数：  
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
uint8_t dat;
void FlashReadID(void)
{
	SPI1_CS_L();	
  	SPI1_SendByte(0x90);
	dat=SPI1_SendByte(0x00);
	dat=SPI1_SendByte(0x00);
	dat=SPI1_SendByte(0x00);
  	//fac_id= SPI1_ReadByte();		          //BFH: 工程码SST
	//dev_id= SPI1_ReadByte();	              //41H: 器件型号SST25VF016B     
  	SPI1_CS_H();	
}
