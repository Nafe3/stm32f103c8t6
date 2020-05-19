#include"HSwitch_interface.h"

u8 State; /*Global variable to store switch state in it*/
Switch_t Alarm_Switch;

//application should be written like this
void APPRunnable()
{
	State = HSwitch_getSwitchState(Alarm_Switch);
	if(State==PRESSED)
	{
		Hled_setledState(ON); //Turn LED ON
	}
	else
	Hled_setledState(OFF);
}





int main(void)
{
Alarm_Switch



}
