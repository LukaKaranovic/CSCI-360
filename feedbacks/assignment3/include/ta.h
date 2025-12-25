/**
 * @file ta.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version 1.0.1
 * @date May 22, 2024
 *
 * Defines the functions required to simulate TA.
 *
 */



#ifndef __TA_HEADER__
#define __TA_HEADER__

#include <pthread.h>
#include <semaphore.h>

/* 
 * Following external global variables has already been deaclared in simulator.h
 * and will be used by run_ta() function.
 */
extern pthread_mutex_t mutex_lock_queue;
extern pthread_mutex_t mutex_lock_log;
extern sem_t ta_sem;
extern sem_t student_sem;


void helping(const int ta_id, const int st_id, const int help_time);
//Log an entry into the logger with a log message indicating that the TA is helping a student
//Format a message calling sprintf() library function and using LOG_MESSAGE_FORMAT_HELPING, 'ta_id', 'st_id', and 'helptime'.
//Call log_message() function using LOG_LABEL_HELPING and the formatted message.
//Guard the log with 'mutex_lock_log' by calling pthread_mutex_lock()
//and pthread_mutex_unlock() library functions on 'mutex_lock_log' before and after
//calling log_message() function respectively.
//Simulate helping the student by calling sleep() system call.


void sleeping(const int ta_id);
//Log an entry into the logger with a log message indicating that the TA is sleeping
//Format a message calling sprintf() library function and using LOG_MESSAGE_FORMAT_SLEEPING, and 'ta_id'.
//Call log_message() function using LOG_LABEL_SLEEPING and the formatted message.
//Guard the log with 'mutex_lock_log' by calling pthread_mutex_lock()
//and pthread_mutex_unlock() library functions on 'mutex_lock_log' before and after
//calling log_message() function respectively.



void *run_ta(void *param);
//Do the followings in an infinite loop.
//Acquire 'mutex_lock_queue' by calling pthread_mutex_lock()
//library function on the mutex lock in order to check the current waiting queue size by calling
//queue_size() function from queue.h.
//If the the queue size is zero
//  Release 'mutex_lock_queue' by calling pthread_mutex_unlock() function.
//	Log an entry into the logger with a log message indicating that the TA is sleeping(waiting)
//  by calling sleeping() function.
//	Wait for a student to show up by calling sem_wait() system call on 'student_sem' semaphore.
//
//Else (the queue size is greater than zero)
//	Dequeue the student by calling dequeue() from queue.h.
//  Release 'mutex_lock_queue' by calling pthread_mutex_unlock() function.
//	Help the student for a random time by calling helping() function.
//  You can call random() library function to generate random help time.
//	After helping is complete, notify the waiting student that the TA is ready 
//  to help by calling sem_post() system call on 'ta_sem' semaphore.
//	Wait for the student to come forward to get help by calling sem_wait()
//  systemt call on 'student_sem' semaphore.



#endif
