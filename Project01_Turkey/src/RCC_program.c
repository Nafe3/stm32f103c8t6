
#include "STD_TYPES.h"

#include "RCC_interface.h"

#define HSION_MASK                             0x00000001
#define HSIRDY_MASK                            0x00000002
#define HSEON_MASK                             0x00010000
#define HSERDY_MASK                            0x00020000
#define PLLON_MASK                             0x01000000
#define PLLRDY_MASK                            0x02000000
#define SWS_MASK                               0x0000000C
#define HSI_SWS_MASK                           0x00000000
#define HSE_SWS_MASK                           0x00000004
#define PLL_SWS_MASK                           0x00000008
#define PLLXTPRE_PLLSRC_MASK                   0x00030000
#define PLLMUL_MASK                            0x003C0000

#define HSION_CLEAR_MASK                       0xFFFFFFFE
#define HSEON_CLEAR_MASK                       0xFFFEFFFF
#define PLLON_CLEAR_MASK                       0xFEFFFFFF
#define SW_CLEAR_MASK                          0xFFFFFFFC
#define MCO_CLEAR_MASK                         0xF8FFFFFF
#define PLLXTPRE_PLLSRC_PLLMUL_CLEAR_MASK      0xFFC0FFFF

#define RCC        ((volatile RCCReg_t * const)(0x40021000))

typedef struct
{
	u32 CR;
	u32 CFGR;
	u32 CIR;
	u32 APB2RSTR;
	u32 APB1RSTR;
	u32 AHBENR;
	u32 APB2ENR;
	u32 APB1ENR;
	u32 BDCR;
	u32 CSR;
}RCCReg_t;

static ErrorStatus RCC_CheckSystemClock(u32 Copy_u8Clock);

extern ErrorStatus RCC_EnableHSI(void)
{
	u32 Local_u32RCC_CR = RCC->CR;

	/* enable the HSI Clock by setting HSION bit */
	Local_u32RCC_CR |= (HSION_MASK);
	RCC->CR = Local_u32RCC_CR;
	/* check on the HSION bit is set or not */
	while(((HSIRDY_MASK) & (RCC->CR)) ==0);
	return STD_TYPES_ERROR_OK;
}

extern ErrorStatus RCC_DisableHSI(void)
{
	u32 Local_u32RCC_CR = RCC->CR;
	if((RCC_CheckSystemClock(HSI_SYSCLK)))
	{
		return STD_TYPES_ERROR_NOK;
	}
	else
	{
		/* disable HSI by clearing HSION bit*/
		Local_u32RCC_CR &= (HSION_CLEAR_MASK);
		RCC->CR = Local_u32RCC_CR;
		return STD_TYPES_ERROR_OK;
	}
}

extern ErrorStatus RCC_EnableHSE(void)
{
	u32 Local_u32RCC_CR = RCC->CR;
	Local_u32RCC_CR |= (HSEON_MASK);
	RCC->CR = Local_u32RCC_CR;
	while(((HSERDY_MASK) & (RCC->CR)) ==0);
	return STD_TYPES_ERROR_OK;
}

extern ErrorStatus RCC_DisableHSE(void)
{
	u32 Local_u32RCC_CR = RCC->CR;
	if(RCC_CheckSystemClock(HSE_SYSCLK))
	{
		return STD_TYPES_ERROR_NOK;
	}
	else
	{
		Local_u32RCC_CR &= (HSEON_CLEAR_MASK);
		RCC->CR = Local_u32RCC_CR;
		return STD_TYPES_ERROR_OK;
	}
}

extern ErrorStatus RCC_EnablePLL(u8 Copy_u8PLLClockSelected, u8 Copy_u8PLLMUL)
{
	u32 Local_u32RCC_CR = RCC->CR;
	u32 Local_u32RCC_CFGR = RCC->CFGR;
	/* disable PLL if it is not the system clock */
	if(RCC_CheckSystemClock(PLL_SYSCLK))
	{
		return STD_TYPES_ERROR_NOK;
	}
	else
	{
		Local_u32RCC_CR &= (PLLON_CLEAR_MASK);
		RCC->CR = Local_u32RCC_CR;
	}
	
	Local_u32RCC_CFGR &= PLLXTPRE_PLLSRC_PLLMUL_CLEAR_MASK;
	Local_u32RCC_CFGR |= Copy_u8PLLClockSelected;

	Local_u32RCC_CFGR |= (Copy_u8PLLMUL);
	RCC->CFGR = Local_u32RCC_CFGR;

	/* enable PLL */
	Local_u32RCC_CR |= (PLLON_MASK);
	RCC->CR = Local_u32RCC_CR;
	
	/* checking that PLL is ready */
	while(((PLLRDY_MASK & RCC->CR))==0);
	return STD_TYPES_ERROR_OK;
}

extern ErrorStatus RCC_DisablePLL(void)
{
	u32 Local_u32RCC_CR = RCC->CR;
	/* disable PLL */
	if(RCC_CheckSystemClock(PLL_SYSCLK))
	{
		return STD_TYPES_ERROR_NOK;
	}
	else
	{
		Local_u32RCC_CR &= (PLLON_CLEAR_MASK);
		RCC->CR = Local_u32RCC_CR;
		return STD_TYPES_ERROR_OK;
	}
}

extern ErrorStatus RCC_SelectSystemClock(u8 Copy_u8SelectSystemClock)
{
	u32 Local_u8Temp = SW_CLEAR_MASK & RCC->CFGR;
	Local_u8Temp |= (Copy_u8SelectSystemClock);
	RCC->CFGR = Local_u8Temp;
	return RCC_CheckSystemClock(Copy_u8SelectSystemClock<<2);
}

extern ErrorStatus RCC_MCOConfiguration(u8 Copy_u8MCOCLockSelected)
{
	u32 Local_u32RCC_CFGR = RCC->CFGR;
	Local_u32RCC_CFGR &= (MCO_CLEAR_MASK);
	Local_u32RCC_CFGR |= (Copy_u8MCOCLockSelected);
	RCC->CFGR = Local_u32RCC_CFGR;
	return STD_TYPES_ERROR_OK;
}

extern ErrorStatus RCC_EnableAHBPeripheral(u32 Copy_u8PeripheralName)
{
	u32 Local_u32RCC_AHBENR = RCC->AHBENR;
	Local_u32RCC_AHBENR |= (Copy_u8PeripheralName);
	RCC->AHBENR = Local_u32RCC_AHBENR;
	return STD_TYPES_ERROR_OK;
}

extern ErrorStatus RCC_DisableAHBPeripheral(u32 Copy_u8PeripheralName)
{
	u32 Local_u32RCC_AHBENR = RCC->AHBENR;
	Local_u32RCC_AHBENR &= (Copy_u8PeripheralName);
	RCC->AHBENR = Local_u32RCC_AHBENR;
	return STD_TYPES_ERROR_OK;
}

extern ErrorStatus RCC_EnableAPB2Peripheral(u32 Copy_u8PeripheralName)
{
	u32 Local_u32RCC_APB2ENR = RCC->APB2ENR;
	Local_u32RCC_APB2ENR |= (Copy_u8PeripheralName);
	RCC->APB2ENR = Local_u32RCC_APB2ENR;
	return STD_TYPES_ERROR_OK;
}

extern ErrorStatus RCC_DisableAPB2Peripheral(u32 Copy_u8PeripheralName)
{
	u32 Local_u32RCC_APB2RSTR = RCC->APB2RSTR;
	Local_u32RCC_APB2RSTR |= (Copy_u8PeripheralName);
	RCC->APB2RSTR = Local_u32RCC_APB2RSTR;
	return STD_TYPES_ERROR_OK;
}

extern ErrorStatus RCC_EnableAPB1Peripheral(u32 Copy_u8PeripheralName)
{
	u32 Local_u32RCC_APB1ENR = RCC->APB1ENR;
	Local_u32RCC_APB1ENR |= (Copy_u8PeripheralName);
	RCC->APB1ENR = Local_u32RCC_APB1ENR;
	return STD_TYPES_ERROR_OK;
}

extern ErrorStatus RCC_DisableAPB1Peripheral(u32 Copy_u8PeripheralName)
{
	u32 Local_u32RCC_APB1RSTR = RCC->APB1RSTR;
	Local_u32RCC_APB1RSTR |= (Copy_u8PeripheralName);
	RCC->APB1RSTR = Local_u32RCC_APB1RSTR;
	return STD_TYPES_ERROR_OK;
}

extern ErrorStatus RCC_GetSysFreq(u32 *Copy_SysFreq)
{
	u32 Local_u32SysFreq = 0;
	switch(RCC->CFGR & SWS_MASK)
	{
		case HSI_SWS_MASK:
		{
			*Copy_SysFreq = 8000000;
		}
		break;
		case HSE_SWS_MASK:
		{
			*Copy_SysFreq = 8000000;
		}
		break;
		case PLL_SWS_MASK:
		{
			switch(RCC->CFGR & PLLXTPRE_PLLSRC_MASK)
			{
				case HSI_DIVIDED_BY_TWO_PLL:
				{
					Local_u32SysFreq = 4000000;
				}
				break;
				case HSE_PLL:
				{
					Local_u32SysFreq = 8000000;
				}
				break;
				case HSE_DIVIDED_BY_TWO_PLL:
				{
					Local_u32SysFreq = 4000000;
				}
				break;
			}

			switch(RCC->CFGR & PLLMUL_MASK)
			{
				case PLLx2:
				{
					Local_u32SysFreq *= 2;
				}
				break;
				case PLLx3:
				{
					Local_u32SysFreq *= 3;
				}
				break;
				case PLLx4:
				{
					Local_u32SysFreq *= 4;
				}
				break;
				case PLLx5:
				{
					Local_u32SysFreq *= 5;
				}
				break;
				case PLLx6:
				{
					Local_u32SysFreq *= 6;
				}
				break;
				case PLLx7:
				{
					Local_u32SysFreq *= 7;
				}
				break;
				case PLLx8:
				{
					Local_u32SysFreq *= 8;
				}
				break;
				case PLLx9:
				{
					Local_u32SysFreq *= 9;
				}
				break;
				case PLLx10:
				{
					Local_u32SysFreq *= 10;
				}
				break;
				case PLLx11:
				{
					Local_u32SysFreq *= 11;
				}
				break;
				case PLLx12:
				{
					Local_u32SysFreq *= 12;
				}
				break;
				case PLLx13:
				{
					Local_u32SysFreq *= 13;
				}
				break;
				case PLLx14:
				{
					Local_u32SysFreq *= 14;
				}
				break;
				case PLLx15:
				{
					Local_u32SysFreq *= 15;
				}
				break;
				case PLLx16:
				{
					Local_u32SysFreq *= 16;
				}
				break;
			}
			*Copy_SysFreq = Local_u32SysFreq;
		}
		break;
	}
	return STD_TYPES_ERROR_OK;
}

static ErrorStatus RCC_CheckSystemClock(u32 Copy_u8Clock)
{
	if((Copy_u8Clock << 2)==(RCC->CFGR & SWS_MASK))
	{
		return STD_TYPES_ERROR_OK;
	}
	return STD_TYPES_ERROR_NOK;
}
