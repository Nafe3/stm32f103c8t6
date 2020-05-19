/*
 * SCHED_config.h
 *
 *  Created on: 13 Mar 2020
 *      Author: mirna
 */

#ifndef SCHED_CONFIG_C_
#define SCHED_CONFIG_C_

#include "STD_TYPES.h"
#include "SCHED_interface.h"
#include "SCHED_config.h"

extern task_t switch_task;
extern task_t app_task;


sysTask_t userTasks[NumOfTasks] = {	{&switch_task,0},
							    	{&app_task,0}
												};


#endif /* SCHED_CONFIG_C_ */
