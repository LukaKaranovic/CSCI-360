/**
 * @file schedule_fcfs.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.0
 * @date October 9, 2025
 *
 * Implements the schedule function which follows the first come first serve CPU scheduling algorithm for a list of tasks.
 */

#include <stdlib.h>

#include "schedule.h"
#include "list.h"
#include "cpu.h"

/** @brief Schedules and runs the first come first serve (FCFS) algorithm on a list of CPU tasks.
 * 
 *  The algorithm selects the task with the earliest arrival time in the list. If two tasks have the same arrival time, 
 *  the task that was inserted into the list (and appears earlier) is selected first. Once it selects a task,
 *  it runs the task and then removes it from the list, as the task has been completed.
 *  This process repeats until the list of tasks is empty, meaning every task has been executed.
 *
 *  @param list A pointer to the head of the linked list containing all tasks.
 *  @return Void.
 */

void schedule(list_node_t** list) {
    while(*list != NULL) {
        cpu_task_t* task = get_first_arrived_task(*list);
        run(task, task->burst);
        delete(list, task);
    }
}
