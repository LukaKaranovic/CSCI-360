/**
 * @file schedule.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version 1.0.1
 * @date May 21, 2024
 *
 * Defines the functions required for a process scheduler.
 *
 */



#ifndef __SCHEDULE_HEADER__
#define __SCHEDULE_HEADER__

#include "task.h"
#include "list.h"
 
// cpu_task_t* pick_next_task(list_node_t* list);
// Pick up the next task from the given task list based on any of the specific scheduling algorithm.
//
//	    First Come First Serve (FCFS): Return the task that came first.
//
//	    Shortest Job First (SJF): Return the task that needs the least cpu burst and came first among the 
//                                tasks that need the same cpu burst.
//
//	    Round Robin (RR): Return the task that should get the turn in the current round
//
//	    Priority (PR): Return the task that has the highest priority and came first among the tasks
//                     in that priority level.
//                      
//	    Priority with Round Robin (PR-RR): Return the task that has the highest priority and should get the turn among
//                                         the tasks in that priority level. 
//


void schedule(list_node_t** list);
//For FCFS, schedule all the tasks from the task list by doing the followings:
//      - Pick up the task that came first by calling pick_next_task() function.
//      - Run the task by calling run() function for its needed cpu burst.
//      - Delete the task from the list by calling delete() function.
//
//For SJF, schedule all the tasks from the task list by doing the followings:
//      - Pick up the task that needs the least cpu burst and came first among the tasks that need the same cpu burst
//        by calling pick_next_task() function.
//      - Run the task by calling run() function for its needed cpu burst.
//      - Delete the task from the list by calling delete() function.
//
//For RR, schedule all the tasks from the task list by doing the followings:
//      - Pick up the next task by calling pick_next_task() function.
//      - Run the task by calling run() function for at most a quanta of the cpu burst and decrement task's cpu burst accordingly.
//	    - Delete the task from the list by calling delete() function only if the task has finished running its needed cpu burst.
//
//For PR, shecdule all the tasks from the task list doing the followings:
//      - Rearrange the tasks into multiple lists (for example, an array of lists), one list for each priority level
//      - For each priority level starting from the highest to lowest do the followings:
//          - Pick up the task that came first in this priority level by calling pick_next_task() function.
//          - Run the task by calling run() function for its needed cpu burst.
//          - Delete the task from the list by calling delete() function.
//
//For PR-RR, shecdule all the tasks from the task list doing the followings:
//      - Rearrange the tasks into multiple lists (for example, an array of lists), one list for each priority level
//      - For each priority level starting from the highest to lowest do the followings:
//          - Pick up the task in turn from this priority level by calling pick_next_task() function.
//              - If there is no other task in the same priority level run the task by calling run() function for its needed cpu burst.
//              - Else run the task by calling run() function for at most a quanta of the cpu burst and decrement task's cpu burst accordingly.
//              - Delete the task from the list by calling delete() function only if the task has finished running its needed cpu burst.
// 


#endif
