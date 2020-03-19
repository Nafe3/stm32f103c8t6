#include "STD_TYPES.h"
#include "GPIO.h"
#include "RCC.h"
#include "Systick.h"


u8 counter=0;
GPIO_Pin_t led;

u8 volatile f=0;
void func (void)
{
	//counter++;
	//if(counter ==2 )
	//{
	if(f==0)
	{
		GPIO_Pin_Write(PORTC,&led,1);
		f=1;
	}
	else
	{
		GPIO_Pin_Write(PORTC,&led,0);
		f=0;
	}
		//GPIO_Pin_Read(PORTC,&led,&p);
		//GPIO_Pin_Write(PORTC,&led,~p);
	//}
}

int main(void)
{

	led.mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	led.pin  = GPIO_PIN_13;
	led.speed= GPIO_OUTPUT_SPEED_2MHz;

	RCC_voidSelectSysClk(2);
	RCC_voidEnablePeripheral(APB2,RCC_APB2ENR_IOPCEN,1);

	GPIO_Init(PORTC,&led);
	//GPIO_Pin_Write(PORTC,&led,1);
	SYSTICK_Init();
	SYSTICK_SetCallback(func);
	SYSTICK_Start(0x003D08FF);
	while(1);
}

