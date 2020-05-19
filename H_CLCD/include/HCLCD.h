/*
 * HCLCD.h
 *
 *  Created on: 31 Mar 2020
 *      Author: mirna
 */

#ifndef HCLCD_H_
#define HCLCD_H_

/*
typedef unsigned char		u8;
typedef unsigned int 		u16;
typedef unsigned long int	u32;
*/
typedef u8					ERROR_t;
typedef void (*notify_t)(void);

#define STATE_OK			(u8)0
#define STATE_IDLE			(u8)1
#define STATE_BUSY			(u8)2

typedef struct{
	GPIO_Pin_t  rs;
	GPIO_Port_t rs_Port;

	GPIO_Pin_t  rw;
	GPIO_Port_t rw_Port;

	GPIO_Pin_t  e;
	GPIO_Port_t e_Port;

	GPIO_Pin_t  d0;
	GPIO_Port_t d0_Port;

	GPIO_Pin_t  d1;
	GPIO_Port_t d1_Port;

	GPIO_Pin_t  d2;
	GPIO_Port_t d2_Port;

	GPIO_Pin_t  d3;
	GPIO_Port_t d3_Port;

	GPIO_Pin_t  d4;
	GPIO_Port_t d4_Port;

	GPIO_Pin_t  d5;
	GPIO_Port_t d5_Port;

	GPIO_Pin_t  d6;
	GPIO_Port_t d6_Port;

	GPIO_Pin_t  d7;
	GPIO_Port_t d7_Port;
}LCD_t;


void    LCD_Task(void);
ERROR_t HCLCD_init(LCD_t*);
ERROR_t HCLCD_write(const u8*, u8);
ERROR_t HCLCD_clear();
void    HCLCD_voidSetWriteDoneNotification(notify_t cbf);

#endif /* HCLCD_H_ */
