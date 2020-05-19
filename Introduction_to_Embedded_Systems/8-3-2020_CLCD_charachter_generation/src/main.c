#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "RCC_interface.h"
#include"Delay_interface.h"
//LCD Commands
#define CLEAR_DISPLAY				0b00000001 //clear
#define RETURN_HOME					0b00000010 //return to home
#define ENTRY_MODE_SET				0b00000100 //mask the two least significant bits
#define DISPLAY_ON_OFF_CONTROL		0b00001000 //mask the three LSBs (D,C,B) display, cursor, blinking of cursor
#define START_OF_CGRAM 				0b01000000
//LCD Display
#define screenUpperRigtLimit 0x0F
#define screenLowerRigtLimit 0x4F
#define screenUpperLeftLimit 0x00
#define screenLowerLeftLimit 0x40

#define default_Password	 1234

int main (void)
{
	delay_setCPUclockFactor(8000000);
	RCC_Init();
	RCC_EnablePeripheralClock(2,2);
	RCC_EnablePeripheralClock(2,3);
	//portInitialize();
	setPinMode('A',0,1);
	setPinMode('A',1,1);
	setPinMode('A',2,1);
	setPinMode('A',3,1);
	setPinMode('A',4,1);
	setPinMode('A',5,1);
	setPinMode('A',6,1);
	setPinMode('A',7,1);
	setPinMode('A',8,1);
	setPinMode('B',12,1);
	setPinMode('B',13,1);

	CLCD_voidInitialize();

	//Start of CGRAM
	CLCD_voidWriteCmd(START_OF_CGRAM);
	//1 standing arms down
	  CLCD_voidWriteData(0b01110);
	  CLCD_voidWriteData(0b01110);
	  CLCD_voidWriteData(0b01110);
	  CLCD_voidWriteData(0b00100);
	  CLCD_voidWriteData(0b01110);
	  CLCD_voidWriteData(0b10101);
	  CLCD_voidWriteData(0b01010);
	  CLCD_voidWriteData(0b10001);
	  //2 standing arms up
	//  B01110,
	//   B01110,
	//   B01110,
	//   B10101,
	//   B01110,
	//   B00100,
	//   B00100,
	//   B00100
	//   //3 ball
	//   B00000,
	//     B00000,
	//     B00000,
	//     B01110,
	//     B01110,
	//     B01110,
	//     B00000,
	//     B00000
	//	 //4 ball pos 1
	//	 B01110,
	//	   B01110,
	//	   B01110,
	//	   B00100,
	//	   B01110,
	//	   B00100,
	//	   B01011,
	//	   B10001
	//	 //5 ball pos 2
    // 	   B01110,
	//	   B01110,
	//	   B01110,
	//	   B00100,
	//	   B01111,
	//   	   B00100,
	//	   B01010,
	//	   B10001
	//		//6 ball pos 3
	//			 B01110,
	//			   B01110,
	//			   B01111,
	//			   B00100,
	//			   B01110,
	//			   B00100,
	//			   B01010,
	//			   B10001

	  CLCD_voidWriteCmd(0b10000000);
	  CLCD_voidWriteData(0);




	  while(1)
	{



	}

return 0;
}
