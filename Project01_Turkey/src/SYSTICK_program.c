/********************************************************************************/
/* Author  : Bishoy Nabil                                                       */
/* Date    : 4 Feb 2020                                                         */
/* Version : V01                                                                */
/********************************************************************************/

#include "STD_TYPES.h"
//#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "SYSTICK_interface.h"

#define CLKSOURSE_MASK                0x00000004
#define TICKINT_MASK                  0x00000002
#define ENABLE_MASK                   0x00000001

#define CLKSOURSE_CLEAR_MASK          0xFFFFFFFB
#define TICKINT_CLEAR_MASK            0xFFFFFFFD
#define ENABLE_CLEAR_MASK             0xFFFFFFFE

#define STK                           ((volatile STKReg_t * const)(0xE000E010))

typedef struct
{
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
}STKReg_t;

void (*Systick_CallBack) (void);

/* this function initialize the Systick Interrupt Control and the Systick Prescalar */
extern ErrorStatus STK_Init(STK_t *Copy_PtrToSTK_t)
{
	ErrorStatus Local_ErrorStatus = STD_TYPES_ERROR_OK;
	volatile STKReg_t *Local_Ptr = STK;
	u32 Local_u32CTRL = Local_Ptr->CTRL;
	if(Copy_PtrToSTK_t->Prescaler == AHB_DIVIDED_BY_EIGHT)
	{
		Local_u32CTRL &= CLKSOURSE_CLEAR_MASK;
	}
	else if(Copy_PtrToSTK_t->Prescaler == AHB)
	{
		Local_u32CTRL |= CLKSOURSE_MASK;
	}
	else
	{
		Local_ErrorStatus = STD_TYPES_ERROR_NOK;
	}

	if(Copy_PtrToSTK_t->InterruptControl == INTERRUPT_DISABLED)
	{
		Local_u32CTRL &= TICKINT_CLEAR_MASK;

	}
	else if(Copy_PtrToSTK_t->InterruptControl == INTERRUPT_ENABLED)
	{
		Local_u32CTRL |= TICKINT_MASK;
	}
	else
	{
		Local_ErrorStatus = STD_TYPES_ERROR_NOK;
	}
	Local_Ptr->CTRL = Local_u32CTRL;
	return Local_ErrorStatus;
}

/* this function sets the timer to a specific time */
extern ErrorStatus STK_SetTime(STK_t *Copy_PtrToSTK_t)
{
	f64 Local_f64Cov = 0;
	u32 Local_u32SysFreq = 0;
	u32 Local_u32Preload = 0;
	volatile u32 Local_u32Prescaler = 0;
	Local_u32Prescaler = ((STK->CTRL >> 2) & 0x00000001);
	if(Local_u32Prescaler == AHB_DIVIDED_BY_EIGHT)
	{
		Local_u32Prescaler = 8;
	}
	else if(Local_u32Prescaler == AHB)
	{
		Local_u32Prescaler = 1;
	}
	RCC_GetSysFreq(&Local_u32SysFreq);
	Local_f64Cov= ( (f64)(Copy_PtrToSTK_t->TimeUS) * (f64)(Local_u32SysFreq) ) / ( ((f64)16777216) * ((f64)Local_u32Prescaler) * ((f64)1000000));
	Local_u32Preload = ((f64)Local_f64Cov - (u32)Local_f64Cov) * (f64)16777216;
	*(Copy_PtrToSTK_t->Cov) = (u32)(Local_f64Cov) + 1;
	/* Load Value into Load Register */
	STK->LOAD = Local_u32Preload;
	return STD_TYPES_ERROR_OK;
}

/* this function starts the timer */
extern ErrorStatus STK_Start(void)
{
	u32 Local_u32CTRL = STK->CTRL;
	/* Clear Value Register */
	STK->VAL = 0;
	Local_u32CTRL &= ENABLE_CLEAR_MASK;
	/* Start System Timer */
	Local_u32CTRL |= ENABLE_MASK;
	STK->CTRL = Local_u32CTRL;
	return STD_TYPES_ERROR_OK;
}

extern ErrorStatus STK_SetCallBack(STK_t *Copy_PtrToSTK_t)
{
	Systick_CallBack = *(Copy_PtrToSTK_t->CallBackPtr);
	return STD_TYPES_ERROR_OK;
}

extern ErrorStatus STK_SetMaxPreload(void)
{
	u8 Local_ErrorStatus = STD_TYPES_ERROR_OK;
	STK->LOAD = 0x00FFFFFF;
	return Local_ErrorStatus;
}

extern ErrorStatus STK_Stop(void)
{
	u32 Local_u32CTRL = STK->CTRL;
	Local_u32CTRL &= ENABLE_CLEAR_MASK;
	return STD_TYPES_ERROR_OK;
}

void SysTick_Handler(void)
{
	Systick_CallBack();
}
