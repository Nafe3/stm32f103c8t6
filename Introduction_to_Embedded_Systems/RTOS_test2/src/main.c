#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "RCC_interface.h"
#include "STK_interface.h"

void Task_1 (void)
{
	DIO_setPinMode('C',13,0b0010);

	DIO_TogglePinValue('C', 13);

}

void Task_2 (void)
{
	DIO_setPinMode('C',14,0b0010);


	DIO_TogglePinValue('C', 14);

}

void main (void)
{
	RCC_Init();
	RCC_EnablePeripheralClock(2,4);

	RTOS_voidCreateTasks(0,1,Task_1);
	RTOS_voidCreateTasks(1,3,Task_2);
	RTOS_voidStartOS();

	while (1)
	{

	}
}
