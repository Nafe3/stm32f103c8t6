#include "STD_TYPES.h"
#include "GPIO.h"
#include "RCC.h"
#include "Systick.h"


u8 counter=0;
GPIO_Pin_t led;


void func (void)
{
	counter++;
	if(counter ==2 )
	{
		GPIO_Pin_Write(PORTC,&led,0);
	}
}

int main(void)
{

	led.mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	led.pin  = GPIO_PIN_13;
	led.speed= GPIO_OUTPUT_SPEED_50MHz;

	RCC_voidSelectSysClk(2);
	RCC_voidEnablePeripheral(APB2,4,1);

	GPIO_Init(PORTC,&led);

	SYSTICK_Init();
	SYSTICK_SetCallback(func);
	SYSTICK_Start(0x00FFFFFF);

	while(1)
	{

	}
}

