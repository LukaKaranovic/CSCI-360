/**
 * @file scheduler.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.0
 * @date October 9, 2025
 *
 * Implements the CPU scheduler. This is the main routine for this application and will read a file of CPU tasks,
 * load them into a list, and then schedule and run them based on the given scheduling algorithm.
 */
 
#include <stdio.h>

#include "list.h"
#include "schedule.h"

list_node_t *list = NULL;  	//Global pointer variable to refer the head of the task list

/** @brief Runs the main routine of a CPU scheduler.
 * 
 *  The user must execute the binary executable based on the scheduling algorithm they want to use, and a file containing all CPU tasks formatted
 *  correctly (1 task per line, 1 string field, 3 int fields all separated by commas). The scheduler will load the tasks from the given file
 *  into a list, and then traverse the list to display all tasks that were loaded. The tasks will then be scheduled and run by the CPU until
 *  all tasks have been executed successfully. Then the program will terminate.
 *
 *  @param argc The number of command line arguments provided by the user.
 *  @param argv The list of command line arguments provided by the user.
 *  @return 0 if ran and exited program successfully. Otherwise, exited the program due to some errors while running the program.
 */

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("CPU Task filename was not given, proper command use is: make run <filename>");
        return 2;
    } else if (argc > 2) {
        printf("Too many arguments were provided, proper command use is make run <filename>");
        return 2;
    }

    load(argv[1], &list);
    traverse(list);
    schedule(&list);
    return 0;
}
