/*
 * SCHEDULER_config.c
 *
 *  Created on: Mar 10, 2020
 *      Author: Mohamed Nafea
 */

/*To easily configure tasks*/
#include "STD_TYPES.h"
#include "SCHEDULER_interface.h"
#include "SCHEDULER_config.h"
#include "SCHEDULER_private.h"


extern task_t app1;
extern task_t app2;
extern task_t LCDTask;
extern task_t SwitchTask;

const sysTaskInfo_t sysTaskInfo[]={ {&app1			,0},
									{&app2			,0},
									{&LCDTask		,0},
									{&SwitchTask	,0}
							   	  };
