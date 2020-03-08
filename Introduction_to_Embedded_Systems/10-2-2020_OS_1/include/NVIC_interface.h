#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

void NVIC_voidEnableExtInt(u8 Copy_u8Idx);

void NVIC_voidDisableExtInt(u8 Copy_u8Idx);

void NVIC_voidSetPendingFlag(u8 Copy_u8Idx);

void NVIC_voidClrPendingFlag(u8 Copy_u8Idx);

u8 NVIC_u8GetActiveFlag(u8 Copy_u8Idx);

#endif