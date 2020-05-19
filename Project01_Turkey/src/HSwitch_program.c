/*
 * HSwitch_program.c
 *
 *  Created on: Mar 10, 2020
 *      Author: Mohamed Nafea
 */

#include "STD_TYPES.h"
#include "GPIO.h"
#include "HSwitch_interface.h"


#define NUM_OF_SWITCHES			(u8)3


//static u8 TaskReq;
//static u8 UserSwitchNum;

static u8 S_TaskState[NUM_OF_SWITCHES];
Switch_t  S_Switch[NUM_OF_SWITCHES];

/*In case of more than one button
static u8 TaskState[SWITCHES_MAX_NUM];
Switch_t Switch[SWITCHES_MAX_NUM];*/

void Switch_Task(void)
{
	static u8 PrevState[NUM_OF_SWITCHES];
	static u8 Counter[NUM_OF_SWITCHES];
	u8 CurrState[NUM_OF_SWITCHES];

	u8 idx;
	//CurrState =gpio_read();//read user switch num here
	for(idx=0; idx<NUM_OF_SWITCHES;idx++)
	{
		GPIO_Pin_Read(S_Switch[idx].Switch_Port, &S_Switch[idx].Switch_Pin, &CurrState[idx]); //edited by mirna
		if (CurrState[idx] == PrevState[idx])
		{
			Counter[idx]++;
		}
		else
		{
			Counter[idx]=0;
		}

		if(Counter[idx] == 5)
		{
			S_TaskState[idx]= CurrState[idx];
			Counter[idx] = 0;
		}
		PrevState[idx] = CurrState[idx];
	}
}

//////////////////////////////////////////////////////////
void HSwitch_init ( Switch_t user_Switch[])
{
	//InitReq = 1;
	u8 index;
	for(index=0; index < NUM_OF_SWITCHES; index++)
	{
		GPIO_Init(user_Switch[index].Switch_Port, &user_Switch[index].Switch_Pin);
		S_Switch[index].Switch_Port = user_Switch[index].Switch_Port;
		S_Switch[index].Switch_Pin = user_Switch[index].Switch_Pin;
		S_Switch[index].Pressed_State = user_Switch[index].Pressed_State;
	}

}

///////////////////////////////////////////////////////////
u8 HSwitch_getSwitchState ( u8 SwitchNum )
{
	//TaskReq = 1;/*msh hawalla3 f merna we7na ben test 3shan ana moktane3 eny lazem a3mel request*/
	//UserSwitchNum = SwitchNum;
	return S_TaskState[SwitchNum];
}


