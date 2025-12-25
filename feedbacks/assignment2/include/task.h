/**
 * @file task.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version 1.0.1
 * @date May 21, 2024
 *
 * Defines the data structure for a cpu task.
 *
 */



#ifndef __TASK_HEADER__
#define __TASK_HEADER__


#define MIN_PRIORITY 1  	//The minimum priority of a task
#define MAX_PRIORITY 10		//The maximum priority of a task
#define TASK_SIZE 100

/*
 * TASK_INFO_FORMAT can be used to format task's name, priority, and burst
 * as "[T7] [3] [20]"   
 */
#define TASK_INFO_FORMAT "[%s] [%d] [%d] [%d]\n"


/*
 * The data structure of a cpu task that will be scheduled by the cpu schedular
 */ 
typedef struct cpu_task {
    char *name;
    int arrival;
    int priority;
    int burst;
} cpu_task_t;


#endif
