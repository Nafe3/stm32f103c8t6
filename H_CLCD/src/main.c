#include "STD_TYPES.h"
#include "RCC.h"
#include "GPIO.h"
#include "RCC.h"
#include "SCHED_interface.h"
#include "HSwitch_interface.h"
#include "HLED.h"
#include "HCLCD.h"
#include <diag/Trace.h> // trace_printf

#define Alarm_Switch	(u8)0
#define LED1			(u8)0

u8 State; 					/*Global variable to store switch state in it*/
Switch_t Switches[3];
LED_t G_Led;
LCD_t   LCD1;

task_t switch_task;
task_t app_task;
task_t lcd_task;

//extern void Switch_Task(void); //SO2AAAAAAAAAAAAAAAAAAAAL
//application should be written like this

void LCD_CB(void)
{
	trace_printf("LCD callback\n");
}

void APPRunnable(void)
{
	HCLCD_write("Hello!", 6);
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
	RCC_voidEnablePeripheral(APB2,RCC_APB2ENR_IOPAEN,ON);
	RCC_voidEnablePeripheral(APB2,RCC_APB2ENR_IOPBEN,ON);
	RCC_voidEnablePeripheral(APB2,RCC_APB2ENR_IOPCEN,ON);

	Switches[Alarm_Switch].Switch_Port    = PORTB;
	Switches[Alarm_Switch].Switch_Pin.pin = GPIO_PIN_11;
	Switches[Alarm_Switch].Switch_Pin.mode = GPIO_MODE_INPUT_PULLUP_PULLDOWN;
	Switches[Alarm_Switch].Switch_Pin.speed = GPIO_INPUT_MODE_RESET_STATE;
	Switches[Alarm_Switch].Pressed_State = 0;	//not sure

	G_Led.LED_Port = PORTC;
	G_Led.LED_Pin.pin   = GPIO_PIN_13;
	G_Led.LED_Pin.mode  = GPIO_MODE_OUTPUT_PUSH_PULL;
	G_Led.LED_Pin.speed = GPIO_OUTPUT_SPEED_10MHz;


	LCD1.d0_Port = PORTA;
	LCD1.d1_Port = PORTA;
	LCD1.d2_Port = PORTA;
	LCD1.d3_Port = PORTA;
	LCD1.d4_Port = PORTA;
	LCD1.d5_Port = PORTA;
	LCD1.d6_Port = PORTA;
	LCD1.d7_Port = PORTA;
	LCD1.rs_Port = PORTA;
	LCD1.rw_Port = PORTB;
	LCD1.e_Port  = PORTB;

	LCD1.d0.pin = GPIO_PIN_0;
	LCD1.d1.pin = GPIO_PIN_1;
	LCD1.d2.pin = GPIO_PIN_2;
	LCD1.d3.pin = GPIO_PIN_3;
	LCD1.d4.pin = GPIO_PIN_4;
	LCD1.d5.pin = GPIO_PIN_5;
	LCD1.d6.pin = GPIO_PIN_6;
	LCD1.d7.pin = GPIO_PIN_7;
	LCD1.rs.pin = GPIO_PIN_8;
	LCD1.rw.pin = GPIO_PIN_12;
	LCD1.e.pin  = GPIO_PIN_13;

	LCD1.d0.speed = GPIO_OUTPUT_SPEED_10MHz;
	LCD1.d1.speed = GPIO_OUTPUT_SPEED_10MHz;
	LCD1.d2.speed = GPIO_OUTPUT_SPEED_10MHz;
	LCD1.d3.speed = GPIO_OUTPUT_SPEED_10MHz;
	LCD1.d4.speed = GPIO_OUTPUT_SPEED_10MHz;
	LCD1.d5.speed = GPIO_OUTPUT_SPEED_10MHz;
	LCD1.d6.speed = GPIO_OUTPUT_SPEED_10MHz;
	LCD1.d7.speed = GPIO_OUTPUT_SPEED_10MHz;
	LCD1.rs.speed = GPIO_OUTPUT_SPEED_10MHz;
	LCD1.rw.speed = GPIO_OUTPUT_SPEED_10MHz;
	LCD1.e. speed = GPIO_OUTPUT_SPEED_10MHz;

	LCD1.d0.mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	LCD1.d1.mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	LCD1.d2.mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	LCD1.d3.mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	LCD1.d4.mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	LCD1.d5.mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	LCD1.d6.mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	LCD1.d7.mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	LCD1.rs.mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	LCD1.rw.mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	LCD1.e.mode  = GPIO_MODE_OUTPUT_PUSH_PULL;


	switch_task.runnable = Switch_Task;
	switch_task.periodicTime = 5;

	app_task.runnable = APPRunnable;
	app_task.periodicTime = 5;

	lcd_task.runnable = LCD_Task;
	lcd_task.periodicTime = 2;

	HSwitch_init(Switches[Alarm_Switch]);

	GPIO_Pin_Write(Switches[Alarm_Switch].Switch_Port,&Switches[Alarm_Switch].Switch_Pin,1);//enable pull-up

	HLED_init(G_Led);

	HCLCD_init(&LCD1);
	HCLCD_voidSetWriteDoneNotification(LCD_CB);

	HCLCD_clear();
	//HCLCD_write("Hello!", 7);

	SCHED_Init();
	SCHED_Start();

	return 0;
}
