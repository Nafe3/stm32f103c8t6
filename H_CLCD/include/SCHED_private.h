#ifndef SCHED_PRIV_H
#define SCHED_PRIV_H

typedef struct{
	task_t* task;
	u32 RemainTickToExec;
	u32 PeriodicTics;
}Task_Info_t;


#endif
