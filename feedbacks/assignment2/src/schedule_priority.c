/**
 * @file schedule_priority.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.0
 * @date October 9, 2025
 *
 * Implements the schedule function which follows the priority CPU scheduling algorithm for a list of tasks.
 */

#include <stdlib.h>

#include "schedule.h"
#include "list.h"
#include "cpu.h"

/** @brief Schedules and runs the priority (PR) algorithm on a list of CPU tasks.
 * 
 *  The higher the priority number, the higher the priority. Therefore, the algorithm will execute all tasks of the highest
 *  priority level first, and make its way down to the lowest priority level. Within each priority level, tasks are executed in order of which
 *  task was added to the list first.
 *
 *  @param list A pointer to the head of the linked list containing all tasks.
 *  @return Void.
 */

void schedule(list_node_t** list) {
    while (*list != NULL) {
        cpu_task_t* task = get_highest_priority_task(*list);
        run(task, task->burst);
        delete(list, task);
    }
}
