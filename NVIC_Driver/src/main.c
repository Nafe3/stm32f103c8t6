#include "NVIC.h"
void main(void)
{
	//u8 koko=0;
	//u8EnableEXTI(31);
	//u8IsActive(31,&koko);
	//u8EnableEXTI(32);
	voidEnableAllEXTI();
	voidFilterEXTI_lowerThan(1);
	voidFilterEXTI_lowerThan(2);
	voidFilterEXTI_lowerThan(3);
	voidFilterEXTI_lowerThan(4);
	voidFilterEXTI_lowerThan(5);
	voidFilterEXTI_lowerThan(6);
	voidFilterEXTI_lowerThan(7);
	voidFilterEXTI_lowerThan(8);

}
