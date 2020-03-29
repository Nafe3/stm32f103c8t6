#include "STD_TYPES.h"
#include "GPIO.h"
#include "RCC.h"
#include "Systick.h"

#include "SCHED_interface.h"

GPIO_Pin_t led;

void app1(void)
{
	static u8 f=1;
	GPIO_Pin_Write(PORTC,&led,f);
	f^=1;
}

void app2(void)
{
	static u8 j=0;
	j++;
}

void app3(void)
{
	static u8 k=0;
	k++;
}
task_t t1,t2,t3;
int main(void)
{
	//task_t t1,t2,t3;
	t1.runnable=app1;
	t2.runnable=app2;
	t3.runnable=app3;
	t1.periodicTime=1;
	t2.periodicTime=2;
	t3.periodicTime=3;


	led.mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	led.pin  = GPIO_PIN_13;
	led.speed= GPIO_OUTPUT_SPEED_2MHz;

	RCC_voidSelectSysClk(2);
	RCC_voidEnablePeripheral(APB2,RCC_APB2ENR_IOPCEN,1);

	GPIO_Init(PORTC,&led);


	SCHED_Init();
	SCHED_Start();

	return 0;
}

// ----------------------------------------------------------------------------

