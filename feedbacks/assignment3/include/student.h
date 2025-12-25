/**
 * @file student.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version 1.0.1
 * @date May 22, 2024
 *
 * Defines the functions required to simulate student.
 *
 */




#ifndef __STUDENT_HEADER__
#define __STUDENT_HEADER__

#include <pthread.h>
#include <semaphore.h>

//different states of a student
typedef enum {PROGRAMMING, WAITING, GETTING_HELP, UNKNOWN} student_state_t;


/* 
 * Following external global variables has already been deaclared in simulator.h
 * and will be used by run_student() function.
 */
extern pthread_mutex_t mutex_lock_queue;
extern pthread_mutex_t mutex_lock_log;
extern sem_t ta_sem;
extern sem_t student_sem;



void programming(const int student_id, const int programing_time);
//Log an entry into the logger with a log message indicating that the student is programming
//Format a message calling sprintf() library function and using LOG_MESSAGE_FORMAT_PROGRAMMING, 'student_id' and 'programming_time'.
//Call log_message() function using LOG_LABEL_PROGRAMMING and the formatted message.
//Guard the log with 'mutex_lock_log' by calling pthread_mutex_lock()
//and pthread_mutex_unlock() library functions on 'mutex_lock_log' before and after
//calling log_message() function respectively.
//Simulate programming by calling sleep() system call.


void waiting(const int student_id, const int queue_size);
//Log an entry into the logger with a log message indicating that the student is waiting
//Format a message calling sprintf() library function and using LOG_MESSAGE_FORMAT_WAITING, 'student_id' and 'queue_size'.
//Call log_message() function using LOG_LABEL_WAITING and the formatted message.
//Guard the log with 'mutex_lock_log' by calling pthread_mutex_lock()
//and pthread_mutex_unlock() library functions on 'mutex_lock_log' before and after
//calling log_message() function respectively.


void no_waiting_room(const int student_id, const int queue_size);
//Log an entry into the logger with a log message indicating that the student is not waiting due to no room in the waiting room.
//Format a message calling sprintf() library function and using LOG_MESSAGE_FORMAT_NO_WAITING_ROOM, 'student_id' and 'queue_size'.
//Call log_message() function using LOG_LABEL_NO_WAITING_ROOM and the formatted message.
//Guard the log with 'mutex_lock_log' by calling pthread_mutex_lock()
//and pthread_mutex_unlock() library functions on 'mutex_lock_log' before and after
//calling log_message() function respectively.


void getting_help(const int student_id);
//Log an entry into the logger with a log message indicating that the student is getting help
//Format a message calling sprintf() library function and using LOG_MESSAGE_FORMAT_GETTING_HELP, 'student_id' and 'queue_size'.
//Call log_message() function using LOG_LABEL_GETTING_HELP and the formatted message.
//Guard the log with 'mutex_lock_log' by calling pthread_mutex_lock()
//and pthread_mutex_unlock() library functions on 'mutex_lock_log' before and after
//calling log_message() function respectively.


void *run_student(void *param);
//Start with UNKNOWN state
//Check the number of loops this student has completed.
//If number of loops does not exceed MAX_NUMBER_OF_STUDENT_CYCLES and the state is not
//WAITING starts programming for a random amount of time by calling programming() function and
//sets the sate PROGRAMMING. You can use random() library function to generate the random programming time.
//After finishing the programming, acquire 'mutex_lock_queue' by calling pthread_mutex_lock()
//library function on the mutex lock in order to check the current waiting queue size by calling
//queue_size() function from queue.h.
//If the the queue size is less than NUMBER_OF_SEATS
//	Enqueues itself into the queue by calling enqueue() function from queue.h and sets the state WAITING.
//	Release 'mutex_lock_queue' by calling pthread_mutex_unlock() function. 
//	Make sure mutex lock does not cause deadlock in your assignment.
//	Log an entry into the logger with a log message indicating that the student is waiting by calling
//  waiting() function.
//	Notify the TA using a semaphore that this student is waiting to get help. Call sem_post()
//  system call on 'student_sem' semaphore to do this.
//	Wait for the TA to get help using a semaphore. Call sem_wait() system call on 'ta_sem' 
//  semaphore to do this.
//	When waiting is over and TA starts helping, set the state to GETTING_HELP.
//	Log an entry into the logger with a log message indicating that the student is getting help
//	by calling getting_help() function.
//	Increment the number of loop the student has completed.
//
//Else (the queue size is not less than NUMBER_OF_SEATS) 
//  Release 'mutex_lock_queue' by calling pthread_mutex_unlock() function.
//	Log an entry into the logger with a log message indicating that there is no room to wait by calling
//  no_waitting_room() function.
//	Don't increment the number of loop the student has completed.
//
//Loop back.


#endif
