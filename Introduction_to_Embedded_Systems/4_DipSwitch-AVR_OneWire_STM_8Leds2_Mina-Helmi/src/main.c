#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Delay_interface.h"

#include "DIO_interface.h"
#include "RCC_interface.h"
#include "DIO_register.h"

#define PORT_IN 'C'
#define PIN_IN   14

/* amount of time to skip as a result of edge change */
#define EDGE_TIMEOUT_US           (u32)500
/* amount of time to purposefully skip to make sure we're at the level of data */
#define DATA_WASTE_TIME_US        (u32)500
/* amount of time wasted as a new frame indicator */
#define FRAME_START_PAUSE_TIME_US (u32)3000
/* amount of time data is held without any change */
#define DATA_HOLD_TIME_US         (u32)1000

void waitForFrameStart(void);
void waitForHighLevel(void);
void waitForLowLevel(void);
void waitForEdge(u8 currentLevel);

void main(void)
{
	/* init clocks */
	RCC_Init();

	/* enable clock on port A */
	RCC_EnablePeripheralClock(2,2);
	RCC_EnablePeripheralClock(2,4);

	/* set pins A0-7 mode to output 2MHz push-pull */
	for (u8 i = 0; i < 8; i++)
	{
		setPinMode('A', i, 0b0010);
	}

	/* set pin A15 mode to input floating */
	setPinMode(PORT_IN, PIN_IN, 0b0100);

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
			level = getPinValue(PORT_IN, PIN_IN);
			result |= level;

			/* if not last iteration, then shift bit */
			if (i != 1)
			{
				result <<= 1;
			}

			waitForEdge(level);
		}

		for (u8 i = 8; i > 0; i--)
		{
			setPinValue('A', i - 1, GET_BIT(result, i - 1));
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
	while (getPinValue(PORT_IN, PIN_IN) == 0)
	{

	}
}

void waitForLowLevel(void)
{
	while (getPinValue(PORT_IN, PIN_IN) == 1)
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
