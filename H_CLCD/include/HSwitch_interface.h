#ifndef H_SWITCH_INTERFACE_H
#define H_SWITCH_INTERFACE_H

/*Debouncing task mechanism
 *
 * RULE : EVERY MODULE SHOULD NOT GENERATE MORE THAN ONE TASK
 *
 * task(void)
 * {
 * 	static u8 prevState;
 * 	static u8 Counter;
 * 	u8 currState;
 *
 * 	currstate =gpio_read();
 * 	if (Currstate == prevstate)
 * 	{
 * 		counter++;
 * 	}
 * 	else{
 * 		counter=0;
 * 		}
 *
 * 	if(counter ==5)
 * 	{
 * 		state= currstate;
 * 		counter =0;
 * 	}
 * 	prevstate = curstate;
 *
 * }
 *
 *
 //global variable used in application
 *	u8 state;
 * 	u8 HSwitch_getSwitchState(SwitchNum)
 * 	{
 * 		return state;
 * 	}
 *
 *application should be written like this
 *APPRunnable()
 *{
 *	State=HSwitch_getSwitchState(Alarm_Switch);
 *	if(State==pressed)
 *	{
 *		Hled_setledState(ON);
 *	}
 *}
 *
 *
 * */
#define SWITCHES_MAX_NUM 5


/*Active Modes*/
#define ACTIVE_HIGH	1U
#define ACTIVE_LOW	0U

typedef struct{
	GPIO_Port_t      	Switch_Port;
	GPIO_Pin_t 			Switch_Pin;
	u8        			Pressed_State;//1 if pulldown, 0 if pullup resistor is active

}Switch_t;

void Switch_Task(void);/*assign it to the runnable element of task_t in your application*/
void HSwitch_init           ( Switch_t Switch);
u8   HSwitch_getSwitchState ( u8 SwitchNum )  ;

#endif
