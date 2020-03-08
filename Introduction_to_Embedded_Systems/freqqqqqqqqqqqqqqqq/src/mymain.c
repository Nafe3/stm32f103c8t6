/*
 * mymain.c
 *
 *  Created on: Feb 9, 2020
 *      Author: moham
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "RCC_interface.h"
#include "DIO_interface.h"
#include "STK_interface.h"

void func(void);

void main(void)
{
	/*HSE is on*/
	u32 x;
	//u8 strt=1;
	RCC_Init();
	RCC_EnablePeripheralClock(2,2); //apb2,port A

	STK_voidInitialize();

	setPinMode('A',0,0b0010);//output pin
	setPinMode('A',1,0b1000);//input pin (increment)
	setPinMode('A',2,0b1000);//input pin (start/stop)
	setPinMode('A',3,0b1000);//input pin (decrement)

	setPinValue('A',1,1);//pull up input pin (increment)
	setPinValue('A',2,1);//pull up input pin (start/stop)
	setPinValue('A',3,1);//pull up input pin (decrement)

	STK_voidSetCallBack(&func);
	x=10000;

	STK_voidStart(x);

	while(1)
	{
		/*if(getPinValue('A',1)==0)
		{
			x+=10;
			STK_voidStart(x);
		}

		if(getPinValue('A',3)==0)
		{
			x-=10;
			STK_voidStart(x);
		}

		if(getPinValue('A',2)==0)
		{
			strt^=1;
			STK_voidStart(x);
		}*/

	}
}

void func(void)
{
	static flag =0;
	if (flag == 0)
	{
		setPinValue('A',0,1);
		flag =1;
	}
	else
	{
		setPinValue('A',0,0);
		flag=0;
	}
}


