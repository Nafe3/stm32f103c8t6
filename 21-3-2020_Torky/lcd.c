/*
 * lcd.c
 *
 *  Created on: Mar 21, 2020
 *      Author: atourkey
 */

#include "lcd.h"

static uint8_t initCompleted ;

static uint8_t userWord[255] ;
static uint8_t userWordLen;
static uint8_t isWriteReq;

typedef enum {
	s1 ,
	s2 ,
	s3 ,
	s4
}initState_t;

static void initProcess(void);
static void writeProcess(void);
typedef enum {
	idle_proc ,
	write_proc ,
	clear_proc,
	cursermove_proc
}process_t;

static process_t curProcess ;

uint8_t lcd_init(void)
{
	// configure GPIOs
	// set mode output
	// set values  = 0

	return STAT_OK ;
}

uint8_t lcd_clear(void)
{
	if(curProcess == idle_proc){

		curProcess = clear_proc;
	}else{
		result = STAT_BUSY ;
	}
}

uint8_t lcd_write(const char * word, uint8_t len)
{
	uint8_t idx , result;

	if(curProcess == idle_proc){

		curProcess = write_proc;

		for(idx=0; idx < len; idx++)
		{
			userWord[idx] = word[idx];
		}

		userWordLen = len ;

		result = STAT_OK ;
	} else {
		result = STAT_BUSY ;
	}

	return result;
}

// 2 ms
void lcd_task(void)
{
	if(initCompleted){

		switch(curProcess)
		{
		case idle_proc:

		break;
		case write_proc:
			writeProcess();
		break;
		case clear_proc:
			clearProcess();
		break;
		}
	} else {
		// init process
		initProcess();
	}
}

#define S1_LINES_COMMAND 0

static void writeProcess(void)
{
	static uint8_t curChar;

	if(gpio_getpinValue(Enable_pins) == 1){
		gpio_writePin ( Enable_pins, 0);
	} else {
		// all char written
		if(userWordLen == curChar){
			curProcess = idle_proc ;
			curChar = 0;
			appWriteDoneNotify();
		}else {
			gpio_writePin ( data_pins, userWord[curChar]);
			gpio_writePin ( Enable_pins, 1);
			curChar++ ;
		}
	}
}

lcd_setWriteDoneNorification(notify_t cbf)
{
	appWriteDoneNotify = cbf ;
}

static void initProcess(void)
{
	static initState_t curState = s1 ;
	static uint8_t commandCounter ;
	switch(curState)
	{
	case s1:
		if(E == 1)
		{
			counter++ ;
			E=0 ;

			if(counter == 3){
				counter = 0;
				curState = s2 ;
			}
		}

		switch(commandCounter)
		{
		case S1_LINES_COMMAND :
			gpio_writePort(lcd_port, LINES_NUMBER);
//			actions
		break;
		}
		// apply s1 actions
		E = 1 ;

	break;

	case s2:
		if(E == 1)
		{
			counter++ ;
			E=0 ;

			if(counter == 2){
				counter = 0;
				curState = s3 ;
			}
		}

		switch(counter)
		{
		case 0 :
//			actions
		break;
		}
		// apply s1 actions
		E = 1 ;
	break;

	case s4:
		if(E == 1)
		{
			counter++ ;
			E=0 ;

			if(counter == 0){
				counter = 0;
				initCompleted = 1;
			}
		}

		switch(counter)
		{
		case 0 :
//			actions
		break;
		}
		// apply s1 actions
		E = 1 ;

	break;
	}
}


