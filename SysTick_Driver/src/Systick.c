/*
 * Systick.c
 *
 *  Created on: Mar 10, 2020
 *      Author: moham
 */
#include "STD_TYPES.h"
#include "Systick.h"
#include "Systick_config.h"
#include "..\system\include\cortexm\ExceptionHandlers.h"

#define STK_BASE_ADDRESS		0XE000E010
#define STK_CTRL			    *((volatile u32*)(STK_BASE_ADDRESS+0x00))
#define STK_LOAD                *((volatile u32*)(STK_BASE_ADDRESS+0x04))
#define STK_VAL                 *((volatile u32*)(STK_BASE_ADDRESS+0x08))
#define STK_CALIB               *((volatile u32*)(STK_BASE_ADDRESS+0x0C))



static systickcbf_t APPcbf;			//global variable(pointer to function to save the user's ISR function address

/*this is the second step after setting the callback function*/
void SysTick_Handler(void)
{
	/*checking if the user has set the callback function or not*/
	if(APPcbf)
	{
		APPcbf();
	}
}

/////////////////////////////////////////////////////////////////
/*saving the the pointer to the user's function in a global variable*/
/*This is step 1*/
extern void SYSTICK_SetCallback(systickcbf_t cbf)
{
	if(cbf)
	{
		APPcbf=cbf;
	}
}

/////////////////////////////////////////////////////////////////
extern void SYSTICK_Init		(void)
{
	/* enable systick interrupt - clock =AHB/8*/
	/*stop systick*/
	STK_CTRL=0x00000002;
}

/////////////////////////////////////////////////////////////////
extern void SYSTICK_Start(u32 Copy_u32Value)
{
	STK_CTRL &=~(0x1);
	/*load the value into load reg*/
	STK_LOAD = Copy_u32Value;
	/*clear value register*/
	STK_VAL=0;
	/*start system timer*/
	STK_CTRL = 0x1;
}

/////////////////////////////////////////////////////////////////
extern void SYSTICK_Stop(void)
{

}

/////////////////////////////////////////////////////////////////
extern void SYSTICK_SetTime_us(u32 timeus,u32 AHB_clcHz)
{

}
