#include "NVIC.h"
void main(void)
{
u8 koko=0;
	u8EnableEXTI(31);
	u8IsActive(31,&koko);
	u8EnableEXTI(32);
}
