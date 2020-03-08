#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"STK_interface.h"
#include"STK_register.h"


void(*SysTick_CallBack)(void);


void STK_voidInitialize(void)
{
  /*Enable SysTick Interrupt -clock AHB/8 */
  /*Stop SysTick*/
  STK_CRTL = 0x00000002;
}
void STK_voidStart(u32 copy_u32Value)
{
  /*Load value into Load register*/
  STK_LOAD = copy_u32Value;
  
  /*clear value register*/
  STK_VAL =0;
  
  /*start system timer*/
  SET_BIT(STK_CRTL,0);
}
void STK_voidSetCallBack(void (*copy_Ptr)(void))
{
	SysTick_CallBack=copy_Ptr;
}

void SysTick_Handler(void)
{
  SysTick_CallBack();
}
