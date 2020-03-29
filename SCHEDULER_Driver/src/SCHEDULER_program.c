/*
 * SCHEDULER_program.c
 *
 *  Created on: Mar 10, 2020
 *      Author: Mohamed Nafea
 */

#include "STD_TYPES.h"
#include "SCHEDULER_interface.h"
#include "SCHEDULER_config.h"
#include "SCHEDULER_private.h"


typedef struct{
	task_t* appTask;
	u32		RemainToExec;
	u32 	PeriodTicks;
	u32		FirstTickDelay;
}systask_t;

//static task_t sysTasks[MAX];
static systask_t sysTasks[MAX];
static u8 OSFlag =0;

extern const sysTaskInfo_t sysTaskInfo[];



/*Step 1: */
/*
void sched_CreateTask(task_t* appTask)
{
	if(appTask)
	{
		sysTasks[appTask->Priority].appTask     = appTask;
		sysTasks[appTask->Priority].PeriodTicks = ((appTask->PeriodicTime)/TICK_MS);
	}
}
*/

/*Step 2: */
void sched_init(void)
{
	u8 i;

	//configure timer
	//set callback(scheduler) :: call this function -> SetOSflag
	//start timer
	for(i=0;i<MAX;i++)
	{
		sysTasks[i].appTask      = &sysTaskInfo[i].appTaskinfo;
		sysTasks[i].RemainToExec = sysTaskInfo[i].delayTicks;
		sysTasks[i].PeriodTicks  = sysTaskInfo[i].appTaskinfo->PeriodicTime/TICK_MS;
	}
}
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


