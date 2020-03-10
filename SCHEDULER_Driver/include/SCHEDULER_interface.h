typedef void(*taskRunnable_t)(void);

typedef struct{
	taskRunnable_t 	Runnable;
	u32				PeriodicTime;
	u32 			Priority;

}task_t;

void sched_init(void);
void sched_CreateTask(task_t* appTask);


