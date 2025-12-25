/**
 * @file student.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.1
 * @date November 10, 2025
 * Implements log helper functions for student actions and the student thread simulation routine.
 *
 */
 
#include "student.h"
#include "logger.h"
#include "config.h"
#include "queue.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 

/** @brief Simulates and logs a student working on their assignment by programming.
 *
 *  Uses mutex lock to access log and logs message of student programming.
 *  Uses sleep() function to sleep 'programing_time' seconds to simulate the programming.
 *
 *  @param student_id The student id of the student that is programming.
 *  @param programing_time The time that the student is programming for.
 *  @return Void.
 */

void programming(const int student_id, const int programing_time) {
    char message[LOG_MESSAGE_MAX_LENGTH];
    sprintf(message, LOG_MESSAGE_FORMAT_PROGRAMMING, student_id, programing_time);
    
    pthread_mutex_lock(&mutex_lock_log);
    log_message(LOG_LABEL_PROGRAMMING, message);
    pthread_mutex_unlock(&mutex_lock_log);

    sleep(programing_time);
}

/** @brief Simulates and logs a student waiting to get help on their assignment.
 *
 *  Uses mutex lock to access log and logs message of student waiting.
 *
 *  @param student_id The student id of the student that is waiting.
 *  @param queue_size The size of the queue at the time the student starts waiting.
 *  @return Void.
 */

void waiting(const int student_id, const int queue_size) {
    char message[LOG_MESSAGE_MAX_LENGTH];
    sprintf(message, LOG_MESSAGE_FORMAT_WAITING, student_id, queue_size);
    
    pthread_mutex_lock(&mutex_lock_log);
    log_message(LOG_LABEL_WAITING, message);
    pthread_mutex_unlock(&mutex_lock_log);
}

/** @brief Simulates and logs a student checking the queue to get help on the assignment, and seeing the queue is full.
 *
 *  Uses mutex lock to access log and logs message of student realising there is no waiting room.
 *
 *  @param student_id The student id of the student that is waiting.
 *  @param queue_size The size of the queue at the time the student checks it.
 *  @return Void.
 */

void no_waiting_room(const int student_id, const int queue_size) {
    char message[LOG_MESSAGE_MAX_LENGTH];
    sprintf(message, LOG_MESSAGE_FORMAT_NO_WAITING_ROOM, student_id, queue_size);
    
    pthread_mutex_lock(&mutex_lock_log);
    log_message(LOG_LABEL_NO_WAITING_ROOM, message);
    pthread_mutex_unlock(&mutex_lock_log);
}

/** @brief Simulates and logs a student getting help from a TA so they can complete their assignment.
 *
 *  Uses mutex lock to access log and logs message of student getting help from TA.
 *
 *  @param student_id The student id of the student that is getting help.
 *  @return Void.
 */

void getting_help(const int student_id) {
    char message[LOG_MESSAGE_MAX_LENGTH];
    sprintf(message, LOG_MESSAGE_FORMAT_GETTING_HELP, student_id);
    
    pthread_mutex_lock(&mutex_lock_log);
    log_message(LOG_LABEL_GETTING_HELP, message);
    pthread_mutex_unlock(&mutex_lock_log);
}

/** @brief Student thread function. Runs simulation for a single student.
 *
 *  Student will run until their loops equal their NUMBER_OF_STUDENT_CYCLES, when this has happened, it means the
 *  student has gotten enough help from the TAs to complete their assignment. Loops will only be incremented once if
 *  if the student gets help. Otherwise, the student will try and get help by checking the queue, and waiting if there is room.
 *  If there is no room, the student will try to program for some time and then try to wait in the queue again.
 *
 *  @param param Pointer to the student id given to this student thread.
 *  @return Pointer of any type.
 */

void *run_student(void *param) {
    int st_id = *(int*)param;
    int loops = 0;
    student_state_t student_state = UNKNOWN;
    
    while (loops < NUMBER_OF_STUDENT_CYCLES) {

        if (student_state != WAITING) {
            student_state = PROGRAMMING;
            programming(st_id, (rand() % MAX_PROGRAM_TIME) + 1); // To get range between 1 and MAX_PROGRAM_TIME
        }

        pthread_mutex_lock(&mutex_lock_queue);
        int q_size = queue_size();
        if (q_size < NUMBER_OF_SEATS) {
            enqueue(st_id);
            student_state = WAITING;
            pthread_mutex_unlock(&mutex_lock_queue);
            waiting(st_id, q_size);
            sem_post(&student_sem);
            sem_wait(&ta_sem);

            student_state = GETTING_HELP;
            getting_help(st_id);
            loops++; // Only increment loop if TA is helping student.
        } else {
            pthread_mutex_unlock(&mutex_lock_queue);
            no_waiting_room(st_id, q_size);
        }
    }
    pthread_exit(NULL);
}
