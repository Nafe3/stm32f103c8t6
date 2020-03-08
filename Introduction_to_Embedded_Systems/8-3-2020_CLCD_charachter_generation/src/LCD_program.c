/********************************/
/* Author		: Mohamed Nafea */
/* Version		: V01			*/
/* Release Date	: 14-1-2020		*/
/********************************/

/* Description:	This API shall initialize LCD	*/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"

#include"LCD_config.h"
#include"LCD_interface.h"
#include<util/delay.h>
void CLCD_voidInitialize(void)
{
	/*	wait more than 30 us	*/
	_delay_ms(40);

	/**/
	//  setPinValue(CLCD_u8_E_PORT,CLCD_u8_E_PIN,0);

	CLCD_voidWriteCmd(0b00111000);
	CLCD_voidWriteCmd(0b00001100);
	CLCD_voidWriteCmd(0b00000001);

	_delay_ms(2);
}

/*Description : This API shall display data on LCD */
void CLCD_voidWriteData(u8 copy_u8Data)
{
  /* Set RS = 1 */
	setPinValue(CLCD_u8_RS_PORT,CLCD_u8_RS_PIN, 1);
  
  /* Set RW = 0 */
	setPinValue(CLCD_u8_RW_PORT,CLCD_u8_RW_PIN, 0);
  
  /* Set Data on Data Port */
  CLCD_voidSetDataPort(copy_u8Data);
  
  /* Enable Pulse */
  setPinValue(CLCD_u8_E_PORT,CLCD_u8_E_PIN,1);
  _delay_ms(1);
  setPinValue(CLCD_u8_E_PORT,CLCD_u8_E_PIN,0);
  _delay_ms(1);
  
}

void CLCD_voidSetDataPort(u8 Copy_u8Data)
{
  u8 Local_u8Bit;
  
  Local_u8Bit = GET_BIT(Copy_u8Data,0);
  setPinValue(CLCD_u8_D0_PORT,CLCD_u8_D0_PIN, Local_u8Bit);
  
  Local_u8Bit = GET_BIT(Copy_u8Data,1);
  setPinValue(CLCD_u8_D0_PORT,CLCD_u8_D1_PIN, Local_u8Bit);
  
  Local_u8Bit = GET_BIT(Copy_u8Data,2);
  setPinValue(CLCD_u8_D0_PORT,CLCD_u8_D2_PIN, Local_u8Bit);
  
  Local_u8Bit = GET_BIT(Copy_u8Data,3);
  setPinValue(CLCD_u8_D0_PORT,CLCD_u8_D3_PIN, Local_u8Bit);
  
  Local_u8Bit = GET_BIT(Copy_u8Data,4);
  setPinValue(CLCD_u8_D0_PORT,CLCD_u8_D4_PIN, Local_u8Bit);
  
  Local_u8Bit = GET_BIT(Copy_u8Data,5);
  setPinValue(CLCD_u8_D0_PORT,CLCD_u8_D5_PIN, Local_u8Bit);
  
  Local_u8Bit = GET_BIT(Copy_u8Data,6);
  setPinValue(CLCD_u8_D0_PORT,CLCD_u8_D6_PIN, Local_u8Bit);
  
  Local_u8Bit = GET_BIT(Copy_u8Data,7);
  setPinValue(CLCD_u8_D0_PORT,CLCD_u8_D7_PIN, Local_u8Bit);
}

/*Description : This API shall execute command on LCD*/
void CLCD_voidWriteCmd(u8 copy_u8Cmd)
{
  /* Set RS = 0 */
	setPinValue(CLCD_u8_RS_PORT,CLCD_u8_RS_PIN, 0);
  
  /* Set RW = 0 */
	setPinValue(CLCD_u8_RW_PORT,CLCD_u8_RW_PIN, 0);
  
  /* Set Data on Data Port */
  CLCD_voidSetDataPort(copy_u8Cmd);
  
  /* Enable Pulse */
  setPinValue(CLCD_u8_E_PORT,CLCD_u8_E_PIN,1);
  _delay_ms(1);
  setPinValue(CLCD_u8_E_PORT,CLCD_u8_E_PIN,0);
  _delay_ms(1);

}

void CLCD_voidWriteString(u8* copy_pu8String)
{
  u8 Local_u8Counter = 0;

  while((copy_pu8String[Local_u8Counter]) != '\0')
  {
    CLCD_voidWriteData(copy_pu8String[Local_u8Counter]);
    Local_u8Counter++;
  }
}
