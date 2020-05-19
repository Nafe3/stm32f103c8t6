/******************************************/
/* Author : Mirna Anis                    */
/*Date    : 2 Feb 2020                    */
/*Version : V01                           */
/******************************************/

#include "BIT_MATH.h"
#include "NVIC_register.h"
#include "NVIC_interface.h"

void NVIC_voidEnableExtInt(u8 Copy_u8Idx)
{
  if(Copy_u8Idx<=31)
  {
    SET_BIT(NVIC_ISER0,Copy_u8Idx);
  }
  else if(Copy_u8Idx <=59)
  {
    Copy_u8Idx -=32;
    SET_BIT(NVIC_ISER1,Copy_u8Idx);
  }
}
void NVIC_voidDisableExtInt(u8 Copy_u8Idx)
{
  if(Copy_u8Idx<=31)
  {
    SET_BIT(NVIC_ICER0,Copy_u8Idx);
  }
  else if(Copy_u8Idx <=59)
  {
    Copy_u8Idx -=32;
    SET_BIT(NVIC_ICER1,Copy_u8Idx);
  }
}
void NVIC_voidSetPendingFlag(u8 Copy_u8Idx)
{
  if(Copy_u8Idx<=31)
  {
    SET_BIT(NVIC_ISPR0,Copy_u8Idx);
  }
  else if(Copy_u8Idx <=59)
  {
    SET_BIT(NVIC_ISPR1, (Copy_u8Idx - 32));
  }
}
void NVIC_voidClrPendingFlag(u8 Copy_u8Idx)
{
  if(Copy_u8Idx<=31)
  {
    SET_BIT(NVIC_ICPR0,Copy_u8Idx);
  }
  else if(Copy_u8Idx <=59)
  {
    Copy_u8Idx -=32;
    SET_BIT(NVIC_ICPR1,Copy_u8Idx);
  }
}

u8 NVIC_u8GetActiveFlag(u8 Copy_u8Idx)
{
  u8 Local_u8Result=0;
  if(Copy_u8Idx<=31)
  {
    Local_u8Result = GET_BIT(NVIC_IABR0,Copy_u8Idx);
  }
  else if(Copy_u8Idx <=59)
  {
    Copy_u8Idx -=32;
    Local_u8Result = GET_BIT(NVIC_IABR1,Copy_u8Idx);
  }
  return Local_u8Result;
}

void NVIC_voidInitPriority(void)
{
  #define SCB_AIRCR *((volatile u32*)0xE000ED0C)

  /* Bit 7&6 for group */
  /* Bit 5&4 for sub */

  SCB_AIRCR = 0x05FA0500;
}

void NVIC_voidSetPriority(u8 Copy_u8Idx, u8 Copy_u8Priority)
{

	NVIC_IPR[Copy_u8Idx]=Copy_u8Priority;

}
