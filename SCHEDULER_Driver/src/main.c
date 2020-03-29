#include "SCHEDULER_config.h"
int main(void)
{
	/*MCAL Drivers init*/

	/*HAL Drivers init*/


	/*Start Scheduler*/
	//static const task_t hamada={hamada.Runnable=Apprun,hamada.PeriodicTime=20};
	 sched_init();
	 sched_start();
}

