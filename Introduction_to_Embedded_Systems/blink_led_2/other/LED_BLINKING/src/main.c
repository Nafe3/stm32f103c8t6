#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "RCC_interface.h"

void main(void)
{
	/* RCC Init */
	RCC_Init();
	
	/* Enable Clock in Port C */
	RCC_EnablePrephiralClock(2,4);
	
	DIO_SetPinMode('C',13 ,0b0010);
	
	DIO_SetPinVal('C',13,0);
	
	while(1);
}