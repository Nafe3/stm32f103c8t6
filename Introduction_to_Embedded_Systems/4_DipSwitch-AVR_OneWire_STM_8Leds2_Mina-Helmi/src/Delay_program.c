/* libs */
#include "STD_TYPES.h"
/* own */
#include "Delay_interface.h"
#include "Delay_private.h"

void delay_ms(u32 time)
{
	const u32 ctr = time * 666;
	for (volatile u32 c = 0; c < ctr; c++)
	{

	}
}

void delay_us(u32 time)
{
	const u32 ctr = (time * 666) / 1000;
	for (volatile u32 c = 0; c < ctr; c++)
	{

	}
}
