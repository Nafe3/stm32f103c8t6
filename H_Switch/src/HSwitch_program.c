/*
 * HSwitch_program.c
 *
 *  Created on: Mar 10, 2020
 *      Author: Mohamed Nafea
 */


#include "HSwitch_interface.h"

static u8 TaskReq;
static u8 UserSwitchNum;
static u8 TaskState;

void Switch_Task(void)
{
	static u8 PrevState;
	static u8 Counter;
	u8 CurrState;

	CurrState =gpio_read();//read user switch num here
	if (CurrState == PrevState)
	{
		Counter++;
	}
	else{
		Counter=0;
		}

	if(Counter ==5)
	{
		state= CurrState;
		Counter =0;
	}
	PrevState = CurrState;

}

//////////////////////////////////////////////////////////
void HSwitch_init           ( Switch_t Switch)
{
	//InitReq = 1;

}

///////////////////////////////////////////////////////////
u8 HSwitch_getSwitchState ( u8 SwitchNum )
{
	TaskReq = 1;
	UserSwitchNum = SwitchNum;
	return TaskState;
}


