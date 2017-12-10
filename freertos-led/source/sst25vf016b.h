#ifndef __SST25VF01B_H
#define __SST25VF01B_H
#include "stm32f10x.h"
#include "stm32f10x_spi.h"	







void FlashReadID(void);
void SST25_R_BLOCK(unsigned long addr, unsigned char *readbuff, unsigned int BlockSize);
void SST25_W_BLOCK(uint32_t addr, u8 *readbuff, uint16_t BlockSize);

#endif
