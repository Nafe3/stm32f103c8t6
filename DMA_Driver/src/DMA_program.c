#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DMA_interface.h"
#include "DMA_register.h"
#include "DMA_private.h"
#include "DMA_config.h"


/*DMA Channel 1 Initialization*/
void DMA_Init(void)
{
	/*CCR register*/
	/*Enable M2M*/
	/*Data Size 32 bit*/
	/*MINC and PINC =1*/
	/*No circular*/
	/*CPAR -> CMAR*/
	/*Transmission complete interrupt*/
	myDMA->Channel[0].CCR = 0x00007AC2;
}

/*SWtart channel 1*/
void DMA_Start(u32 SourceAddress, u32 DestinationAddress, u16 BlockLength)
{
/* SourceAddress -> CPAR
 * DestinationAddress -> CMAR
 * BlockLength -> CNDTR
 * */
	myDMA->Channel[0].CPAR = SourceAddress;
	myDMA->Channel[0].CMAR = DestinationAddress;
	myDMA->Channel[0].CNDTR= BlockLength;

	/*DMA Channel 1 Enable*/
	myDMA->Channel[0].CCR |= 1;
}
