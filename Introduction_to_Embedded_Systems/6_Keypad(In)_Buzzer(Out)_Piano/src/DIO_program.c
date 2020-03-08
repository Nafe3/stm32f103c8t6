/*Library Inclusion*/
/*Library Layer*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "DIO_register.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"


/*This is the function that we will use to set mode of pin
Modes:
00: Input
01: Output @ 10 MHz
10: Output @ 2 MHz
11: Output @ 50 MHz

CNF:
Input-> 00: Analog
		01: Floating
		10: Pull Up/Down
		11: Reserved
Output->
*/
void setPinMode(u8 Port, u8 Pin, u8 Mode)
{
	switch (Port)
	{
		/*We need to know the number of pin so that we can know the register
		that we will use (CRL or CRH)*/
		case 'A':
		{
			/*If the pin is less than 7, then we will use CRL*/
			if (Pin<=7)
			{
				/*Here we will shift it by the pin number multiplied by number
				of bits, which is 4
				So our steps will be to reset mode of all pins by (AND) with ~1
				Then make the shift mentioned above*/
				PORTA_CRL &= ~(0b1111<<(Pin*4)); /*After this operations, all the pins are zeros*/
				PORTA_CRL |= (Mode << (Pin*4)); /*Here, we set mode*/
			}
			/*If pin number is over 7, then we will use CRH*/
			else if (Pin<=15)
			{
				/*Here we will shift it by the pin number multiplied by number
				of bits, which is 4
				So our steps will be to reset mode of all pins by (AND) with ~1
				Then make the shift mentioned above*/
				/*NOTE: GPIO Pin8 equals the first pin in the CRH (which is Pin0)*/
				Pin=Pin-8; /*This is to convert for example pin8 to pin0*/
				PORTA_CRH &= ~(0b1111<<(Pin*4)); /*After this operations, all the pins are zeros*/
				PORTA_CRH |= (Mode << (Pin*4)); /*Here, we set mode*/
			}
			/*Don't forget to break the case at the end*/

		}
		break;
		case 'B':
		{
			/*If the pin is less than 7, then we will use CRL*/
			if (Pin<=7)
			{
				/*Here we will shift it by the pin number multiplied by number
				of bits, which is 4
				So our steps will be to reset mode of all pins by (AND) with ~1
				Then make the shift mentioned above*/
				PORTB_CRL &= ~(0b1111<<(Pin*4)); /*After this operations, all the pins are zeros*/
				PORTB_CRL |= (Mode << (Pin*4)); /*Here, we set mode*/
			}
			/*If pin number is over 7, then we will use CRH*/
			else if (Pin<=15)
			{
				/*Here we will shift it by the pin number multiplied by number
				of bits, which is 4
				So our steps will be to reset mode of all pins by (AND) with ~1
				Then make the shift mentioned above*/
				/*NOTE: GPIO Pin8 equals the first pin in the CRH (which is Pin0)*/
				Pin=Pin-8; /*This is to convert for example pin8 to pin0*/
				PORTB_CRH &= ~(0b1111<<(Pin*4)); /*After this operations, all the pins are zeros*/
				PORTB_CRH |= (Mode << (Pin*4)); /*Here, we set mode*/
			}
			/*Don't forget to break the case at the end*/

		}
		break;
		case 'C':
		{
			/*Port C has only 3 GPIO Pins which are:
			Pin 13
			Pin 14
			Pin 15
			*/
			if ((Pin>=13) && (Pin<=15))
			{
				/*Here we will shift it by the pin number multiplied by number
				of bits, which is 4
				So our steps will be to reset mode of all pins by (AND) with ~1
				Then make the shift mentioned above*/
				/*NOTE: GPIO Pin8 equals the first pin in the CRH (which is Pin0)*/
				Pin=Pin-8; /*This is to convert for example pin8 to pin0*/
				PORTC_CRH &= ~(0b1111<<(Pin*4)); /*After this operations, all the pins are zeros*/
				PORTC_CRH |= (Mode << (Pin*4)); /*Here, we set mode*/
			}
			/*Don't forget to break at the end of case*/
		}
		break;
	}
}
/*This function sets the value on the pin whether it is input or output*/
void setPinValue(u8 Port, u8 Pin, u8 Val)
{
	switch (Port)
	{
		case 'A':
		{
			/*If incoming value is zero, we will set this value to
			the regitser. If not, then we will clear the bits on the pin*/
			if (Val==1)
			{
				SET_BIT(PORTA_ODR, Pin);
			}
			else
			{
				CLR_BIT(PORTA_ODR, Pin);
			}
			/*Don't Forget to break at the end*/

		}
		break;
		case 'B':
		{
			/*If incoming value is zero, we will set this value to
			the regitser. If not, then we will clear the bits on the pin*/
			if (Val==1)
			{
				SET_BIT(PORTB_ODR, Pin);
			}
			else
			{
				CLR_BIT(PORTB_ODR, Pin);
			}
			/*Don't Forget to break at the end*/

		}
		break;
		case 'C':
		{
			/*If incoming value is zero, we will set this value to
			the regitser. If not, then we will clear the bits on the pin*/
			if (Val==1)
			{
				SET_BIT(PORTC_ODR, Pin);
			}
			else
			{
				CLR_BIT(PORTC_ODR, Pin);
			}
			/*Don't Forget to break at the end*/

		}
		break;
	}
}

/*This is the function that we will use to know the state of the pin*/
u8 getPinValue(u8 Port, u8 Pin)
{
	/*This is the variable that will store the value of GET_BIT*/
	u8 result=0;
	switch (Port)
	{
		case 'A':
		{
			/*We will store the state in a variable called result*/
			result = GET_BIT(PORTA_IDR, Pin);
			/*Don't Forget to break at the end*/

		}
		break;
		case 'B':
		{
			/*We will store the state in a variable called result*/
			result = GET_BIT(PORTB_IDR, Pin);
			/*Don't Forget to break at the end*/

		}
		break;
		case 'C':
		{
			/*We will store the state in a variable called result*/
			result = GET_BIT(PORTC_IDR, Pin);
			/*Don't Forget to break at the end*/

		}
		break;
	}	
	/*Return the result variable*/
	return result;
}
