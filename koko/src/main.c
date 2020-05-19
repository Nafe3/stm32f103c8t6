#include "STD_TYPES.h"
#include "RCC.h"
#include "GPIO.h"
#include "HLED.h"
#include "HSwitch_interface.h"

#include "SCHED_interface.h"


#define Alarm_Switch	(u8)0
#define LED1			(u8)0

u8 State; 					/*Global variable to store switch state in it*/
Switch_t Switches[3];
LED_t G_Led;

task_t switch_task;
task_t app_task;

//extern void Switch_Task(void); //SO2AAAAAAAAAAAAAAAAAAAAL
//application should be written like this
void APPRunnable(void)
{
	State = HSwitch_getSwitchState(Alarm_Switch);
	if(State == Switches[Alarm_Switch].Pressed_State)
	{
		HLED_SetLedOFF(LED1); //Turn LED ON
	}
	else
		HLED_SetLedOn(LED1);
}



int main(void)
{
	RCC_voidSelectSysClk(HSE);
	RCC_voidEnablePeripheral(APB2,RCC_APB2ENR_IOPCEN,ON);
	RCC_voidEnablePeripheral(APB2,RCC_APB2ENR_IOPAEN,ON);
	RCC_voidEnablePeripheral(APB2,RCC_APB2ENR_IOPBEN,ON);


	Switches[Alarm_Switch].Switch_Port    = PORTA;
	Switches[Alarm_Switch].Switch_Pin.pin = GPIO_PIN_5;
	Switches[Alarm_Switch].Switch_Pin.mode = GPIO_MODE_INPUT_PULLUP_PULLDOWN;
	Switches[Alarm_Switch].Switch_Pin.speed = GPIO_INPUT_MODE_RESET_STATE;
	Switches[Alarm_Switch].Pressed_State = 0;	//not sure



	G_Led.LED_Port = PORTC;
	G_Led.LED_Pin.mode  = GPIO_MODE_OUTPUT_PUSH_PULL;
	G_Led.LED_Pin.pin   = GPIO_PIN_13;
	G_Led.LED_Pin.speed = GPIO_OUTPUT_SPEED_2MHz;


	switch_task.runnable = Switch_Task;
	switch_task.periodicTime = 5;

	app_task.runnable = APPRunnable;
	app_task.periodicTime = 5;

	HSwitch_init(Switches[Alarm_Switch]);

	GPIO_Pin_Write(PORTA,&Switches[Alarm_Switch].Switch_Pin,1);//enable pull-up

	HLED_init(G_Led);


	SCHED_Init();
	SCHED_Start();

	return 0;
}
