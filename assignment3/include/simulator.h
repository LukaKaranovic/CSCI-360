/**
 * @file simulator.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version 1.0.1
 * @date May 22, 2024
 *
 * Defines the functions for TA-Student simulator.
 *
 */



#ifndef __SIMULATOR_HEADER__
#define __SIMULATOR_HEADER__

#include <pthread.h>
#include <semaphore.h>
#include "config.h"


int student_id[NUMBER_OF_STUDENTS];    	//Numeric ids of the students


int ta_id[NUMBER_OF_TAS];		//Numeric ids for tas


pthread_t tas[NUMBER_OF_TAS];		//Thread identifiers for TA threads


pthread_t students[NUMBER_OF_STUDENTS];	//Thread identifiers for the STUDENT threads


sem_t student_sem;			//Semaphore on which the TAs will wait and be waked up by STUDENTs 


sem_t ta_sem;				//Semaphore on which the STUDENTSs will wait and be waked up by TAs


pthread_mutex_t mutex_lock_queue;	//Mutex lock for the shared queue


pthread_mutex_t mutex_lock_log; 	//Mutex lock for the shared logger


void init();
//Initialize mutex locks by calling pthread_mutex_init() library function on each lock.
//Initialize both student_sem and ta_sem semaphores by calling sem_init() system call on each semaphore.
//Initializes all student ids
//Initialize all TA ids
//Initialize random number generator seed by calling srandom() library function
//by passing current time. You can call time() library function to get current time. 


void cleanup();
//Destroy mutex locks by calling pthread_mutex_destroy() library function on each lock.
//Destroy both student_sem and ta_sem semaphores by calling sem_destroy() library function on each semaphore.


void create_tas();
//Create TA threads by calling pthread_create() library function with run_ta() function
//as the thread function.


void create_students();
//Create all STUDENT threads by calling pthread_create() library function with run_student() function
//as the thread function.


int main();
//Call init()
//Call create_tas()
//Call create_students()
//Join on student threads by calling pthread_join() library function.
//Cancel ta threads after all student threads have been finished by caling pthread_cancel() library function.
//Call log_show() function.
//Call log_save() function.
//Call cleanup() function.


#endif


