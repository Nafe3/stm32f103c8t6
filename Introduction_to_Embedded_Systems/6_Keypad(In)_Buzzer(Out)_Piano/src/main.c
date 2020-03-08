#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_register.h"
#include "RCC_interface.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_config.h"
#include "SEVEN_SEGMENT-interface.h"

void main(void)
{
	/* RCC Init */
	RCC_Init();

	/* Enable Clock in Port C */
	RCC_EnablePeripheralClock(2,2);//enable clock of PORT A
	RCC_EnablePeripheralClock(2,3);//enable clock of PORT B

	/*DIO configurations*/
	/*Input pins*/
	setPinMode('B',0, 0b1000);//Keypad row0
	setPinMode('B',1, 0b1000);//Keypad row1
	setPinMode('B',10,0b1000);//Keypad row2
	setPinMode('B',11,0b1000);//Keypad row3
	/*Activating pull-up resistance for input pins*/
	PORTB_ODR=0x00000C03;
	/*Output pins*/
	//PORT A
	setPinMode('A',0 ,0b0011);//Seven_Segment DP
	setPinMode('A',1 ,0b0011);//Seven_Segment C
	setPinMode('A',2 ,0b0011);//Seven_Segment D
	setPinMode('A',3 ,0b0011);//Seven_Segment E
	setPinMode('A',4 ,0b0011);//Seven_Segment B
	setPinMode('A',5 ,0b0011);//Seven_Segment A
	setPinMode('A',6 ,0b0011);//Seven_Segment F
	setPinMode('A',7 ,0b0011);//Seven_Segment G
	setPinMode('A',8 ,0b0011);//Seven_Segment common 0
	setPinMode('A',9 ,0b0011);//Seven_Segment common 1
	setPinMode('A',10,0b0011);//Seven_Segment common 2
	setPinMode('A',11,0b0011);//Seven_Segment common 3
	setPinMode('A',12,0b0011);//Seven_Segment common 4
	setPinMode('A',15,0b0011);//Seven_Segment common 5
	//PORT B                      
	setPinMode('B',3 ,0b0011);//Keypad column0
	setPinMode('B',4 ,0b0011);//Keypad column1
	setPinMode('B',5 ,0b0011);//Keypad column2
	setPinMode('B',6 ,0b0011);//Keypad column3

	setPinMode('B',7 ,0b0011);//Buzzer

	//powering the seven segments
	//setPinValue('A',8 ,1);//Seven_Segment common 0
	//setPinValue('A',9 ,1);//Seven_Segment common 1
	//setPinValue('A',10,1);//Seven_Segment common 2
	//setPinValue('A',11,1);//Seven_Segment common 3
	//setPinValue('A',12,1);//Seven_Segment common 4
	//setPinValue('A',15,1);//Seven_Segment common 5
	

	s8 rakam1=0;
	s8 rakam2=0;
	u8 i;
	u32 j;
	//s8 rakam3=0;
	//s8 rakam4=0;
	//s8 rakam5=0;
	//s8 rakam6=0;
	u8 key;

	//disableSevenSegment(4);
	//disableSevenSegment(5);
	enableSevenSegment(0);
	enableSevenSegment(1);
	//enableSevenSegment(2);
	//enableSevenSegment(3);
	//enableSevenSegment(4);
	//enableSevenSegment(5);
	while(1)
	{


		setPinValue('B',7,0);
		key=KEYPAD_GetPressedKey();
		if(key!=KEYPAD_NOKEYPRESS)
		{
			rakam1=key%10;
			rakam2=key/10;
		}
		//tones
		if(key==3)
		{
			setPinValue('B',7,1);
			for(j=0;j<1000000;j++);//delay
		}

		if(key==7)
		{
			for(i=0;i<100;i++)
			{
			setPinValue('B',7,1);
			for(j=0;j<1000;j++);//delay
			setPinValue('B',7,0);
			}
		}
		
		if(key==11)
		{
			for(i=0;i<200;i++)
			{
				setPinValue('B',7,1);
				for(j=0;j<2000;j++);//delay
				setPinValue('B',7,0);
			}
		}

		if(key==15)
		{
			for(i=0;i<100;i++)
			{
				setPinValue('B',7,1);
				for(j=0;j<700;j++);//delay
				setPinValue('B',7,0);
				for(j=0;j<700;j++);//delay
			}
		}

		//for(i=0;i<30;i++)
		//{
			disableSevenSegment(1);
			setNumber(rakam1);
			enableSevenSegment(0);
			for(j=0;j<50;j++);//delay

			disableSevenSegment(0);
			setNumber(rakam2);
			enableSevenSegment(1);
			for(j=0;j<50;j++);//delay
		//}


	}
}

