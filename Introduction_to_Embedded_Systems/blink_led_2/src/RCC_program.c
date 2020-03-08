
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_register.h"
#include "RCC_config.h"
#include "RCC_private.h"


void RCC_Init(void)
{
	/*
	 HSI -> off
	 HSE -> ON
	 CSS -> Off
	 PLL -> Off
	
	*/
	RCC_CR=0x00010000;
	
	
	/*
	 SysCLK         -> HSE
	 AHB ,APB1,APB2 -> No Division
	 MC0            -> Not Connected
	*/
	RCC_CFGR=0x00000001;	
}

extern void RCC_EnablePrephiralClock(u8 Bus,u8 Prephiral)
{
	switch(Bus)
	{
		case 0 :SET_BIT(RCC_AHBENR,Prephiral);break;
		
		case 1 :SET_BIT(RCC_APB1ENR ,Prephiral);break;
		
		case 2 :SET_BIT(RCC_APB2ENR ,Prephiral);break;					
	}	
}



extern void RCC_DisablePrephiralClock(u8 Bus,u8 Prephiral)
{
	switch(Bus)
	{
		case 0 :CLR_BIT(RCC_AHBENR,Prephiral);break;
		
		case 1 :CLR_BIT(RCC_APB1ENR ,Prephiral);break;
		
		case 2 :CLR_BIT(RCC_APB2ENR ,Prephiral);break;					
	}	
}