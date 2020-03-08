/*Libraries Iclusion*/

/*Library Layer*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*MCAL LAYER*/
#include "RCC_interface.h"
#include "RCC_register.h"
#include "RCC_private.h"
#include "RCC_config.h"

extern void RCC_Init(void)
{
	/*HSI -> off
	  PLL -> off
	  HSE -> on
	  CSS -> off */
	//RCC_CR=0x00010000;

	RCC_CR=0x00010000;
	
	/* SysClk 			-> HSE
	   AHB,APB1,APB2 	-> No division
	   MCO 				-> Not connected */
	RCC_CFGR=0x00000001;
}

extern void RCC_EnablePeripheralClock (u8 Bus,u8 Peripheral)
{
	switch(Bus)
	{
		case 0: SET_BIT(RCC_AHBENR ,Peripheral);break;
		case 1: SET_BIT(RCC_APB2ENR,Peripheral);break;
		case 2: SET_BIT(RCC_APB1ENR,Peripheral);break;
	}
}

extern void RCC_DisablePeripheralClock(u8 Bus,u8 Peripheral)
{
	switch(Bus)
	{
		case 0: CLR_BIT(RCC_AHBENR ,Peripheral);break;
		case 1: CLR_BIT(RCC_APB2ENR,Peripheral);break;
		case 2: CLR_BIT(RCC_APB1ENR,Peripheral);break;
	}	
}
