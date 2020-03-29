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
 * 	HSwitch_getSwitchState(SwitchNum)
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
