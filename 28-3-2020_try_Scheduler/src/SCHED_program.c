/*
 * SCHED_program.c
 *
 *  Created on: 13 Mar 2020
 *      Author: mirna
 */
#include "STD_TYPES.h"
#include "SCHED_interface.h"
#include "SCHED_private.h"
#include "SCHED_config.h"
#include "Systick.h"


Task_Info_t sysTasks[NumOfTasks];//array of system tasks of type(Task_Info_t)

static u8 osFlag;//used in SCHED_Start

extern sysTask_t userTasks[];      //this is the array of user's tasks that exists in config.c
static void scheduler(void);//prototype
void SCHED_SetOsFlag(void);//prototype


void SCHED_Init(void)
{
	u8 i;
	/*Systick init*/
	SYSTICK_Init();
	
	/*set the TickMS parameter located in (SCHED_config.h)
	  in a systick function,*/
	
	/*make the systick ISR(IRQ) sets the OS flag
	  by assigning (SCHED_SetOsFlag) function to
	  (SYSTICK_SetCallback(func)) function in systick driver*/
	SYSTICK_SetCallback(SCHED_SetOsFlag);
	
	for(i = 0; i<NumOfTasks; i++)
	{
		sysTasks[i].task             = userTasks[i].appTask;	//provided by user in app
		sysTasks[i].RemainTickToExec = userTasks[i].firstDelay;	//provided by user in config.c
		sysTasks[i].PeriodicTics     = userTasks[i].appTask->periodicTime;///TickMS;//provided by user in app
	}
}
void SCHED_Start(void)
{
	//start systick timer
	SYSTICK_Start(500000);//1/4 second
	while(1)
	{
		if(osFlag)
		{
			osFlag = 0;
			scheduler();
		}
	}
}

static void scheduler(void)
{
	u8 i;
	for(i=0;i<NumOfTasks;i++)
	{
		if(sysTasks[i].RemainTickToExec==0)
		{
			sysTasks[i].task->runnable();
			sysTasks[i].RemainTickToExec = sysTasks[i].PeriodicTics;
		}
		sysTasks[i].RemainTickToExec--;
	}
}



void SCHED_SetOsFlag(void)
{
	osFlag = 1;
}

