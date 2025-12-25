/**
 * @file logger.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version 1.0.1
 * @date May 22, 2024
 *
 * Defines the functions for simulator logger that will be used 
 * by TAs and Students to log their events.
 */

#ifndef __LOGGER_HEADER__
#define __LOGGER_HEADER__


#define LOG_MESSAGE_MAX_LENGTH 256


#define LOG_ENTRY_FORMAT "%s: %s -  %s"

#define LOG_MESSAGE_FORMAT_SLEEPING "TA %d is waiting for students"
#define LOG_MESSAGE_FORMAT_HELPING  "TA %d is helping Student %d for %d seconds"
#define LOG_MESSAGE_FORMAT_PROGRAMMING "Student %d is programming for %d seconds"
#define LOG_MESSAGE_FORMAT_WAITING "Student %d takes a seat, Total waiting %d"
#define LOG_MESSAGE_FORMAT_NO_WAITING_ROOM "Student %d does not get room, Total waiting %d"
#define LOG_MESSAGE_FORMAT_GETTING_HELP "Student %d is getting help"


#define LOG_LABEL_SLEEPING "SLEEPING"
#define LOG_LABEL_HELPING "HELPING"
#define LOG_LABEL_PROGRAMMING "PROGRAMMING"
#define LOG_LABEL_WAITING "WAITING"
#define LOG_LABEL_GETTING_HELP "GETTING HELP"
#define LOG_LABEL_NO_WAITING_ROOM "NO WAITING ROOM"


/*
 * You will need to declare global variables for logs and the size of the logs 
 * in your logger.c file as follows:
 *
 *	char logs[LOG_MAX_SIZE][LOG_MESSAGE_MAX_LENGTH];	//Array to hold log messages in memory
 *	int log_size = 0;									//The actual number of log messages in the array
 *
 * The above variables are not declared here in this header file to avoid multiple declarations
 * of them in multiple source files where logger.h header file is being included.
 */



void log_message(const char* label, const char* message);
//Determine current time by calling time() library  function.
//Convert current time into human readable string by calling ctime() library function.
//Remove the newline character inserted by ctime() function from the end of current time human readable string.
//Format log entry  logs[log_size] calling sprintf() library function and using LOG_ENTRY_FORMAT, current time, 'label', and 'message'
//Increment log_size to update the next available log entry in the logs.



void log_show();
//Display all the log entries from the log sequence.
//You can use printf() library function.


void log_save();
//Save all the log entries from the log sequence into the file specified by LOG_FILE_PATH.
//You can use fopen(), fprintf(), and fclose() library functions.




#endif
