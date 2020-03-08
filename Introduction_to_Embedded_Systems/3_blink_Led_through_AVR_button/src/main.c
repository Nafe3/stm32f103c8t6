#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "RCC_interface.h"

void main(void)
{
	/* RCC Init */
	RCC_Init();

	/* Enable Clock in Port C */
	RCC_EnablePeripheralClock(1,4);

	DIO_SetPinMode('C',13,0b0010);//output pin on chip led
	DIO_SetPinMode('C',14,0b1000);

	while(1)
	{

		if(DIO_GetPinVal('C',14))
		{
			DIO_SetPinVal('C',13,0);
		}
		else
		{
			DIO_SetPinVal('C',13,1);
		}

	}
}
