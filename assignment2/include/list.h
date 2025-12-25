/**
 * @file list.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version 1.0.1
 * @date May 21, 2024
 *
 * Defines the data structure and the functions for a single linked list of cpu tasks.
 *
 */



#ifndef __LIST_HEADER__
#define __LIST_HEADER__

#include "task.h"

/*
 * Data structure for single linked list node or element
 */
typedef struct list_node {
	cpu_task_t* task;
	struct list_node* next;
} list_node_t;



void insert(list_node_t** list, cpu_task_t* task);
//Parameter 'list' is a pointer of a 'list_node_t' pointer, i.e., a pointer of a pointer.
//This pointer points to the fist node of the list, it could be NULL if there is no node already inserted in the list.
//Allocate memory for a new list node using malloc() function and assign its task to the given task.
//Add the new list node at the end of the list.


void delete(list_node_t** list, const cpu_task_t* task);
//Parameter 'list' is a pointer of a 'list_node_t' pointer, i.e., a pointer of a pointer.
//This pointer points to the fist node of the list, it could be NULL if there is no node already inserted in the list.
//Do nothing if the list is empty or the task pointer is NULL.
//Search the task in the list by task name.
//If the task is found remove the corresponding list node from the list by manipulating appropriate pointers.
//Release memory from both the task and the node of the removed list node using free() function.
//Remember the task can be found at the first node, at a middle node, or at the last
//node, i.e., you have three cases to deal with.



void add(char* name, const int arrival, const int priority, const int burst, list_node_t** list);
//Allocate memory by calling malloc() or calloc() library function for a new task.
//Assign name, priority, and burst to the new task.
//Insert the task into the list by calling your insert() function.


void load(const char* filename, list_node_t** list);
//Open the task file specified by the filename in read only mode by calling fopen() library function.
//Read each task from each line from the file. You can use fgets() or getline() library function for this.
//Extract the comma separated name, priority, and burst of the task from each line using 
//strtok() or strsep() and atoi() library functions.
//Add the task name, priority, and burst to the list by calling your add() function.
//Close the file once all tasks are added to the list using fclose() function.



void traverse(list_node_t* list);
//Loop through the task list.
//Display each task in a separate line as follows using TASK_INFO_FORMAT in printf() function:
//	[T1] [4] [20]
//	[T2] [3] [25]
//	[T3] [3] [25]
//	[T4] [5] [15]
//	[T5] [5] [20]
//	[T6] [1] [10]
//	[T7] [3] [30]
//	[T8] [10] [25]


cpu_task_t* get_first_arrived_task(list_node_t* list);
cpu_task_t* get_shortest_burst_task(list_node_t* list);
cpu_task_t* get_highest_priority_task(list_node_t* list);


#endif
