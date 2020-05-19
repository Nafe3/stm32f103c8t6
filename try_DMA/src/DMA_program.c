/****************************************************/
/* Author : Mirna Anis */
/* Date : 30 march 2020 */
/* Version : 1.0 */
/****************************************************/

#include "STD_TYPE.h"
#include "BIT_MATH.h"

#include "DMA_interface.h"
#include "DMA_register.h"
#include "DMA_config.h"
#include "DMA_private.h"

/* DMA channel 1 initialization */
void DMA_Init(void)
{
  /* Enable M2M
     Data size 32 Bit
     MINC and PIN = 1
     No Circular
     CPAR -> CMAR
     Transmission complete interrupt */
  myDMA->Channel[0].CCR = 0x00007AC2;
  
}

/* DMA 1 channel start */
void DMA_Start(u32 copy_u32SourceAddress, u32 copy_u32DestinationAddress, u16 copy_u16BlockLength)
{
  
  myDMA->Channel[0].CPAR = copy_u32SourceAddress;
  myDMA->Channel[0].CMAR = copy_u32DestinationAddress;
  myDMA->Channel[0].CNDTR = copy_u16BlockLength;
  
  /* DMA channel 1 enable */
  myDMA->Channel[0].CCR |= 1;
}

