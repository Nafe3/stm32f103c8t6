#include"STD_TYPES.h"
#include"OS.h"
#include"NVIC_interface.h"
#include"STK_interface.h"


void main(void)
{
	/*Initialization*/
	RCC_init();
	RCC_Enable();
	DIO_init();

	/*Activate tasks*/
	RTOS_createtask();

	/*START OS*/
	RTOS_startOS();

	while(1);
}
