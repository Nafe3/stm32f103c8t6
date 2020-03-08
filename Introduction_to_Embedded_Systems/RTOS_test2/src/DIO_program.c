#include "BIT_MATH.h"
#include "DIO_interface.h"

#include "DIO_register.h"
#include "RCC_register.h"
#include "RCC_interface.h"
#include "STD_TYPES.h"

extern void DIO_setPinMode(u8 Port, u8 Pin, u8 Mode)
{
	switch(Port)
	{
		case 'A':
			if(Pin <=7)
			{
				PORTA_CRL &= ~(0b1111 << (Pin*4));  //clearing the bits before re-writing on them
				PORTA_CRL |= (Mode << (Pin*4)); 	//setting the mode	
			}
			else if(Pin <=15)
			{
				Pin -= 8; //shifting back to the start
				PORTA_CRH &= ~(0b1111 << (Pin*4));  //clearing the bits before re-writing on them
				PORTA_CRH |= (Mode << (Pin*4));		//setting the mode	
			}
			break;
		case 'B':
			if(Pin <=7)
			{
				PORTB_CRL &= ~(0b1111 << (Pin*4));  //clearing the bits before re-writing on them
				PORTB_CRL |= (Mode << (Pin*4)); 	//setting the mode	
			}
			else if(Pin <=15)
			{
				Pin -= 8; //shifting back to the start
				PORTB_CRH &= ~(0b1111 << (Pin*4));  //clearing the bits before re-writing on them
				PORTB_CRH |= (Mode << (Pin*4));		//setting the mode
			}
			break;
		
		case 'C':
			if((Pin >=13) && (Pin <=15))
			{
				Pin -= 8; //shifting back to the start
				PORTC_CRH &= ~(0b1111 << (Pin*4));  //clearing the bits before re-writing on them
				PORTC_CRH |= (Mode << (Pin*4));		//setting the mode
			}
			break;

	}
	
	
}
extern void DIO_setPinValue(u8 Port, u8 Pin, u8 Value)
{
	switch(Port)
	{
		case 'A':
			if(Value==1)
				SET_BIT(PORTA_ODR, Pin);
			else
				CLR_BIT(PORTA_ODR, Pin);
			break;
		case 'B':
			if(Value==1)
				SET_BIT(PORTB_ODR, Pin);
			else
				CLR_BIT(PORTB_ODR, Pin);
			break;
		
		case 'C':
			if(Value==1)
				SET_BIT(PORTC_ODR, Pin);
			else
				CLR_BIT(PORTC_ODR, Pin);
			break;
	}
}

extern void DIO_TogglePinValue(u8 Port, u8 Pin)
{
	switch(Port)
	{
		case 'A':

			TOGGLE_BIT(PORTA_ODR, Pin);

			break;
		case 'B':

			TOGGLE_BIT(PORTB_ODR, Pin);

			break;

		case 'C':

			TOGGLE_BIT(PORTC_ODR, Pin);

			break;
	}
}
extern u8 DIO_getPinValue(u8 Port, u8 Pin)
{
	u8 Result;
	switch(Port)
	{
		case 'A':
			Result = GET_BIT(PORTA_IDR, Pin);
			break;
		case 'B':
			Result = GET_BIT(PORTB_IDR, Pin);
			break;
		case 'C':
			Result = GET_BIT(PORTC_IDR, Pin);
			break;
		default:
			Result = 255;
			break;
	}
	return Result;
}
