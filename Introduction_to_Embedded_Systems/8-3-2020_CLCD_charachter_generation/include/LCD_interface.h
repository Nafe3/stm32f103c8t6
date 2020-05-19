/********************************/
/* Author		: Mohamed Nafea */
/* Version		: V01			*/
/* Release Date	: 14-1-2020		*/
/********************************/

//LCD Commands
#define CLCD_CMD_CLEAR_DISPLAY				0b00000001 //clear
#define CLCD_CMD_RETURN_HOME				0b00000010 //return to home
#define CLCD_CMD_ENTRY_MODE_SET				0b00000100 //mask the two least significant bits (Bit 1: I/D , Bi t0: SH)
#define CLCD_CMD_DISPLAY_ON_OFF_CONTROL		0b00001000 //mask the three LSBs (D,C,B) display, cursor, blinking of cursor
#define CLCD_CMD_CURSOR_DISPLAY_SHIFT		0b00010000 //mask Bits 2:3 (Bit 3: S/C , Bit 2: R/L)
#define CLCD_CMD_FUNCTION_SET				0b00100000 //mask Bits 2:4 (Bit 4: DL  , Bit 3: N , Bit2: F)
#define CLCD_CMD_SET_CGRAM_ADDRESS			0b01000000 //mask Bits 0:5 with CGRAM address
#define CLCD_CMD_SET_DDRAM_ADDRESS			0b10000000 //mask Bits 0:6 with DDRAM address
#define CLCD_CMD_READ_BUSY_FLAG_AND_ADDRESS 0b00000000 //Read (Bit 7: BF , Bit 6:0 address counter content)
#define CLCD_CMD_WRITE_DATA_TO_RAM			0b00000000 //mask Bits 0:7 with data to write in CG or DD RAM address
#define CLCD_CMD_READ_DATA_FROM_RAM         0b00000000 //read Bits 0:7 from CG or DD RAM



#define START_OF_CGRAM 				0b01000000

//LCD Display
#define screenUpperRigtLimit 0x0F
#define screenLowerRigtLimit 0x4F
#define screenUpperLeftLimit 0x00
#define screenLowerLeftLimit 0x40

#define default_Password	 1234

/* Description:	This API shall initialize LCD	*/
void CLCD_voidInitialize(void);

/* Description:	This API shall display data on LCD	*/
void CLCD_voidWriteData(u8 copy_u8Data);

/* Description:	This API shall initialize LCD	*/
void CLCD_voidWriteCmd(u8 copy_u8Cmd);

void CLCD_voidSetDataPort(u8 copy_u8Data);

void CLCD_voidWriteString(u8* copy_pu8String);

void CLCD_voidGenerateCharachter(u8 copy_pu8Arr[][8]);
