/**
 * @file cpu.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version 1.0.0
 * @date May 21, 2024
 *
 * Defines the functions required to simulate cpu cycles.
 *
 */


#ifndef __CPU_HEADER__
#define __CPU_HEADER__

#include "task.h"


#define QUANTUM 10 	//length of a time quantum

/*
 * TASK_RUN_INFO_FORMAT can be used to format task's name, priority, burst, slice
 * as "Running task = [T7] [3] [20] for 10 units."   
 */
#define TASK_RUN_INFO_FORMAT "Running task = [%s] [%d] [%d] [%d] for %d units.\n"


void run(const cpu_task_t *task, const int slice);
// Print task's name, priority, burst and the time slice is is being running
// using TASK_RUN_INFO_FORMAT in printf() function.
// Please, don't use any sleep() function to simulate running for slice time unit. It
// will make the simulation execution unnecessarily slower.


#endif
