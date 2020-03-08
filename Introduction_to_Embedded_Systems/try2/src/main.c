// libs
#include "STD_TYPES.h"
#include "BIT_MAN.h"
#include "Delay_interface.h"
// MCAL
#include "RCC_interface.h"
#include "DIO_interface.h"

#define PORT_IN 'A'
#define PIN_IN   15

#define PORT_LEDS 'A'

/* amount of time wasted as a new frame indicator */
#define FRAME_START_PAUSE_TIME_US (u32)6500
/* amount of time data is held without any change */
#define DATA_HOLD_TIME_US         (u32)2500
/* amount of time to skip as a result of edge change */
#define EDGE_TIMEOUT_US           (u32)1500
/* amount of time to purposefully skip to make sure we're at the level of next data */
#define DATA_WASTE_TIME_US        (u32)1500

void waitForFrameStart(void);
void waitForHighLevel(void);
void waitForLowLevel(void);
void waitForEdge(u8 currentLevel);

void main(void)
{
	/* init clocks */
	RCC_init();

	/* enable clock of port A */
	RCC_enablePeriClock(2, 2);

	/* set pins A0-7 (LEDS) mode to output 2MHz push-pull */
	for (u8 i = 0; i < 8; i++)
	{
		DIO_setPinMode(PORT_LEDS, i, 0b0010);
	}

	/* set pin A15 mode to input floating */
	DIO_setPinMode(PORT_IN, PIN_IN, 0b1000);
	DIO_setPinVal(PORT_IN,PIN_IN,0);

	/* both sender and receiver must be started exactly
	 * at the same time */
	delay_ms(3000);

	/* holds value of LEDs */
	u8 result = 0;

	/* holds value of current level */
	u8 level = 0;

	while (1)
	{
		result = 0;
		level = 0;

		/* wait for frame start */
		waitForFrameStart();

		/* read frame data (8-bits) */
		for (u8 i = 8; i > 0; i--)
		{
			level = DIO_getPinVal(PORT_IN, PIN_IN);
			result |= level;

			/* if not last iteration, then shift bit to the left.
			 * by the end of this loop, first received bit will be at the most left (MSB) */
			if (i != 1)
			{
				result <<= 1;
			}

			/* trap until the level of this bit is inverted (rising/falling edge) */
			waitForEdge(level);
		}

		/* display/reflect the received frame on the LEDs */
		for (u8 i = 8; i > 0; i--)
		{
			DIO_setPinVal(PORT_LEDS, i - 1, BIT_GET(result, i - 1));
		}
	}
}

void waitForFrameStart(void)
{
	/* wait for rising edge */
	waitForEdge(0);
}

void waitForHighLevel(void)
{
	while (DIO_getPinVal(PORT_IN, PIN_IN) == 0)
	{

	}
}

void waitForLowLevel(void)
{
	while (DIO_getPinVal(PORT_IN, PIN_IN) == 1)
	{

	}
}

void waitForEdge(u8 currentLevel)
{
	/* if current level is high, then wait for low and vice versa */
	if (currentLevel == 1)
	{
		waitForLowLevel();
	}
	else
	{
		waitForHighLevel();
	}

	/* wait until sender prepares next bit */
	delay_us(EDGE_TIMEOUT_US + DATA_WASTE_TIME_US);
}
