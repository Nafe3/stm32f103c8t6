#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "KEYPAD_interface.h"
#include "KEYPAD_config.h"
#include "KEYPAD_private.h"

u8 KEYPAD_GetPressedKey(void)
{
	u8 ROWSCounter=0;
	u8 COLSCounter=0;
	u8 keypressed = KEYPAD_NOKEYPRESS;
	//Static 3shan msh kol ma a call el function a push el arrays fel stack
	//ba3deen a pull wana rage3 3shan el time complexity
	static u8 KEYPAD_ROWSPortArray[KEYPAD_ROWSMAXNUM]=KEYPAD_ROWS_PORTS;
	static u8 KEYPAD_COLSPortArray[KEYPAD_COLSMAXNUM]=KEYPAD_COLS_PORTS;
	
	static u8 KEYPAD_ROWSPinArray[KEYPAD_ROWSMAXNUM]=KEYPAD_ROWS_PINS;
	static u8 KEYPAD_COLSPinArray[KEYPAD_COLSMAXNUM]=KEYPAD_COLS_PINS;
	
	static u8 KeysArray[KEYPAD_ROWSMAXNUM][KEYPAD_COLSMAXNUM]=KEYPAD_KEYS;

	//we have to turn every output pin into zero
	//then loop on the input pins to see which one of them is zero(pressed)
	//COLS is output
	//ROWs is input
	for (COLSCounter=0;COLSCounter<KEYPAD_COLSMAXNUM; COLSCounter++)
	{
		setPinValue(KEYPAD_COLSPortArray[COLSCounter],KEYPAD_COLSPinArray[COLSCounter],0);
		for (ROWSCounter=0;ROWSCounter<KEYPAD_ROWSMAXNUM; ROWSCounter++)
		{
			while(getPinValue(KEYPAD_ROWSPortArray[ROWSCounter],KEYPAD_ROWSPinArray[ROWSCounter])==0)
				keypressed=KeysArray[ROWSCounter][COLSCounter];
		}
		setPinValue(KEYPAD_COLSPortArray[COLSCounter],KEYPAD_COLSPinArray[COLSCounter],1);
	}
	return keypressed;
}
