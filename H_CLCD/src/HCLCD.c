/*
 * HCLCD.c
 *
 *  Created on: 31 Mar 2020
 *      Author: mirna
 */

#include "STD_TYPES.h"
#include "GPIO.h"
#include "HCLCD.h"
#include"Delay_interface.h"

#define LCD_40MS_COUNT					(u8)20 //assuming that the task periodicity is 2ms

#define LCD_INIT_S_1					(u8)0
#define LCD_INIT_S_2					(u8)1

#define BIT_0							(u8)0
#define BIT_1               			(u8)1
#define BIT_2               			(u8)2
#define BIT_3               			(u8)3
#define BIT_4              				(u8)4
#define BIT_5               			(u8)5
#define BIT_6               			(u8)6
#define BIT_7               			(u8)7

#define FUNCTION_SET					0b00111000 //N=1 => 2 line display, F=0 => 5*7 dots char
#define DISPLAY_ON_OFF_CONTROL			0b00001100 //D=1 => entire display on, c=0 => cursor is not displayed, b=0 => character doesn't blink
#define DISPLAY_CLEAR					0b00000001
#define ENTRY_MODE_SET					0b00000110 //I/D=1 => move direction to the right, SH=0 => the display doesn't shift

//#define CLEAR_CMD						0b00000001

//LCD Commands
#define CLCD_CMD_CLEAR_DISPLAY				0b00000001 //clear
#define CLCD_CMD_RETURN_HOME				0b00000010 //return to home
#define CLCD_CMD_ENTRY_MODE_SET				0b00000100 //mask the two least significant bits (Bit 1: I/D , Bit 0: SH)
#define CLCD_CMD_DISPLAY_ON_OFF_CONTROL		0b00001000 //mask the three LSBs (D,C,B) display, cursor, blinking of cursor
#define CLCD_CMD_CURSOR_DISPLAY_SHIFT		0b00010000 //mask Bits 2:3 (Bit 3: S/C , Bit 2: R/L)
#define CLCD_CMD_FUNCTION_SET				0b00100000 //mask Bits 2:4 (Bit 4: DL  , Bit 3: N , Bit2: F)
#define CLCD_CMD_SET_CGRAM_ADDRESS			0b01000000 //mask Bits 0:5 with CGRAM address
#define CLCD_CMD_SET_DDRAM_ADDRESS			0b10000000 //mask Bits 0:6 with DDRAM address
#define CLCD_CMD_READ_BUSY_FLAG_AND_ADDRESS 0b00000000 //Read (Bit 7: BF , Bit 6:0 address counter content)
#define CLCD_CMD_WRITE_DATA_TO_RAM			0b00000000 //mask Bits 0:7 with data to write in CG or DD RAM address
#define CLCD_CMD_READ_DATA_FROM_RAM         0b00000000 //read Bits 0:7 from CG or DD RAM


/*
typedef enum {
	s1 ,
	s2 ,
	s3 ,
	s4
}initState_t;
*/

typedef enum {
	idle_proc ,
	write_proc ,
	clear_proc,
	cursermove_proc
}process_t;


notify_t appWriteDoneNotify;

LCD_t G_lcd;

//static u8* G_userData;//NILA SODA
static u8 G_userData[10];
static u8 G_dataLen;
static u8 initCompleted;
static u8 G_initFlag;
static u8 G_writeFlag;
static u8 G_clearFlag;

//static uint8_t initCompleted ;
static process_t curProcess ;
//static uint8_t isWriteReq;

/*Static Functions */

static void HLCD_setDataPort(u8 data)
{
	u8 volatile LOC_u8Bit;

	LOC_u8Bit = ((data>>BIT_0)&1);
	GPIO_Pin_Write(G_lcd.d0_Port ,&(G_lcd.d0),LOC_u8Bit);

	LOC_u8Bit = ((data>>BIT_1)&1);
	GPIO_Pin_Write(G_lcd.d1_Port ,&(G_lcd.d1),LOC_u8Bit);

	LOC_u8Bit = ((data>>BIT_2)&1);
	GPIO_Pin_Write(G_lcd.d2_Port ,&(G_lcd.d2),LOC_u8Bit);

	LOC_u8Bit = ((data>>BIT_3)&1);
	GPIO_Pin_Write(G_lcd.d3_Port ,&(G_lcd.d3),LOC_u8Bit);

	LOC_u8Bit = ((data>>BIT_4)&1);
	GPIO_Pin_Write(G_lcd.d4_Port ,&(G_lcd.d4),LOC_u8Bit);

	LOC_u8Bit = ((data>>BIT_5)&1);
	GPIO_Pin_Write(G_lcd.d5_Port ,&(G_lcd.d5),LOC_u8Bit);

	LOC_u8Bit = ((data>>BIT_6)&1);
	GPIO_Pin_Write(G_lcd.d6_Port ,&(G_lcd.d6),LOC_u8Bit);

	LOC_u8Bit = ((data>>BIT_7)&1);
	GPIO_Pin_Write(G_lcd.d7_Port ,&(G_lcd.d7),LOC_u8Bit);
}

static void HLCD_writeProcess(void)
{
	static u8 curChar;
	u8 Pin_Read_Return ;
	GPIO_Pin_Read(G_lcd.e_Port, &(G_lcd.e), &Pin_Read_Return);

	if(Pin_Read_Return == 1){
		GPIO_Pin_Write (G_lcd.e_Port, &(G_lcd.e), 0);
	} else {
		// all char written
		if(G_dataLen == curChar){
			curProcess = idle_proc ;
			G_writeFlag = 0; /* reset the write flag to allow further write process */
			curChar = 0;
			if (appWriteDoneNotify) /* if not an empty pointer */
			{
				appWriteDoneNotify();
			}
		}else {
			GPIO_Pin_Write(G_lcd.rs_Port, &(G_lcd.rs),1);
			GPIO_Pin_Write(G_lcd.rw_Port, &(G_lcd.rw),0);

			HLCD_setDataPort ( G_userData[curChar]);

			GPIO_Pin_Write (G_lcd.e_Port, &(G_lcd.e), 1);
			curChar++ ;
		}
	}
}

static void HLCD_initProcess()
{
//	/* wait for more than 30ms after VDD rises to 4.5V */
//	static u8 counter = 0;
//	counter++;
//	static u8 state = LCD_INIT_S_1;
//	if(counter>=LCD_40MS_COUNT)
//	{
//		switch(state)
//		{
//			case LCD_INIT_S_1:
				delay_ms(40);
				GPIO_Pin_Write(G_lcd.rw_Port, &(G_lcd.rw),0);
				GPIO_Pin_Write(G_lcd.rs_Port, &(G_lcd.rs),0);
				HLCD_setDataPort(FUNCTION_SET);
				GPIO_Pin_Write(G_lcd.e_Port, &(G_lcd.e),1);
				delay_ms(1);
				GPIO_Pin_Write(G_lcd.e_Port, &(G_lcd.e),0);


				delay_ms(2);
				//GPIO_Pin_Write(G_lcd.rw_Port, &(G_lcd.rw),0);
				//GPIO_Pin_Write(G_lcd.rs_Port, &(G_lcd.rs),0);
				HLCD_setDataPort(DISPLAY_ON_OFF_CONTROL);
				GPIO_Pin_Write(G_lcd.e_Port, &(G_lcd.e),1);
				delay_ms(1);
				GPIO_Pin_Write(G_lcd.e_Port, &(G_lcd.e),0);

				delay_ms(2);
				//GPIO_Pin_Write(G_lcd.rw_Port, &(G_lcd.rw),0);
				//GPIO_Pin_Write(G_lcd.rs_Port, &(G_lcd.rs),0);
				HLCD_setDataPort(DISPLAY_CLEAR);
				GPIO_Pin_Write(G_lcd.e_Port, &(G_lcd.e),1);
				delay_ms(1);
				GPIO_Pin_Write(G_lcd.e_Port, &(G_lcd.e),0);

//				state = LCD_INIT_S_2;
//
//				break;
//
//			case LCD_INIT_S_2:
//
//              GPIO_Pin_Write(G_lcd.rw_Port, &(G_lcd.rw),0);
//				GPIO_Pin_Write(G_lcd.rs_Port, &(G_lcd.rs),0);
//				HLCD_setDataPort(ENTRY_MODE_SET);
				delay_ms(2);
				initCompleted = 1;
			//	curProcess = idle_proc;

//				break;
//		}
//	}
}

static void HLCD_clearProcess()
{
	u8 Pin_Read_Return ;
	GPIO_Pin_Read(G_lcd.e_Port, &(G_lcd.e), &Pin_Read_Return);

	if(Pin_Read_Return == 1)
	{
		GPIO_Pin_Write (G_lcd.e_Port, &(G_lcd.e), 0);
		curProcess=idle_proc;
		G_clearFlag = 0;
	}
	else
	{
		GPIO_Pin_Write(G_lcd.rs_Port, &(G_lcd.rs),0);
		GPIO_Pin_Write(G_lcd.rw_Port, &(G_lcd.rw),0);

		HLCD_setDataPort(CLCD_CMD_CLEAR_DISPLAY);

		GPIO_Pin_Write(G_lcd.e_Port, &(G_lcd.e),1);
	}
}

void LCD_Task(void)
{
	if(initCompleted){

		switch(curProcess)
		{
		case idle_proc:

		break;
		case write_proc:
			HLCD_writeProcess();
		break;
		case clear_proc:
			HLCD_clearProcess();
		break;

		default:
			break;
		}
	}
	else {
		// init process
		HLCD_initProcess();
	}
}

/*User Functions*/
ERROR_t HCLCD_init(LCD_t* lcd)
{
	ERROR_t e=STATE_OK;
	GPIO_Init(lcd->d0_Port, &(lcd->d0));
	GPIO_Init(lcd->d1_Port, &(lcd->d1 ));
	GPIO_Init(lcd->d2_Port, &(lcd->d2 ));
	GPIO_Init(lcd->d3_Port, &(lcd->d3 ));
	GPIO_Init(lcd->d4_Port, &(lcd->d4 ));
	GPIO_Init(lcd->d5_Port, &(lcd->d5 ));
	GPIO_Init(lcd->d6_Port, &(lcd->d6 ));
	GPIO_Init(lcd->d7_Port, &(lcd->d7 ));
	GPIO_Init(lcd->e_Port, &(lcd->e  ));
	GPIO_Init(lcd->rs_Port, &(lcd->rs ));
	GPIO_Init(lcd->rw_Port, &(lcd->rw ));

	G_lcd.d0      = lcd->d0;
	G_lcd.d0_Port = lcd->d0_Port;

	G_lcd.d1      = lcd->d1;
	G_lcd.d1_Port = lcd->d1_Port;

	G_lcd.d2      = lcd->d2;
	G_lcd.d2_Port = lcd->d2_Port;

	G_lcd.d3      = lcd->d3;
	G_lcd.d3_Port = lcd->d3_Port;

	G_lcd.d4      = lcd->d4;
	G_lcd.d4_Port = lcd->d4_Port;

	G_lcd.d5      = lcd->d5;
	G_lcd.d5_Port = lcd->d5_Port;

	G_lcd.d6      = lcd->d6;
	G_lcd.d6_Port = lcd->d6_Port;

	G_lcd.d7      = lcd->d7;
	G_lcd.d7_Port = lcd->d7_Port;

	G_lcd.e       = lcd->e;
	G_lcd.e_Port =  lcd->e_Port;

	G_lcd.rs      = lcd->rs;
	G_lcd.rs_Port = lcd->rs_Port;

	G_lcd.rw      = lcd->rw;
	G_lcd.rw_Port = lcd->rw_Port;

	G_initFlag = 1;

	return e;
}

ERROR_t HCLCD_write(const u8*data, u8 len)
{
	ERROR_t e = STATE_OK;
	u8 i;
	if(!G_writeFlag && curProcess == idle_proc)
	{
		G_writeFlag = 1;
		for(i=0;i<len;i++)
		{
			G_userData[i]=data[i];
			//*G_userData = *data;
			//G_userData++;
			//data++;
		}
		G_dataLen = len;
		e= STATE_OK;
		curProcess = write_proc;
	}
	else
		e = STATE_BUSY;
	return e;
}

ERROR_t HCLCD_clear()
{
	ERROR_t e = STATE_OK;
	if(curProcess == idle_proc)
	{
		curProcess = clear_proc;
		G_clearFlag = 1;
	}
	else
	{
		e = STATE_BUSY;
	}
	return e;
}

void HCLCD_voidSetWriteDoneNotification(notify_t cbf)
{
	appWriteDoneNotify = cbf ;
}

