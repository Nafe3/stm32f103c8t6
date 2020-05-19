#ifndef _DMA_REGISTER_H
#define _DMA_REGISTER_H

typedef struct{
	u32 CCR;									//DMA channel configuration register
	u32 CNDTR;									//DMA channel x number of data register
	u32 CPAR; 									//DMA channel x peripheral address register
	u32 CMAR; 									//DMA channel x memory address register
	u32 Reserved;
}DMA_Channel_register_t;

typedef struct{
	u32 					ISR;				//DMA interrupt status register
	u32 					IFCR;				//DMA interrupt flag clear register
	DMA_Channel_register_t  Channel[7];
}DMA_t;


#define myDMA ((volatile DMA_t*)0x40020000)



#endif
