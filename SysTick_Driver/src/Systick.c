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

static systickcbf_t APPcbf;

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
extern void SYSTICK_Start(void)
{

}

/////////////////////////////////////////////////////////////////
extern void SYSTICK_Stop(void)
{

}

/////////////////////////////////////////////////////////////////
extern void SYSTICK_SetTime_us(u32 timeus,u32 AHB_clcHz)
{

}
