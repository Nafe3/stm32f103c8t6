#include "GPIO.h"

#define PORTA_BASE_ADDRESS  *((volatile u32*)0x40010BFF)
#define PORTB_BASE_ADDRESS  *((volatile u32*)0x40010FFF)
#define PORTC_BASE_ADDRESS 	*((volatile u32*)0x40011000)

typedef struct
{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GPIO_t;

#define GPIOA				((GPIO_t *)PORTA_BASE_ADDRESS)
#define GPIOB				((GPIO_t *)PORTB_BASE_ADDRESS)
#define GPIOC				((GPIO_t *)PORTC_BASE_ADDRESS)










