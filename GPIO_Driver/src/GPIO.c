#include "GPIO.h"

//Standard error
#define OK 	0U
#define NOK	1U
typedef struct{
	u8 error_status;
}std_err;

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

//////////////////////////////////////////////////////////
std_err GPIO_Init     (GPIO_Pin_t* ptrGP){
	std_err err;
	err.error_status= OK;


	if     ((ptrGP->pin >= 0) && (ptrGP->pin <= 7))//CRL
	{
		ptrGP->
	}
	else if((ptrGP->pin >  7) && (ptrGP->pin <=15))//CRH
	{

	}
	else
	{

	}

	return err;
}

/////////////////////////////////////////////////////////
std_err GPIO_Write    (GPIO_Pin_t*,u8  state){
	std_err err;
	err.error_status= OK;

	return err;
}

/////////////////////////////////////////////////////////////
std_err GPIO_Read     (GPIO_Pin_t*,u8* returnValue){
	std_err err;
	err.error_status= OK;

	return err;
}

/////////////////////////////////////////////////////////////
std_err GPIO_FastSet  (GPIO_Pin_t*){
std_err err;
err.error_status= OK;

return err;
}

//////////////////////////////////////////////////////////////
std_err GPIO_FastReset(GPIO_Pin_t*){
	std_err err;
	err.error_status= OK;

	return err;
}

/////////////////////////////////////////////////////////////
std_err GPIO_Lock     (GPIO_Pin_t*){
	std_err err;
	err.error_status= OK;

	return err;
}
