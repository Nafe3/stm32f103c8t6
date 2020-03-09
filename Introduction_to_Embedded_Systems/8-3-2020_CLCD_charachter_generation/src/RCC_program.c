/*Libraries Iclusion*/
/*Library Layer*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*MCAL LAYER*/
#include "RCC_interface.h"
#include "RCC_register.h"







extern void RCC_Init(void)
{
	SET_BIT(RCC_CR,16);//HSEON Bit on

	SET_BIT(RCC_CFGR,0);//Switch to HSE, since the processor is connected to PLL by default(start-up code)
	CLR_BIT(RCC_CFGR,1);//Switch to HSE

}

extern void RCC_EnablePeripheralClock (u8 Bus,u8 Peripheral)
{
	switch(Bus)
	{
		case 0: SET_BIT(RCC_AHBENR ,Peripheral);break;
		case 1: SET_BIT(RCC_APB1ENR,Peripheral);break;
		case 2: SET_BIT(RCC_APB2ENR,Peripheral);break;
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
