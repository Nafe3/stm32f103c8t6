/*
 * SCHED_interface.h
 *
 *  Created on: 13 Mar 2020
 *      Author: mirna
 */

#ifndef SCHED_INTERFACE_H_
#define SCHED_INTERFACE_H_

typedef void (*taskRunnable_t)(void);

typedef struct{
	taskRunnable_t runnable;
	u32 periodicTime;
}task_t;

void SCHED_Init(void);
void SCHED_Start(void);

#endif /* SCHED_INTERFACE_H_ */
