#ifndef NVIC_REGISTER_H
#define NVIC_REGISTER_H

/*Set Enable Register*/
#define NVIC_ISER0  *((volatile u32*) 0xE000E100)
#define NVIC_ISER1  *((volatile u32*) 0xE000E104)

/*Clear Enable Register */
#define NVIC_ICER0 	*((volatile u32*) 0xE000E180)
#define NVIC_ICER1 	*((volatile u32*) 0xE000E184)

/*Set Pending Flag*/
#define NVIC_ISPR0 	*((volatile u32*) 0xE000E200)
#define NVIC_ISPR1 	*((volatile u32*) 0xE000E204)


/*Clear Pending Flag*/
#define NVIC_ICPR0 	*((volatile u32*) 0xE000E280)
#define NVIC_ICPR1 	*((volatile u32*) 0xE000E284)


/*Get Active Flag*/
#define NVIC_IABR0 	*((volatile u32*) 0xE000E300)
#define NVIC_IABR1 	*((volatile u32*) 0xE000E304)
#define NVIC_IPR   	((volatile u8*)	  0xE000E400)

#endif
