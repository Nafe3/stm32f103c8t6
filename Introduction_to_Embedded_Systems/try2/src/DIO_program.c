// libs
#include "STD_TYPES.h"
#include "BIT_MAN.h"
// own
#include "DIO_interface.h"
#include "DIO_registers.h"
#include "DIO_private.h"
#include "DIO_config.h"

void DIO_setPinMode(u8 port, u8 pin, u8 mode)
{
   switch (port)
   {
      case 'A':
         PORTA_CR &= ~((u64)0b1111 << (pin * 4));
         PORTA_CR |= (u64)mode << (pin * 4);
      break;

      case 'B':
         PORTB_CR &= ~((u64)0b1111 << (pin * 4));
         PORTB_CR |= (u64)mode << (pin * 4);
      break;

      case 'C':
    	 //pin = pin - 8;
         PORTC_CR &= ~((u64)0b1111 << (pin * 4));
         PORTC_CR |= (u64)mode << (pin * 4);
      break;
   }
}

void DIO_setPinVal(u8 port, u8 pin, u8 val)
{
   switch(port)
   {
      case 'A':
         if(val == 1)
         {
        	 PORTA_ODR = BIT_SET(PORTA_ODR, pin);
         }
         else
         {
        	 PORTA_ODR = BIT_CLEAR(PORTA_ODR, pin);
         }
      break;
      
      case 'B':
         if(val == 1)
         {
        	 PORTB_ODR = BIT_SET(PORTB_ODR, pin);
         }
         else
         {
        	 PORTB_ODR = BIT_CLEAR(PORTB_ODR, pin);
         }
      break;
      
      case 'C':
         if(val == 1)
         {
        	 PORTC_ODR = BIT_SET(PORTC_ODR, pin);
         }
         else
         {
        	 PORTC_ODR = BIT_CLEAR(PORTC_ODR, pin);
         }
      break;
   }
}

u8 DIO_getPinVal(u8 port, u8 pin)
{
   switch (port)
   {
      case 'A':
         return BIT_GET(PORTA_IDR, pin);
      break;
      
      case 'B':
         return BIT_GET(PORTB_IDR, pin);
      break;
      
      case 'C':
         return BIT_GET(PORTC_IDR, pin);
      break;

      default:
    	  return 0;
	  break;
   }
}
