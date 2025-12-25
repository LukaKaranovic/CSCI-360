/**
 * @file ta.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.1
 * @date November 10, 2025
 *
 * Implements log helper functions for TA actions and the TA thread simulation routine.
 *
 */
 
#include "ta.h"
#include "logger.h"
#include "config.h"
#include "queue.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 

/** @brief Simulates and logs a TA helping a student complete their assignment.
 *
 *  Uses mutex lock to access log and logs message of TA helping student. Uses sleep function
 *  of 'help_time' to simulate TA helping student.
 *
 *  @param ta_id The TA id of the TA providing help.
 *  @param st_id The student id of the student that is getting help.
 *  @param help_time The amount of time the TA helped the student.
 *  @return Void.
 */

void helping(const int ta_id, const int st_id, const int help_time) {
    char message[LOG_MESSAGE_MAX_LENGTH]; 
    sprintf(message, LOG_MESSAGE_FORMAT_HELPING, ta_id, st_id, help_time);
    
    pthread_mutex_lock(&mutex_lock_log);
    log_message(LOG_LABEL_HELPING, message);
    pthread_mutex_unlock(&mutex_lock_log);

    sleep(help_time);
}

/** @brief Simulates and logs a TA sleeping because there are no students to help.
 *
 *  Uses mutex lock to access log and logs message of TA sleeping.
 *
 *  @param ta_id The TA id of the TA providing help.
 *  @return Void.
 */

void sleeping(const int ta_id) {
    char message[LOG_MESSAGE_MAX_LENGTH];
    sprintf(message, LOG_MESSAGE_FORMAT_SLEEPING, ta_id);
    
    pthread_mutex_lock(&mutex_lock_log);
    log_message(LOG_LABEL_SLEEPING, message);
    pthread_mutex_unlock(&mutex_lock_log);
}

/** @brief TA thread function. Runs simulation for a single TA.
 *
 *  TA will run until all students have completed their assignment (meaning all students have received adequate help and
 *  the student threads have exited). A TA will help the next student that is ready in the queue. A TA can noly help one
 *  student at a time. A TA will sleep if there are no students in the queue. Uses a semaphore to signal to students that it 
 *  is able to help them.
 *
 *  @param param Pointer to the TA id given to this TA thread.
 *  @return Pointer of any type.
 */

void *run_ta(void *param) {
    int ta_id = *(int*)param;
    while (1) {
        pthread_mutex_lock(&mutex_lock_queue);
        int q_size = queue_size();

        if (q_size == 0) {
            pthread_mutex_unlock(&mutex_lock_queue);
            sleeping(ta_id);
            sem_wait(&student_sem);
        } else {
            int st_id = dequeue();
            pthread_mutex_unlock(&mutex_lock_queue);
            helping(ta_id, st_id, (rand() % MAX_PROGRAM_TIME) + 1); // To get range between 1 and MAX_PROGRAM_TIME
            sem_post(&ta_sem);
            sem_wait(&student_sem);
        }
    }
    return NULL;
}

