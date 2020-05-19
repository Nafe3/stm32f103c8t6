#include "STD_TYPE.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DMA_interface.h"
#include "NVIC_interface.h"

void DMA1_Channel1_IRQHandler();

u32 Arr_src[1000] = {0};
u32 Arr_dest[1000];
u16 i;

void main(void)
{
  /* Enable clock DMA 1 */
  RCC_Init();
  RCC_EnablePeripheralClock(0,0);
  
  /* Enable DMA 1 channel 1 interrupt from NVIC */
  NVIC_voidEnableExtInt(11);
  
  /* DMA init */
  DMA_Init();
  
  /* DMA start */
  DMA_Start((u32)Arr_src, (u32)Arr_dest, 1000);

  for(i = 0; i < 1000; i++)
  {
    Arr_dest[i] = Arr_src[i];
  }

  while(1)
  {
    
  }
}

void DMA1_Channel1_IRQHandler()
{
  asm("NOP");
}
