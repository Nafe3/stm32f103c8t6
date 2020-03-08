/********************************/
/* Author		: Mohamed Nafea */
/* Version		: V01			*/
/* Release Date	: 14-1-2020		*/
/********************************/

/* Description:	This API shall initialize LCD	*/
void CLCD_voidInitialize(void);

/* Description:	This API shall display data on LCD	*/
void CLCD_voidWriteData(u8 copy_u8Data);

/* Description:	This API shall initialize LCD	*/
void CLCD_voidWriteCmd(u8 copy_u8Cmd);

void CLCD_voidSetDataPort(u8 copy_u8Data);

void CLCD_voidWriteString(u8* copy_pu8String);
