/******************************************/
/* Author : Mirna Anis                    */
/*Date    : 2 Feb 2020                    */
/*Version : V01                           */
/******************************************/

#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

#include "STD_TYPE.h"

void NVIC_voidEnableExtInt(u8 Copy_u8Idx);
void NVIC_voidDisableExtInt(u8 Copy_u8Idx);
void NVIC_voidSetPendingFlag(u8 Copy_u8Idx);
void NVIC_voidClrPendingFlag(u8 Copy_u8Idx);
u8 NVIC_u8GetActiveFlag(u8 Copy_u8Idx);

void NVIC_voidInitPriority(void);
void NVIC_voidSetPriority(u8 Copy_u8Idx, u8 Copy_u8Priority);

#endif
