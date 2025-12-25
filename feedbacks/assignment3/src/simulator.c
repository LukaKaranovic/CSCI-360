/**
 * @file simulator.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.0
 * @date November 9, 2025
 *
 * Implements the main routine where the simulation is run. Also implements helper functions to aid the simulation process.
 *
 */
 
#include "simulator.h"
#include "ta.h"
#include "student.h"
#include "logger.h"

#include <stdlib.h>
#include <time.h>


/** @brief Initializes various data structures and data used in the simulation. Executed before starting simulation.
 *
 *  Initializes both mutex locks used to avoid race condition. Then initializes sempahores used for resource
 *  management. Then initializes all student and ta id data. Finally, initializes the rng seed by using the current time.
 * 
 *  @return Void.
 */

void init() {
    // Mutex lock initialization
    pthread_mutex_init(&mutex_lock_queue, NULL);	
    pthread_mutex_init(&mutex_lock_log, NULL); 	

    // Semaphore intialization
    sem_init(&student_sem, 0, 0);			
    sem_init(&ta_sem, 0, NUMBER_OF_TAS);				

    // Student ID initialization
    for (int i = 0; i < NUMBER_OF_STUDENTS; i++) {
        student_id[i] = i+1;
    }

    // TA ID initialization
    for (int i = 0; i < NUMBER_OF_TAS; i++) {
        ta_id[i] = i+1;
    }

    // Simulation RNG seed initialization
    srandom(time(NULL));
}

/** @brief Cleans up various data structures used to help simulate. Executed after finishing simulation.
 *
 *  Destroys both mutexes and semaphores used in the simulation.
 * 
 *  @return Void.
 */

void cleanup() {
    // Mutex lock destruction
    pthread_mutex_destroy(&mutex_lock_log);
    pthread_mutex_destroy(&mutex_lock_queue);

    // Semaphore destruction
    sem_destroy(&student_sem);
    sem_destroy(&ta_sem);
}


/** @brief Initializes a thread for each TA in the simulation.
 *
 *  Number of TAs is configured in 'include/config.h' file.
 * 
 *  @return Void.
 */

void create_tas() {
    // TA thread initialization
    for (int i = 0; i < NUMBER_OF_TAS; i++) {
        pthread_create(&tas[i], NULL, &run_ta, &ta_id[i]);
    }
}

/** @brief Initializes a thread for each student in the simulation.
 *
 *  Number of students is configured in 'include/config.h' file.
 * 
 *  @return Void.
 */

void create_students() {
    // Student thread initialization
    for (int i = 0; i < NUMBER_OF_STUDENTS; i++) {
        pthread_create(&students[i], NULL, &run_student, &student_id[i]);
    }
}

/** @brief Sets up and runs the simulation. Writes events to log, and cleans up.
 *
 *  First, sets up data structures, data, and threads for simulation. Then, each thread runs its routine in
 *  the simulation. After the simulation is done, the log is displayed and then written to the log file. 
 *  Finally, cleanup routine is called.
 * 
 *  @return 0 if exited normally. Non-zero if any errors occured during execution.
 */

int main() {
    init();
    create_tas();
    create_students();

    // Wait for all student threads to finish
    for (int i = 0; i < NUMBER_OF_STUDENTS; i++) {
        pthread_join(students[i], NULL);
    }

    // Cancel all TA threads
    for (int i = 0; i < NUMBER_OF_TAS; i++) {
        pthread_cancel(tas[i]);
        pthread_join(tas[i], NULL);
    }

    log_show();
    log_save();
    cleanup();

    return 0;
}

