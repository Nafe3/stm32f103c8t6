#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
//#include "PORT_interface.h"

#include "SEVEN_SEGMENT-interface.h"
#include "SEVEN_SEGMENT-config.h"
#include "SEVEN_SEGMENT-private.h"

u8 lastNumber= sevenSeg1_Initial_Value;
u8 sevenSeg_Enable_Port[6]={sevenSeg1_Enable_Port,sevenSeg2_Enable_Port,sevenSeg3_Enable_Port,sevenSeg4_Enable_Port,sevenSeg5_Enable_Port,sevenSeg6_Enable_Port};
u8 sevenSeg_Enable_Pins[6]={sevenSeg1_Enable_Pin,sevenSeg2_Enable_Pin,sevenSeg3_Enable_Pin,sevenSeg4_Enable_Pin,sevenSeg5_Enable_Pin,sevenSeg6_Enable_Pin};
void setNumber(u8 number)
{
	u8 sevenSeg_Numbers[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};
	#if sevenSeg_Mode == 1
		setPinValue(sevenSeg_Pin_A_Port,sevenSeg_Pin_A_Number,GET_BIT(sevenSeg_Numbers[number],0));
		setPinValue(sevenSeg_Pin_B_Port,sevenSeg_Pin_B_Number,GET_BIT(sevenSeg_Numbers[number],1));
		setPinValue(sevenSeg_Pin_C_Port,sevenSeg_Pin_C_Number,GET_BIT(sevenSeg_Numbers[number],2));
		setPinValue(sevenSeg_Pin_D_Port,sevenSeg_Pin_D_Number,GET_BIT(sevenSeg_Numbers[number],3));
		setPinValue(sevenSeg_Pin_E_Port,sevenSeg_Pin_E_Number,GET_BIT(sevenSeg_Numbers[number],4));
		setPinValue(sevenSeg_Pin_F_Port,sevenSeg_Pin_F_Number,GET_BIT(sevenSeg_Numbers[number],5));
		setPinValue(sevenSeg_Pin_G_Port,sevenSeg_Pin_G_Number,GET_BIT(sevenSeg_Numbers[number],6));
		setPinValue(sevenSeg_Pin_H_Port,sevenSeg_Pin_H_Number,GET_BIT(sevenSeg_Numbers[number],7));
	#elif sevenSeg_Mode == 0
		setPinValue(sevenSeg_Pin_A_Port,sevenSeg_Pin_A_Number,GET_BIT(sevenSeg_Numbers[number],0)^0x01);
		setPinValue(sevenSeg_Pin_B_Port,sevenSeg_Pin_B_Number,GET_BIT(sevenSeg_Numbers[number],1)^0x01);
		setPinValue(sevenSeg_Pin_C_Port,sevenSeg_Pin_C_Number,GET_BIT(sevenSeg_Numbers[number],2)^0x01);
		setPinValue(sevenSeg_Pin_D_Port,sevenSeg_Pin_D_Number,GET_BIT(sevenSeg_Numbers[number],3)^0x01);
		setPinValue(sevenSeg_Pin_E_Port,sevenSeg_Pin_E_Number,GET_BIT(sevenSeg_Numbers[number],4)^0x01);
		setPinValue(sevenSeg_Pin_F_Port,sevenSeg_Pin_F_Number,GET_BIT(sevenSeg_Numbers[number],5)^0x01);
		setPinValue(sevenSeg_Pin_G_Port,sevenSeg_Pin_G_Number,GET_BIT(sevenSeg_Numbers[number],6)^0x01);
		setPinValue(sevenSeg_Pin_H_Port,sevenSeg_Pin_H_Number,GET_BIT(sevenSeg_Numbers[number],7)^0x01);
	#endif
}

void setLed(u8 led)
{
	u8 sevenSeg_Numbers[8] = {0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000};
		#if sevenSeg_Mode == 1
			setPinValue(sevenSeg_Pin_A_Port,sevenSeg_Pin_A_Number,GET_BIT(sevenSeg_Numbers[led],0));
			setPinValue(sevenSeg_Pin_B_Port,sevenSeg_Pin_B_Number,GET_BIT(sevenSeg_Numbers[led],1));
			setPinValue(sevenSeg_Pin_C_Port,sevenSeg_Pin_C_Number,GET_BIT(sevenSeg_Numbers[led],2));
			setPinValue(sevenSeg_Pin_D_Port,sevenSeg_Pin_D_Number,GET_BIT(sevenSeg_Numbers[led],3));
			setPinValue(sevenSeg_Pin_E_Port,sevenSeg_Pin_E_Number,GET_BIT(sevenSeg_Numbers[led],4));
			setPinValue(sevenSeg_Pin_F_Port,sevenSeg_Pin_F_Number,GET_BIT(sevenSeg_Numbers[led],5));
			setPinValue(sevenSeg_Pin_G_Port,sevenSeg_Pin_G_Number,GET_BIT(sevenSeg_Numbers[led],6));
			setPinValue(sevenSeg_Pin_H_Port,sevenSeg_Pin_H_Number,GET_BIT(sevenSeg_Numbers[led],7));
		#elif sevenSeg_Mode == 0
			setPinValue(sevenSeg_Pin_A_Port,sevenSeg_Pin_A_Number,GET_BIT(sevenSeg_Numbers[led],0)^0x01);
			setPinValue(sevenSeg_Pin_B_Port,sevenSeg_Pin_B_Number,GET_BIT(sevenSeg_Numbers[led],1)^0x01);
			setPinValue(sevenSeg_Pin_C_Port,sevenSeg_Pin_C_Number,GET_BIT(sevenSeg_Numbers[led],2)^0x01);
			setPinValue(sevenSeg_Pin_D_Port,sevenSeg_Pin_D_Number,GET_BIT(sevenSeg_Numbers[led],3)^0x01);
			setPinValue(sevenSeg_Pin_E_Port,sevenSeg_Pin_E_Number,GET_BIT(sevenSeg_Numbers[led],4)^0x01);
			setPinValue(sevenSeg_Pin_F_Port,sevenSeg_Pin_F_Number,GET_BIT(sevenSeg_Numbers[led],5)^0x01);
			setPinValue(sevenSeg_Pin_G_Port,sevenSeg_Pin_G_Number,GET_BIT(sevenSeg_Numbers[led],6)^0x01);
			setPinValue(sevenSeg_Pin_H_Port,sevenSeg_Pin_H_Number,GET_BIT(sevenSeg_Numbers[led],7)^0x01);
		#endif
}



void enableSevenSegment(u8 sevenSegNum)
{
	#if sevenSeg1_Mode == 1
		setPinValue(sevenSeg_Enable_Port[sevenSegNum],sevenSeg_Enable_Pins[sevenSegNum],0x00);
	#elif sevenSeg1_Mode == 0
		setPinValue(sevenSeg_Enable_Port[sevenSegNum],sevenSeg_Enable_Pins[sevenSegNum],0x01);
	#endif
	//setNumber(lastNumber);
}
void disableSevenSegment(u8 sevenSegNum)
{
	#if sevenSeg1_Mode == 1
		setPinValue(sevenSeg_Enable_Port[sevenSegNum],sevenSeg_Enable_Pins[sevenSegNum],0x01);
	#elif sevenSeg_Mode == 0
		setPinValue(sevenSeg_Enable_Port[sevenSegNum],sevenSeg_Enable_Pins[sevenSegNum],0x00);
	#endif
}
