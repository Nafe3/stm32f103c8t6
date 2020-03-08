#include "STD_TYPES.h"

extern void DIO_setPinMode(u8 Port, u8 Pin, u8 Mode);
extern void DIO_setPinValue(u8 Port, u8 Pin, u8 Value);
extern void DIO_TogglePinValue(u8 Port, u8 Pin);
extern u8 DIO_getPinValue(u8 Port, u8 Pin);
