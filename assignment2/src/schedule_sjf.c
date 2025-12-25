/**
 * @file schedule_sjf.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.0
 * @date October 9, 2025
 *
 * Implements the schedule function which follows the shortest job first CPU scheduling algorithm for a list of tasks.
 */
 
#include <stdlib.h>

#include "schedule.h"
#include "list.h"
#include "cpu.h"

/** @brief Schedules and runs the shortest job first (SJF) algorithm on a list of CPU tasks.
 * 
 *  The algorithm selects the task with the shortest CPU burst time in the list. Once it selects it,
 *  it runs the task and then removes it from the list, as the task has been completed.
 *  This process repeats until the list of tasks is empty, meaning every task has been executed.
 *
 *  @param list A pointer to the head of the linked list containing all tasks.
 *  @return Void.
 */

void schedule(list_node_t** list) {
    while(*list != NULL) {
        cpu_task_t* task = get_shortest_burst_task(*list);
        run(task, task->burst);
        delete(list, task);
    }
}
