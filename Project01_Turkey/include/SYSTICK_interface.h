/********************************************************************************/
/* Author  : Bishoy Nabil                                                       */
/* Date    : 4 Feb 2020                                                         */
/* Version : V01                                                                */
/********************************************************************************/

#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H

#include "STD_TYPES.h"
//#include "BIT_MATH.h"

/* Prescaler */
#define AHB_DIVIDED_BY_EIGHT 0
#define AHB                  1

/* InterruptControl */
#define INTERRUPT_DISABLED   0
#define INTERRUPT_ENABLED    1

typedef struct
{
	u32 TimeUS;
	u32 *Cov;
	u8 Prescaler;
	u8 InterruptControl;
	void (*CallBackPtr)(void);
}STK_t;

extern ErrorStatus STK_Init(STK_t *Copy_PtrToSTK_t);
extern ErrorStatus STK_Start(void);
extern ErrorStatus STK_SetTime(STK_t *Copy_PtrToSTK_t);
extern ErrorStatus STK_SetCallBack(STK_t *Copy_PtrToSTK_t);
extern ErrorStatus STK_SetMaxPreload(void);
extern ErrorStatus STK_Stop(void);

#endif
