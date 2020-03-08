#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_register.h"
#include "RCC_interface.h"

void main(void)
{
	/* RCC Init */
	RCC_Init();

	/* Enable Clock in Port C */
	RCC_EnablePeripheralClock(1,4);

	DIO_SetPinMode('C',13,0b0011);//output pin on chip led
	DIO_SetPinMode('C',15,0b0011);//buzzer output
	DIO_SetPinMode('C',14,0b1000);//input


	while(1)
	{

		PORTC_ODR=0x0000C000;
/*
		if(DIO_GetPinVal('C',14)==0)
		{
			DIO_SetPinVal('C',13,0);
			DIO_SetPinVal('C',15,1);
		}
		else
		{
			DIO_SetPinVal('C',13,1);
			DIO_SetPinVal('C',15,0);
		}
*/
	}
}
