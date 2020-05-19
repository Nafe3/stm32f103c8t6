/****************************************************/
/* Author : Mirna Anis */
/* Date : 30 march 2020 */
/* Version : 1.0 */
/****************************************************/

#ifndef DMA_INTERFACE_H
#define DMA_INTERFACE_H

/* DMA channel 1 initialization */
void DMA_Init(void);

/* DMA 1 channel start */
void DMA_Start(u32 copy_u32SourceAddress, u32 copy_u32DestinationAddress, u16 copy_u16BlockLength);

#endif