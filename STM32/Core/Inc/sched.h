/*
 * sched.h
 *
 *  Created on: Nov 25, 2023
 *      Author: dell
 */

#ifndef INC_SCHED_H_
#define INC_SCHED_H_

#include <stdint.h>

typedef struct {
	void (*pTask)(void);
	uint32_t	Delay;
	uint32_t	Period;
	uint8_t 	RunMe;

	uint32_t	TaskID;
}sTasks;

#define SCH_MAX_TASK	40

void SCH_Init(void);
void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Task(void);
uint8_t SCH_Delete_Task(uint32_t taskID);

#endif /* INC_SCHED_H_ */
