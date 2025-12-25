/**
 * @file cpu.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.0
 * @date October 9, 2025
 *
 * Implements the CPU, which simulates executing a task and displaying that it ran to the terminal.
 */
 
#include "cpu.h"
#include <stdio.h>

/** @brief Executes a task by displaying its information to the terminal.
 *
 *  @param task The CPU task being executed.
 *  @param slice The time slice the CPU is being executed for, in time units.
 *  @return Void.
 */

void run(const cpu_task_t *task, const int slice) {
    printf(TASK_RUN_INFO_FORMAT, task->name, task->arrival, task->priority, task->burst, slice);
}
