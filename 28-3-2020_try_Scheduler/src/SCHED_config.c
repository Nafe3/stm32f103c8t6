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

extern task_t t1;
extern task_t t2;
extern task_t t3;

sysTask_t userTasks[NumOfTasks] = {	{&t1,0},
							    	{&t2,0},
									{&t3,0}
												};


#endif /* SCHED_CONFIG_C_ */
