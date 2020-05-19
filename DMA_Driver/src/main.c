/* 1. Source address
 * 2. Destination address
 * 3. data size
 * 4. Block Length
 * 5. SINC & DINC
 * 6. Circular (Repeat)
 * 7. End of transfer Interrupt
 * 8. Trigger Source
 * */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC.h"
#include "DMA_interface.h"
#include "NVIC.h"

void DMA1_Channel1_IRQHandler(void);

u32 Arr_Src[1000]={0};
u32 Arr_Des[1000];
u16 i;
int main(void)
{


	RCC_voidSelectSysClk(HSE);
	/*Enable RCC for DMA1*/
	RCC_voidEnablePeripheral(AHB,RCC_AHBENR_DMA1EN,ON);

	/*Enable DMA1 Channel 1 Interrupt from NVIC*/
	NVIC_u8EnableEXTI(11);

	/*DMA Init*/
	DMA_Init();

	/*DMA Start*/
	DMA_Start((u32)Arr_Src, (u32)Arr_Des, 1000);



	for(i=0;i<1000;i++)
	{
		Arr_Des[i]=Arr_Src;
	}

	while(1)
	{

	}
}

void DMA1_Channel1_IRQHandler(void)
{
	asm("NOP");
}
