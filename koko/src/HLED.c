/*
 * HLED.c
 *
 *  Created on: 29 Mar 2020
 *      Author: mirna
 */
#include "STD_TYPES.h"
#include "GPIO.h"
#include "HLED.h"



static LED_t G_LED;

void HLED_init      ( LED_t  LED )
{
	G_LED=LED;
	GPIO_Init(LED.LED_Port,&LED.LED_Pin);
}
void HLED_SetLedOn  ( u8 	 LED_Num )
{
	GPIO_Pin_Write(G_LED.LED_Port,&G_LED.LED_Pin,ON);
}
void HLED_SetLedOFF ( u8	 LED_Num )
{
	GPIO_Pin_Write(G_LED.LED_Port,&G_LED.LED_Pin,OFF);
}
