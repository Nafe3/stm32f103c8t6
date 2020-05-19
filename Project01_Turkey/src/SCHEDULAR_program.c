/*
 * SHEDULAR.c
 *
 *  Created on: Mar 27, 2020
 *      Author: Lenovo
 */


#include "STD_TYPES.h"
#include "SCHEDULAR_interface.h"
#include "SCHEDULER_config.h"
#include "SYSTICK_interface.h"

typedef struct
{
	const TaskInterface_t *const AppTask;
	      u32                    FirstDelayTicks;
}TaskInfo_t;

typedef struct
{
	TaskInfo_t    *TaskInfo;
	u32            RemainToExecute;
	u32            PeriodTicks;
	u8             State;
}SysTask_t;

extern TaskInfo_t TasksInfo[];
static SysTask_t SysTasks[NUM_OF_TASKS];
static u8 OS_Flag = 0;

static ErrorStatus SCHEDULAR_Schedular(void);
static void SCHEDULAR_SetOSFlag(void);

ErrorStatus SCHEDULAR_Init(void)
{
	u32 x;
	ErrorStatus Local_u8ErrorStatus = STD_TYPES_ERROR_OK;
	u32         Local_u32ForLoopCounter = 0;

	/* initialize the SysTick Timer */
	STK_t Local_STKStruct;
	Local_STKStruct.InterruptControl = INTERRUPT_ENABLED;
	Local_STKStruct.Prescaler = AHB_DIVIDED_BY_EIGHT;
	Local_STKStruct.CallBackPtr = &SCHEDULAR_SetOSFlag;
	Local_STKStruct.TimeUS = TICKTIME_US;
	Local_STKStruct.Cov = &x;

	STK_Init(&Local_STKStruct);
	STK_SetCallBack(&Local_STKStruct);
	STK_SetTime(&Local_STKStruct);

	/* initialize the SysTasks Array and the members of each element */
	for(Local_u32ForLoopCounter = 0;Local_u32ForLoopCounter < NUM_OF_TASKS;Local_u32ForLoopCounter++)
	{
		SysTasks[Local_u32ForLoopCounter].TaskInfo = &TasksInfo[Local_u32ForLoopCounter];
		SysTasks[Local_u32ForLoopCounter].RemainToExecute = SysTasks[Local_u32ForLoopCounter].TaskInfo->FirstDelayTicks;
		SysTasks[Local_u32ForLoopCounter].PeriodTicks = SysTasks[Local_u32ForLoopCounter].TaskInfo->AppTask->PeriodicTimeMS / TICKTIME_MS;
	}

	return Local_u8ErrorStatus;
}

/* this function starts the OS timer */
extern ErrorStatus SCHEDULAR_Start(void)
{
	//static u32 y = 0;
	ErrorStatus Local_u8ErrorStatus = STD_TYPES_ERROR_OK;
	STK_Start();
	while(1)
	{
		if(OS_Flag == 1)
		{
			//y++;
			OS_Flag = 0;
			SCHEDULAR_Schedular();
		}
	}
	return Local_u8ErrorStatus;
}

static ErrorStatus SCHEDULAR_Schedular(void)
{
	ErrorStatus Local_u8ErrorStatus = STD_TYPES_ERROR_OK;
	u8 Local_u8ForLoopCounter = 0;
	//static u32 Local_u32Counter = 0;
	for(Local_u8ForLoopCounter=0;Local_u8ForLoopCounter < NUM_OF_TASKS;Local_u8ForLoopCounter++)
	{
		if(SysTasks[Local_u8ForLoopCounter].RemainToExecute == 0)
		{
			SysTasks[Local_u8ForLoopCounter].RemainToExecute = SysTasks[Local_u8ForLoopCounter].PeriodTicks;
			(SysTasks[Local_u8ForLoopCounter].TaskInfo->AppTask->Runnable)();
		}
		SysTasks[Local_u8ForLoopCounter].RemainToExecute --;
	}
	//Local_u32Counter ++;
	return Local_u8ErrorStatus;
}

/* function that will be executed when SystemTick timer fires an interrupt */
static void SCHEDULAR_SetOSFlag(void)
{
	OS_Flag = 1;
}
