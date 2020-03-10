/*
 * SCHEDULER_program.c
 *
 *  Created on: Mar 10, 2020
 *      Author: moham
 */

#include "STD_TYPES.h"
#include "SCHEDULER_interface.h"
#include "SCHEDULER_config.h"
#include "SCHEDULER_private.h"


//static task_t sysTasks[MAX];
static systask_t sysTasks[MAX];
static u8 OSFlag =0;
///////////////////////////////////////////////////////////
static void Scheduler(void)
{
	//static u32 counter=0;
	u32 i=-0;
	for(i=0;i<MAX;i++)
	{
		//if(counter%((sysTasks[i]->PeriodicTime)/TICK_MS)==0)
		if(sysTasks[i].RemainToExec == 0)
		{
			sysTasks[i].appTask->Runnable();
			//sysTasks[i].RemainToExec = sysTasks[i].appTask->PeriodicTime/TICK_MS;
			sysTasks[i].RemainToExec = sysTasks[i].PeriodTicks;
		}


		//counter++;
		sysTasks[i].RemainToExec--;
	}

}

//////////////////////////////////////////////////////////
void sched_init(void)
{
	//configure timer
	//set callback(scheduler) :: call this function -> SetOSflag
	//start timer
}
/////////////////////////////////////////////////////////
void setOSFlag(void)
{
	OSFlag = 1;
}
/////////////////////////////////////////////////////////
void Sched_Start(void)
{
	//start systick timer
	while(1)
	{
		if(OSFlag)
		{
			OSFlag=0;
			Scheduler();
		}
	}
}
/////////////////////////////////////////////////////////
void sched_CreateTask(task_t* appTask)
{
	if(appTask)
	{
		sysTasks[appTask->Priority].appTask     = appTask;
		sysTasks[appTask->Priority].PeriodTicks = ((appTask->PeriodicTime)/TICK_MS);
	}
}


