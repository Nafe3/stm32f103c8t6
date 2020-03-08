#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"
#include "RTOS_interface.h"
#include "RTOS_config.h"
#include "RTOS_private.h"
#include "RTOS_register.h"


u32 Global_u32TickCounter = 0;
Task_t SystemTasks[RTOS_TASKS_NUMBER];
u32 Global_u32PeriodicityOverflow = 1;

static void RTOS_voidScheduler (void)
{
	Global_u32TickCounter++;
	u32 Local_u32Counter;
	for ( Local_u32Counter =0; Local_u32Counter < RTOS_TASKS_NUMBER ; Local_u32Counter++)
	{
		if (Global_u32TickCounter % (SystemTasks[Local_u32Counter].Periodicity) == 0 )
		{
			(SystemTasks[Local_u32Counter].Task_Handler)();
		}
		if (Global_u32TickCounter == Global_u32PeriodicityOverflow ) // Sum of periodicity
		{
			Global_u32TickCounter = 0;
		}
	}
}

void RTOS_voidCreateTasks(u32 Copy_u32Priorty, u32 Copy_u32Priodicity, void(*Copy_pvTaskHandler)(void))
{
	if (!(Copy_u32Priorty >= RTOS_TASKS_NUMBER))
	{
		SystemTasks[Copy_u32Priorty].Task_Handler = Copy_pvTaskHandler;
		SystemTasks[Copy_u32Priorty].Periodicity = Copy_u32Priodicity;

		if (Copy_u32Priodicity!=0)
		{
			Global_u32PeriodicityOverflow *= Copy_u32Priodicity;
		}
	}

}

void RTOS_voidStartOS(void)
{
	STK_voidIntialize();
	STK_voidSetCallBack(RTOS_voidScheduler);
	STK_voidStart(RTOS_PRELOAD_VALUE);// Preload Value
}

void RTOS_voidStopOS(void)
{
	STK_voidStop();
}
