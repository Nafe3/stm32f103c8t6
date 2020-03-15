/*
 * Systick.h
 *
 *  Created on: Mar 10, 2020
 *      Author: Mohamed Nafea
 */

/*	To set up the SysTick Timer, the recommended programming sequence is as follows:
		1� Disable SysTick by writing 0 to the SYSTICK Control and Status register.
		2� Write new reload value to the SYSTICK Reload Value register.
		3� Write to the SYSTICK Current Value register to clear the current value to 0.
		4� Write to the SYSTICK Control and Status register to start the SysTick timer.
 */


#ifndef SYSTICK_H_
#define SYSTICK_H_

#define CLK_PRE_AHB				0U
#define CLK_PRE_AHB_DIV_8		1U

typedef void(*systickcbf_t)(void);

void SysTick_Handler(void);

extern void SYSTICK_Init		(void)						;
extern void SYSTICK_Start		(u32 Copy_u32Value)			;
extern void SYSTICK_Stop		(void)						;
extern void SYSTICK_SetTime_ms	(u32 timems,u32 AHB_clcHz)	;
extern void SYSTICK_SetTime_us	(u32 timeus,u32 AHB_clcHz)	;
extern void SYSTICK_SetCallback	(systickcbf_t cbf)			;



#endif /* SYSTICK_H_ */
