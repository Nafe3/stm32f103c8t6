/*
This is to make value of bit=1 by 
making it OR with 1 shifted by bit number to left
*/
#define SET_BIT(VAR,BIT_NO) 	VAR|=(1<<BIT_NO)
/*
This is to make value of bit=0 by 
making it AND with 1 after shifting by bit number to left
*/
#define CLR_BIT(VAR,BIT_NO)		VAR&=~(1<<BIT_NO)
/*
This is to change value of bit 
by XOR with 1 after shifting by bit number to left
*/
#define TOGGLE_BIT(VAR,BIT_NO)	VAR^=(1<<BIT_NO)
/*
This is to get value of pin 
by AND with 1 after shifting VAR to right by Bit number
*/
#define GET_BIT(VAR,BIT_NO)		((VAR>>BIT_NO)&1)