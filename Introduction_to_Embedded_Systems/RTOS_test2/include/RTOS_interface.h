#ifndef RTOS_INTERFACE_H_
#define RTOS_INTERFACE_H_

typedef struct
{
	void (* Task_Handler)(void);
	u32 Periodicity;
}Task_t;

void RTOS_voidCreateTasks(u32 Copy_u32Priorty, u32 Copy_u32Priodicity, void(*Copy_pvTaskHandler)(void));
void RTOS_voidStartOS(void);
void RTOS_voidStopOS(void);
void RTOS_voidSuspendTask(u8);
void RTOS_voidResumeTask(u8);
void RTOS_voidDeleteTask(u8);

#endif
