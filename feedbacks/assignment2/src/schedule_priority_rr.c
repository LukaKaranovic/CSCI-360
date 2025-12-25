/**
 * @file schedule_priority_rr.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.0
 * @date October 9, 2025
 *
 * Implements the schedule function which follows the priority round robin CPU scheduling algorithm for a list of tasks.
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "schedule.h"
#include "list.h"
#include "cpu.h"
#include "task.h"

/** @brief Schedules and runs the priority round robin (PR-RR) algorithm on a list of CPU tasks.
 * 
 *  The algorithm first takes the input list of tasks and sorts them into separate lists of tasks based on priority levels.
 *      - For example, all tasks of priority level 9 will be in one list, and all tasks of priority level 7 will be in another list.
 *  
 *  The higher the priority number, the higher the priority. Therefore, the algorithm will perform a round robin on each
 *  priority level list until that list is empty. This round robin executes every CPU task in the list for a fixed burst of 
 *  time (time quantum defined in 'cpu.h'). Each time it does this, it is a "round". If there is one task left in the priority list,
 *  the task will run for its remaining burst in one round, instead of the time quantum. The function will execute rounds of tasks until there are 
 *  no tasks left in the list.
 *
 *  Once all priority level lists have been scheduled and executed, the original list's nodes will be cleared from memory and the algorithm will finish.
 *
 *  @param list A pointer to the head of the linked list containing all tasks.
 *  @return Void.
 */

void schedule(list_node_t** list) {
    list_node_t* priorityLists[MAX_PRIORITY - MIN_PRIORITY + 1] = {NULL};

    // Sort current list into priority level lists.
    list_node_t* iterator = *list;
    while (iterator != NULL) {
        insert(&priorityLists[(iterator->task->priority)-MIN_PRIORITY], iterator->task);
        iterator = iterator->next;
    }

    // Perform round robin on each priority level, from max to min.
    for (int i = MAX_PRIORITY-1; i >= MIN_PRIORITY-1; i--) {
        int round = 1;
        if (priorityLists[i] != NULL) {
            printf("--------------- Priority level: %d ---------------\n", i+1);
        }
        while (priorityLists[i] != NULL) {
            printf("\tRound %d\n", round);

            // If 1 task left in LL
            if (priorityLists[i]->next == NULL) {
                run(priorityLists[i]->task, priorityLists[i]->task->burst);
                priorityLists[i]->task->burst = 0;
                delete(&priorityLists[i], priorityLists[i]->task);
                priorityLists[i] = NULL;
            }

            iterator = priorityLists[i];

            // Handle a round in round robin when more than 1 task left in LL
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
                    delete(&priorityLists[i], task);                    
                }
            }
            round++;
        }
    }

    // Delete all remaining copies of nodes (tasks were already freed).
    iterator = *list;
    while (iterator != NULL) {
        list_node_t* temp = iterator;
        iterator = iterator->next;
        free(temp);
    }
}