#ifndef __GPIO_H
#define __GPIO_H

//Standard Types
#define u8	unsigned char
#define u16 unsigned short int
#define u32 unsigned long int

#define s8	signed
#define s16	signed short int
#define s32	signed long int

//Standard error
#define STATUS_OK 	0U
#define STATUS_NOK	1U
typedef struct{
	u8 error_status;
}std_err;



/*Macros for user input arguments*/

//use HIGH or LOw to set pin states
#define HIGH 1U
#define LOW  0U





//Port_Mask


/*PRIVATE*/
#define GPIO_PORTA_BASE_ADDRESS  0x40010800
#define GPIO_PORTB_BASE_ADDRESS  0x40010C00
#define GPIO_PORTC_BASE_ADDRESS  0x40011000
#define GPIO_PORTD_BASE_ADDRESS  0x40011400
#define GPIO_PORTE_BASE_ADDRESS  0x40011800
#define GPIO_PORTF_BASE_ADDRESS  0x40011C00
#define GPIO_PORTG_BASE_ADDRESS  0x40012000

#define GPIOA				((void*)GPIO_PORTA_BASE_ADDRESS)
#define GPIOB				((void*)GPIO_PORTB_BASE_ADDRESS)
#define GPIOC				((void*)GPIO_PORTC_BASE_ADDRESS)
#define GPIOD				((void*)GPIO_PORTD_BASE_ADDRESS)
#define GPIOE				((void*)GPIO_PORTE_BASE_ADDRESS)
#define GPIOF				((void*)GPIO_PORTF_BASE_ADDRESS)
#define GPIOG				((void*)GPIO_PORTG_BASE_ADDRESS)

//Use this    ↓
//#define 	PORTA 0x40010800UL check with this
#define 	PORTA GPIOA
#define 	PORTB GPIOB
#define 	PORTC GPIOC
#define 	PORTD GPIOD
#define 	PORTE GPIOE
#define 	PORTF GPIOF
#define 	PORTG GPIOG

//Gpio_Pin_Num_Mask
#define GPIO_PIN_0       ((u16)0x0001)
#define GPIO_PIN_1       ((u16)0x0002)
#define GPIO_PIN_2       ((u16)0x0004)
#define GPIO_PIN_3       ((u16)0x0008)
#define GPIO_PIN_4       ((u16)0x0010)
#define GPIO_PIN_5       ((u16)0x0020)
#define GPIO_PIN_6       ((u16)0x0040)
#define GPIO_PIN_7       ((u16)0x0080)
#define GPIO_PIN_8       ((u16)0x0100)
#define GPIO_PIN_9       ((u16)0x0200)
#define GPIO_PIN_10      ((u16)0x0400)
#define GPIO_PIN_11      ((u16)0x0800)
#define GPIO_PIN_12      ((u16)0x1000)
#define GPIO_PIN_13      ((u16)0x2000)
#define GPIO_PIN_14      ((u16)0x4000)
#define GPIO_PIN_15      ((u16)0x8000)
#define GPIO_PIN_ALL     ((u16)0xFFFF)

//Gpio_Pin_Mode_Mask (Masks of CNF bits in CRL and CRH registers)
#define GPIO_MODE_INPUT_ANALOG                         0b00
#define GPIO_MODE_INPUT_FLOATING                       0b01
#define GPIO_MODE_INPUT_PULLUP_PULLDOWN                0b10

#define GPIO_MODE_OUTPUT_PUSH_PULL                     0b00
#define GPIO_MODE_OUTPUT_OPEN_DRAIN                    0b01
#define GPIO_MODE_OUTPUT_ALTERNATE_FUNCTION_PUSH_PULL  0b10
#define GPIO_MODE_OUTPUT_ALTERNATE_FUNCTION_OPEN_DRAIN 0b11

//Gpio_Pin_Speed_Mask (Masks of Mode bits in CRL and CRH registers)
#define GPIO_INPUT_MODE_RESET_STATE						00
#define GPIO_OUTPUT_SPEED_2MHz                          10
#define GPIO_OUTPUT_SPEED_10MHz                         01
#define GPIO_OUTPUT_SPEED_50MHz							11

//Use this type to assign new pin in your program
typedef struct{
	s16   pin;
	u8    mode;
	u8    speed;
}GPIO_Pin_t;



/*----------------------------------------------------------------------------*/

std_err GPIO_Init         (u32* Port_Mask, GPIO_Pin_t* Pin);
std_err GPIO_Pin_Write    (u32* Port_Mask, GPIO_Pin_t* Pin, u8  State);
std_err GPIO_Pin_Read     (u32* Port_Mask, GPIO_Pin_t* Pin, u8* ReturnValue);
std_err GPIO_Pin_FastSet  (u32* Port_Mask, GPIO_Pin_t* Pin);
std_err GPIO_Pin_FastReset(u32* Port_Mask, GPIO_Pin_t* Pin);
std_err GPIO_Pin_Lock     (u32* Port_Mask, GPIO_Pin_t* Pin);

#endif
