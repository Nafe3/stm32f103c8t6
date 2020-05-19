#ifndef SCHEDULAR_H
#define SCHEDULAR_H

#include "STD_TYPES.h"
//#include "BIT_MATH.h"

typedef void (*TaskRunnable_t)(void);


/* Any user wants to create a task just create an object from this struct type and fill its parameters,
 * nothing more */

typedef struct
{
	TaskRunnable_t Runnable;
	u32            PeriodicTimeMS;
}TaskInterface_t;

/* IMPORTANT NOTE: it is not allowed to any user to use this functions except MAIN function */

/* Description   : sets SYSTICK parameters to interrupt enabled, AHB/8.
 *                 sets SYSTICK time.
 *                 calculate Period Ticks and Remain to execute value for each task.
 * Input         : void
 * Output        : ErrorStatus */
extern ErrorStatus SCHEDULAR_Init(void);

/* Description   : starts SYSTICK timer and stuck inside Operating System While Loop.
 * Input         : void
 * Output        : ErrorStatus */
extern ErrorStatus SCHEDULAR_Start(void);

#endif
