/**
 * @file logger.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.0
 * @date November 2, 2025
 *
 * This file implements staff functions for the log. The log records all events that take place in a simulation.
 * Staff functions include: writing a log entry to the log, writing the logs to a file, and displaying the logs on the console.
 *
 */
 
#include "logger.h"
#include "config.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

char logs[LOG_MAX_SIZE][LOG_MESSAGE_MAX_LENGTH];    // Array to hold log messages in memory
int log_size = 0;                                   // The actual number of log messages in the array

/** @brief Adds a single line message to the log as a log entry.
 * 
 *  Takes a message, formats it, and appends it to the log, along with its corresponding timestamp.
 *
 *  @param label Format string that specifies the log's entry format.
 *  @param message The message to be added to the log.
 *  @return Void.
 */

void log_message(const char* label, const char* message) {
    // Get current time and strip newline
    time_t seconds;
    time(&seconds);
    char* current_time = ctime(&seconds);
    current_time[strlen(current_time) - 1] = '\0';

    // Format current log entry and increment size.
    sprintf(logs[log_size], LOG_ENTRY_FORMAT, current_time, label, message);
    log_size++;
}

/** @brief Displays every log entry on the console.
 *
 *  @return Void.
 */

void log_show() {
    for (int i = 0; i < log_size; i++) {
        printf("%s\n", logs[i]);
    }
}

/** @brief Writes every log entry into the log file. The log file is specified by LOG_FILE_PATH in 'include/config.h'.
 *
 *  @return Void.
 */

void log_save() {
    FILE* log_file = fopen(LOG_FILE_PATH, "w");
    
    if (log_file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < log_size; i++) {
        fprintf(log_file, "%s\n", logs[i]);
    }

    fclose(log_file);
}
