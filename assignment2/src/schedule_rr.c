/**
 * @file schedule_rr.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.0
 * @date October 9, 2025
 *
 * Implements the schedule function which follows the round robin CPU scheduling algorithm for a list of tasks.
 */

#include <stdio.h>

#include "schedule.h"
#include "list.h"
#include "cpu.h"

/** @brief Schedules and runs the round robin (RR) algorithm on a list of CPU tasks.
 * 
 *  The algorithm executes every CPU task in the list for a fixed burst of time (time quantum defined in 'cpu.h').
 *  Each time it does this, it is a "round". The function will execute rounds of tasks until there are no tasks 
 *  left in the list.
 *
 *  @param list A pointer to the head of the linked list containing all tasks.
 *  @return Void.
 */

void schedule(list_node_t** list) {
    int round = 1;
    
    while(*list != NULL) {
        printf("\n\tRound %d\n", round);
        list_node_t* iterator = *list;
        while (iterator != NULL) {
            cpu_task_t* task = iterator->task;
        
            if (task->burst < QUANTUM) {
                run(task, task->burst);
                task->burst = 0;
            } else {
                run(task, QUANTUM);
                task->burst -= QUANTUM;
            }
                
            iterator = iterator->next;
            if (task->burst <= 0) {
                delete(list, task);
            }
        }
        round++;
    }
}