/*
 * SHEDULAR_config.c
 *
 *  Created on: Mar 28, 2020
 *      Author: Bishoy Nabil
 */



#include "SCHEDULAR_interface.h"
#include "SCHEDULER_config.h"


typedef struct
{
	const TaskInterface_t *const AppTask;
	      u32                    FirstDelayTicks;
}TaskInfo_t;

/* Structures of type TaskInterface_t created by users */

extern TaskInterface_t switch_task;
extern TaskInterface_t lcd_task;
extern TaskInterface_t app_task;
//extern TaskInterface_t uart_send_task;
//extern TaskInterface_t uart_recieve_task;


const TaskInfo_t TasksInfo[NUM_OF_TASKS] = {

		{&switch_task		,0},
		{&lcd_task   		,0},
		{&app_task    		,0},
		{&uart_send_task   	,0},
		{&uart_recieve_task	,0}

};






