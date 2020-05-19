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

#define ON 	1
#define OFF 0

#define PRESSED	0


typedef struct{
u8 Switch_Port;
u8 Switch_Pin;
}Switch_t;

void HSwitch_init           ( Switch_t Switch);
u8   HSwitch_getSwitchState ( u8 SwitchNum )  ;

