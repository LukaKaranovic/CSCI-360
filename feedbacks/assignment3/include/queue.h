/**
 * @file queue.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version 1.0.1
 * @date May 22, 2024
 *
 * Defines the functions for a queue using double linked list.
 *
 *
 * Implementation of this header file will be an implementation of Queue abstract
 * data type using a double-way-link-list.
 * When a student wants to wait to get help from the TA, it enqueues
 * itself into the queue. A student must check the queue size against the maximum number
 * of seats available in the TA office before it enqueues itself into the queue.
 * Queue itself is of unlimited size.
 * When the TA is ready to help a waiting student, it dequeues the student
 * from the queue.
 *
 */

#ifndef __QUEUE_HEADER__
#define __QUEUE_HEADER__

/*
 * Data structure for a queue node
 */
typedef struct queue_node {
	int id;
	struct queue_node* next;
} queue_node_t;

/*
 * You will need to declare global variables for the head, tail, and the size of the queue 
 * in your queue.c file as follows:
 *
 *	queue_node_t*  head = NULL;		//Queue head
 *	queue_node_t* tail = NULL;		//Queue tail	
 *	int q_size = 0;					//Queue size
 *
 * The above variables are not declared here in this header file to avoid multiple declarations
 * of them in multiple source files where queue.h header file is being included.
 */



void enqueue(const int id);
//Adds the student id at the tail of the queue and increment queue size


int dequeue();
//Removes a student id from the head of the queue and decrement queue size


int queue_size();
//Returns the current size of the queue.


#endif
