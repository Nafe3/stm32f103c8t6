
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "RCC_register.h"
#include "RCC_interface.h"
#include "DIO_interface.h"
#include "DIO_register.h"



extern void RCC_Init(void)
{
	/*
		HSE -> ON
	*/
	
	RCC_CR = 0x00010000;
	/*

		SWS= 01
	*/
	
	RCC_CFGR = 0x00000001;
}

extern void RCC_EnablePeripheralClock(u8 Bus, u8 Peripheral)
{
	switch(Bus)
	{
		case 0: SET_BIT(RCC_AHBENR, Peripheral); break;
		case 1: SET_BIT(RCC_APB1ENR, Peripheral); break;
		case 2: SET_BIT(RCC_APB2ENR, Peripheral); break;
	}
}
extern void RCC_DisablePeripheralClock(u8 Bus, u8 Peripheral)
{
	switch(Bus)
	{
		case 0: CLR_BIT(RCC_AHBENR, Peripheral); break;
		case 1: CLR_BIT(RCC_APB1ENR, Peripheral); break;
		case 2: CLR_BIT(RCC_APB2ENR, Peripheral); break;
	}
}
