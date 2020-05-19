#ifndef _DMA_INTERFACE_H
#define _DMA_INTERFACE_H


/*DMA Channel 1 Initialization*/
void DMA_Init(void);

/*SWtart channel 1*/
void DMA_Start(u32 SourceAddress, u32 DestinationAddress, u16 BlockLength);




#endif
