#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "RCC_interface.h"
#include "DIO_register.h"

//u8 startCom();//function to initialize the communication
void recvByte();//function that recieves the byte


void main(void)
{
	/* RCC Init */
	RCC_Init();

	/* Enable Clock in Port C */
	RCC_EnablePeripheralClock(2,2);
	RCC_EnablePeripheralClock(2,4);


	setPinMode('A',0 ,0b0011);//led 8
	setPinMode('A',1 ,0b0011);//led 7
	setPinMode('A',2 ,0b0011);//led 6
	setPinMode('A',3 ,0b0011);//led 5
	setPinMode('A',4 ,0b0011);//led 4
	setPinMode('A',5 ,0b0011);//led 3
	setPinMode('A',6 ,0b0011);//led 2
	setPinMode('A',7 ,0b0011);//led 1

	setPinMode('C',13,0b0011);
	setPinMode('C',14,0b1000);//input pin (signal coming from avr)
	//PORTC_ODR=0x00004000;

	setPinValue('A',0 ,0);
	setPinValue('A',1 ,0);
	setPinValue('A',2 ,0);
	setPinValue('A',3 ,0);
	setPinValue('A',4 ,0);
	setPinValue('A',5 ,0);
	setPinValue('A',6 ,0);
	setPinValue('A',7 ,0);

	while(1)
	{
		if(getPinValue('C',14))setPinValue('C',13,0);
		else
			setPinValue('C',13,1);
		//setPinValue('A',0,getPinValue('C',14));
		//setPinValue('A',1,getPinValue('C',14));
		//setPinValue('A',2,getPinValue('C',14));
		//setPinValue('A',3,getPinValue('C',14));
		//setPinValue('A',4,getPinValue('C',14));
		//setPinValue('A',5,getPinValue('C',14));
		//('A',6,getPinValue('C',14));
		//setPinValue('A',7,getPinValue('C',14));
		//startCom();
	//	recvByte();
	}
}
/*
u8 startCom()//function to initialize the communication
{
	if(getPinValue('C',14)==0)
	{
		if(getPinValue('C',14)==0)
		{
			if(getPinValue('C',14)==1)
			{
				if(getPinValue('C',14)==1)
				{
					if(getPinValue('C',14)==0)
					{
						setPinValue('C',13,0);
						return 1;
					}
				}
			}
		}
	}
	else
		return 0;
}
*/
void recvByte()//function that recieves the byte
{
	//setPinValue()
}
