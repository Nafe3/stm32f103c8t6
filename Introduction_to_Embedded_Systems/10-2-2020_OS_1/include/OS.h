//SCHEDULER IMPLEMENTATION
#include"STD_TYPES.h"
#define num_of_tasks 2

typedef struct
{
	void (*taskHandler)(void);
	u32 periodicity;
}Task;

Task SysTasks[num_of_tasks];


//scheduler function comes every tume equals to TICK TIME
/*
Timer -> t(desired time)=t(tick time) //our main constraint is tick time, it cannot be broken or it will affect the system badly
Action-> Scheduler();
*/

void schedule(void)
{
static u32 Tick_Counter=0;
Tick_Counter++;

	for(u8 i=0;i<num_of_tasks;i++)
	{
		/*check Task Periodicity against current tick*/
		if(Tick_Counter % (SysTasks[i].periodicity)==0)
		{
			(SysTasks[i].taskHandler)();
		}
	}
	if(Tick_Counter== 0)//??)
	{
		Tick_Counter=0;
	}

}


/*
RTOS.c w n7ot fih el function ely foo2 di
w hane3mel function esmaha ->  */



