/*
 * HSwitch_program.c
 *
 *  Created on: Mar 10, 2020
 *      Author: Mohamed Nafea
 */

#include "STD_TYPES.h"
#include "GPIO.h"
#include "HSwitch_interface.h"





//static u8 TaskReq;
static u8 UserSwitchNum;

static u8 S_TaskState;
Switch_t  S_Switch;

/*In case of more than one button
static u8 TaskState[SWITCHES_MAX_NUM];
Switch_t Switch[SWITCHES_MAX_NUM];*/

void Switch_Task(void)
{
	static u8 PrevState;
	static u8 Counter;
	u8 CurrState;

	//CurrState =gpio_read();//read user switch num here
	GPIO_Pin_Read(S_Switch.Switch_Port, &S_Switch.Switch_Pin, &CurrState); //edited by mirna
	if (CurrState == PrevState)
	{
		Counter++;
	}
	else
	{
		Counter=0;
	}

	if(Counter == 5)
	{
		S_TaskState= CurrState;
		Counter =0;
	}
	PrevState = CurrState;

}

//////////////////////////////////////////////////////////
void HSwitch_init        ( Switch_t user_Switch)
{
	//InitReq = 1;
	GPIO_Init(user_Switch.Switch_Port, &user_Switch.Switch_Pin);

	S_Switch.Switch_Port = user_Switch.Switch_Port;
	S_Switch.Switch_Pin = user_Switch.Switch_Pin;
	S_Switch.Pressed_State = user_Switch.Pressed_State;

}

///////////////////////////////////////////////////////////
u8 HSwitch_getSwitchState ( u8 SwitchNum )
{
	//TaskReq = 1;/*msh hawalla3 f merna we7na ben test 3shan ana moktane3 eny lazem a3mel request*/


	UserSwitchNum = SwitchNum;


	return S_TaskState;
}


