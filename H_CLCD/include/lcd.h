/*
 * lcd.h
 *
 *  Created on: Mar 21, 2020
 *      Author: atourkey
 */

#ifndef LCD_H_
#define LCD_H_

typedef unsigned char uint8_t;

#define STAT_OK 0
#define STAT_BUSY 1
#define STAT_ERROR 2


extern uint8_t lcd_init(void);
extern uint8_t lcd_write(const char * word, uint8_t len);


#endif /* LCD_H_ */
