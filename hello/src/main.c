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

	DIO_SetPinMode('C',13,0b0010);


	u32 i;
	while(1)
	{
		DIO_SetPinVal('C',13,0);
	//	for(i=0;i<100000;i++);
		DIO_SetPinVal('C',13,1);
	//	for(i=0;i<100000;i++);
	}
}
