#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "RCC_interface.h"

void main(void)
{
	/* RCC Init */
	RCC_Init();

	/* Enable Clock in Port C */
	RCC_EnablePeripheralClock(2,2);
	//RCC_EnablePeripheralClock(2,0);

	DIO_SetPinMode('A',8,0b1011);



	while(1)
	{

	}
}
