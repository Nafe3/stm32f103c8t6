// libs
#include "STD_TYPES.h"
#include "BIT_MAN.h"
// own
#include "RCC_interface.h"
#include "RCC_registers.h"
#include "RCC_private.h"
#include "RCC_config.h"

void RCC_init(void)
{
	  /*HSI off
	    PLL off
	    CSS off
	    HSE on
	  */
	  RCC_CR=0x00010000;

	  /*SYSCLCK         HSE
	    AHB, APB1, ABP2 SYSCLK
	    MCO             not connected
	  */
	  RCC_CFGR=0x00000001;
}

void RCC_enablePeriClock(u8 bus, u8 peri)
{
   switch (bus)
   {
      case 0:
    	  RCC_AHBENR = BIT_SET(RCC_AHBENR, peri);
      break;
      
      case 1:
    	  RCC_APB1ENR = BIT_SET(RCC_APB1ENR, peri);
      break;
      
      case 2:
    	  RCC_APB2ENR = BIT_SET(RCC_APB2ENR, peri);
      break;
   }
}

extern void RCC_disablePeriClock(u8 bus, u8 peri)
{
   switch (bus)
   {
      case 0:
    	  RCC_AHBENR = BIT_CLEAR(RCC_AHBENR, peri);
      break;
      
      case 1:
    	  RCC_APB1ENR = BIT_CLEAR(RCC_APB1ENR, peri);
      break;
      
      case 2:
    	  RCC_APB2ENR = BIT_CLEAR(RCC_APB2ENR, peri);
      break;
   }
}
