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
	SET_BIT(RCC_CR,16);//HSEON Bit on

	SET_BIT(RCC_CFGR,0);//Switch to HSE, since the processor is connected to PLL by default(start-up code)
	CLR_BIT(RCC_CFGR,1);//Switch to HSE

	CLR_BIT(RCC_CR,24);//turn off PLL

	SET_BIT(RCC_CFGR,18);//PLLMUL bit0
	SET_BIT(RCC_CFGR,19);//PLLMUL bit1
	SET_BIT(RCC_CFGR,20);//PLLMUL bit2
	CLR_BIT(RCC_CFGR,21);//PLLMUL bit3

	CLR_BIT(RCC_CFGR,17);//HSE as PLL source not divided

	SET_BIT(RCC_CFGR,16);//HSE oscillator clock selected as PLL input clock
	SET_BIT(RCC_CR,24);//turn on PLL

	CLR_BIT(RCC_CFGR,0);//Switch to PLL, since the processor is connected to PLL by default(start-up code)
	SET_BIT(RCC_CFGR,1);//Switch to PLL

	SET_BIT(RCC_CFGR,26);//MCO source is SYSCLK
	CLR_BIT(RCC_CFGR,25);//MCO source is SYSCLK
	CLR_BIT(RCC_CFGR,24);//MCO source is SYSCLK

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
