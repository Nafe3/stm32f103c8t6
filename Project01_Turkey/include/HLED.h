/*
 * HLED.h
 *
 *  Created on: 29 Mar 2020
 *      Author: mirna
 */

#ifndef HLED_H_
#define HLED_H_


#define ON 	1
#define OFF 0

typedef struct
{
	u32*       LED_Port;
	GPIO_Pin_t LED_Pin;
	//GPIO_Pin_t LED_Pin;
	//u8         LED_State;
}LED_t;

void HLED_init      ( LED_t  LED )	  ;
void HLED_SetLedOn  ( u8 	 LED_Num );
void HLED_SetLedOFF ( u8	 LED_Num );




#endif /* HLED_H_ */
