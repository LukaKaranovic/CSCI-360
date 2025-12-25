/**
 * @file config.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version 1.0.0
 * @date December 03, 2020
 *
 * Defines simulation configuration parameter values as pre-processor macros
 */
 

#ifndef __CONFIG_HEADER__
#define __CONFIG_HEADER__



/*
 * Configuration parameters related to TA
 */

#define NUMBER_OF_TAS 2 // number of teaching assiatants in the simulation
#define MAX_HELP_TIME 5 // maximum help time of a teaching assistant to a student



/*
 * Configuration parameters related to students
 */
#define NUMBER_OF_STUDENTS 10 // number of students in the simulation
#define NUMBER_OF_STUDENT_CYCLES 5 // number of times a student will loop through the simulation
#define MAX_PROGRAM_TIME 5  // maximum time (in seconds) for a STUDENT to program 


/*
 * Configuration parameter related to waiting room
 */
#define NUMBER_OF_SEATS	3 // the number of available seats to sit in for seeking help


/*
 * Configuration parameters related to logger
 */
#define LOG_MAX_SIZE NUMBER_OF_STUDENTS*NUMBER_OF_STUDENT_CYCLES*NUMBER_OF_TAS*10 //maximum log size

#define LOG_FILE_PATH "resource/logs.txt" // the path of the logger file 


#endif
