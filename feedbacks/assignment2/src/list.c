/**
 * @file list.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.0
 * @date October 9, 2025
 *
 * Implements the staff functions that provide functionality to the singly linked list data structure that holds all tasks.
 * - These staff functions include: insertion, deletion, creation of tasks, reading tasks from a file, and list traversal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/** @brief Inserts a new list node containing a task into a given list.
 * 
 *  Creates a new list node that holds the task to be inserted. This node will be attached to the end of
 *  the passed linked list. Tasks are held in list nodes and are always added at the end of the list.
 *  If the list is empty at the time of insertion, the newly created node will become the head.
 *
 *  @param list A pointer to the head of the linked list containing all tasks.
 *  @param task The task to be attached to a node and inserted into the list.
 *  @return Void.
 */

void insert(list_node_t** list, cpu_task_t* task) {
    // Create the node
    list_node_t* node = (list_node_t*)malloc(sizeof(list_node_t));
    node->task = task;
    node->next = NULL;

    // If list is empty
    if (*list == NULL) {
        *list = node;
        return;
    }

    // Otherwise, insert at end
    list_node_t* iterator = *list;

    while (iterator->next != NULL) {
        iterator = iterator->next;
    }

    iterator->next = node;
}

/** @brief Deletes a node from the list based on the given task.
 * 
 *  Searches the list for the node that contains the target task by comparing each node's task's name
 *  with the target task's name. When the target task is found within the list, the memory for the task name, task, and the list 
 *  node is freed. All pointers of the list are maintained, even if the current head of the linked list is deleted.
 *
 *  @param list A pointer to the head of the linked list containing all tasks.
 *  @param task The task attached to the node being removed from the list.
 *  @return Void.
 */

void delete(list_node_t** list, const cpu_task_t* task) {
    // If list is empty or no task, do nothing.
    if (list ==  NULL || task == NULL) {
        return;
    }


    // If head needs to be deleted
    list_node_t* iterator = *list;

    if (iterator->task->name == task->name) {
        *list = iterator->next;
        // Got name through strdup, have to free it as well.
        free(iterator->task->name); 
        free(iterator->task);
        free(iterator);
        return;
    }

    // Search for node with task (from 2nd node to end).
    list_node_t* prev = iterator;
    iterator = iterator->next;
    while (iterator->task->name != task->name) {
        prev = iterator;
        iterator = iterator->next;
        if (iterator == NULL) { // Reached the end of the list.
            printf("Task not found in list.\n");
            return;
        }

    }

    prev->next = iterator->next;   
    // Got name through strdup, have to free it as well.
    free(iterator->task->name); 
    free(iterator->task); 
    free(iterator);
}

/** @brief Creates a new CPU task based off of data, and inserts it into the list of tasks.
 * 
 *  Creates a new CPU task object and inserts the relevant data into the correct data fields.
 *  Then calls insert() to insert the task into the list.
 *
 *  @param name The name of the newly created task.
 *  @param arrival The arrival time of the newly created task.
 *  @param priority The priority level of the newly created task.
 *  @param burst The CPU burst time required to execute the newly created task.
 *  @param list A pointer to the head of the linked list containing all tasks.
 *  @return Void.
 */

void add(char* name, const int arrival, const int priority, const int burst, list_node_t** list) {
    cpu_task_t* task = (cpu_task_t*)malloc(sizeof(cpu_task_t));
    task->name = name;
    task->arrival = arrival;
    task->priority = priority;
    task->burst = burst;
    insert(list, task);
}

/** @brief Reads task data from a file and calls add() to create task objects and insert them into a linked list.
 * 
 *  Reads each line of the file and seperates each line by the comma "," character. Each line is expected to have
 *  one string for the task name, and three integers for the task arrival time, priority level, and CPU burst time.
 *  If the input file does not have the correct formatting, tasks will be parsed incorrectly by this function which will likely cause
 *  the scheduling to fail.
 *  - Make sure to have 1 task per line, separate the data fields by commas, and have the first data field be a string, followed by three integer data fields.
 *
 *  @param filename The name of the file to read the task information from.
 *  @param list A pointer to the head of the linked list containing all tasks.
 *  @return Void.
 */

void load(const char* filename, list_node_t** list) {
    FILE* file;
    char line[256];
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening the file for reading.\n");
        return;
    } 

    while (fgets(line, sizeof(line), file) != NULL) { // get info from each line of file and add task
        char* taskName = strdup(strtok(line, ","));
        int taskArrival = atoi(strtok(NULL, ","));
        int taskPriority = atoi(strtok(NULL, ","));
        int taskBurst = atoi(strtok(NULL, ","));
        add(taskName, taskArrival, taskPriority, taskBurst, list);
    }

    fclose(file);
}

/** @brief Traverses linearly through the list and displays each node's task's information to the terminal.
 * 
 *  Beginning from the head of the list, gets each list node's task and displays all of its information to the console on a separate line.
 *
 *  @param list The head of the linked list containing all tasks.
 *  @return Void.
 */

void traverse(list_node_t* list) {
    list_node_t* iterator = list;
    while (iterator != NULL) {
        cpu_task_t* task = iterator->task;
        printf(TASK_INFO_FORMAT, task->name, task->arrival, task->priority, task->burst);
        iterator = iterator->next;
    }
}

/** @brief Searches the list for the task that arrived first.
 * 
 *  Traverses the list linearly looking for the task that arrived first.
 *  The task that arrived first is the task with the lowest arrival time value. If two tasks
 *  have the lowest arrival time value, the one that comes first in the linked list is selected.
 *
 *  @param list The head of the linked list containing all tasks.
 *  @return The task with the lowest arrival time.
 */

cpu_task_t* get_first_arrived_task(list_node_t* list) {
    list_node_t* iterator = list;
    cpu_task_t* firstArrived = iterator->task;
    
    while (iterator != NULL) {
        if (iterator->task->arrival < firstArrived->arrival) {
            firstArrived = iterator->task;
        }
        iterator = iterator->next;
    }
    
    return firstArrived;
}

/** @brief Searches the list for the task with the shortest burst.
 * 
 *  Traverses the list linearly looking for the task with the shortest CPU burst time.
 *  The task with the shortest burst is the task with the lowest burst value. If two tasks
 *  have the lowest burst value, the one that comes first in the linked list is selected.
 *
 *  @param list The head of the linked list containing all tasks.
 *  @return The task with the lowest burst time.
 */

cpu_task_t* get_shortest_burst_task(list_node_t* list) {
    list_node_t* iterator = list;
    cpu_task_t* shortestBurst = iterator->task;
    
    while (iterator != NULL) {
        if (iterator->task->burst < shortestBurst->burst) {
            shortestBurst = iterator->task;
        }
        iterator = iterator->next;
    }
    
    return shortestBurst;
}

/** @brief Searches the list for the task with the highest priority.
 * 
 *  Traverses the list linearly looking for the highest priority task.
 *  The highest priority task is the task with the highest priority value. If two tasks
 *  have the highest priority value, the one that comes first in the linked list is selected.
 *
 *  @param list The head of the linked list containing all tasks.
 *  @return The task with the highest priority.
 */

cpu_task_t* get_highest_priority_task(list_node_t* list) {
    list_node_t* iterator = list;
    cpu_task_t* highestPriority = iterator->task;
    
    while (iterator != NULL) {
        if (iterator->task->priority > highestPriority->priority) {
            highestPriority = iterator->task;
        }
        iterator = iterator->next;
    }
    
    return highestPriority;
}
