/*
 * sched.c
 *
 *  Created on: Nov 25, 2023
 *      Author: dell
 */

#include "sched.h"

sTasks SCH_tasks_G[SCH_MAX_TASK];
uint8_t current_index_task = 0;

void SCH_Init(void) {
	for(int i = 0; i < SCH_MAX_TASK; i++) {
		SCH_Delete_Task(i);
	}
}

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
	if(current_index_task < SCH_MAX_TASK) {
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period = PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;
		current_index_task++;
	}
}

void SCH_Update(void) {
	for(int i = 0; i < current_index_task; i++) {
		if(SCH_tasks_G[i].Delay > 0) {
			SCH_tasks_G[i].Delay--;
		}
		else {
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe++;
		}
	}
}

void SCH_Dispatch_Task(void) {
	for(int i = 0; i < current_index_task; i++) {
		if(SCH_tasks_G[i].RunMe > 0) {
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();

			if(SCH_tasks_G[i].Period == 0) {
				SCH_Delete_Task(i);
				i--;
			}
		}
	}
}

uint8_t SCH_Delete_Task(uint32_t taskID) {
	uint8_t Return_code = 0;
	if(taskID < (current_index_task - 1) && taskID >= 0) {
		Return_code = 1;
		while(taskID < current_index_task - 1) {
			SCH_tasks_G[taskID].pTask = SCH_tasks_G[taskID + 1].pTask;
			SCH_tasks_G[taskID].Delay = SCH_tasks_G[taskID + 1].Delay;
			SCH_tasks_G[taskID].Period = SCH_tasks_G[taskID + 1].Period;
			SCH_tasks_G[taskID].RunMe = SCH_tasks_G[taskID + 1].RunMe;
			taskID++;
		}
	}
	if(taskID == (current_index_task - 1)) {
		Return_code = 1;
		SCH_tasks_G[taskID].pTask = 0x0000;
		SCH_tasks_G[taskID].Delay = 0;
		SCH_tasks_G[taskID].Period = 0;
		SCH_tasks_G[taskID].RunMe = 0;
		SCH_tasks_G[taskID].TaskID = 0;
		current_index_task--;
	}
	return Return_code;
}
