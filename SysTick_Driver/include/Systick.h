/*
 * Systick.h
 *
 *  Created on: Mar 10, 2020
 *      Author: moham
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_


#define CLK_PRE_AHB				0U
#define CLK_PRE_AHB_DIV_8		1U


typedef void(*systickcbf_t)(void);

void SysTick_Handler(void);

extern void SYSTICK_Start(void);
extern void SYSTICK_Stop(void);
extern void SYSTICK_SetTime_us(u32 timeus,u32 AHB_clcHz);
extern void SYSTICK_SetCallback(systickcbf_t cbf);



#endif /* SYSTICK_H_ */
