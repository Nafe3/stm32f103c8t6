/****************************************/
/*Author :salma amr*/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"
#include "STK_register.h"

void (*SysTick_CallBack)(void);

void STK_voidIntialize(void)
{
	/* enable systick interrupt - clock =AHB/8*/
	/*stop systick*/
	STK_CTRL=0x00000002;
}

void STK_voidStart(u32 Copy_u32Value)
{
	/*load the value into load reg*/
	STK_LOAD = Copy_u32Value;
	/*clear value register*/
	STK_VAL=0;
	/*start system timer*/
	SET_BIT(STK_CTRL,0);
}
void STK_voidStop(void)
{
	STK_VAL=0;
	CLR_BIT(STK_CTRL,0);
}

void STK_voidSetCallBack(void (*Copy_ptr)(void))
{
	SysTick_CallBack = Copy_ptr;
}
void SysTick_Handler(void)
{
	SysTick_CallBack();
}

