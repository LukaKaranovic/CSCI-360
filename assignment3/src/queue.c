/**
 * @file queue.c
 * @author Luka Karanovic, 665778833, F25No1, CSCI 360, VIU
 * @version 1.0.0
 * @date November 06, 2025
 *
 * Implements helper functions for a queue data structure to be used in other files, such as 'src/student.c' and 'src/ta.c'.
 * Helper functions include: enqueue, dequeue, and get size operations.
 *
 */
 
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

queue_node_t*  head = NULL;		// Queue head
queue_node_t* tail = NULL;		// Queue tail
int q_size = 0;					// Queue size

/** @brief Adds a queue node to the end of a queue.
 *
 *  Creates a new node and gives it an id, then adds this node to the end of the queue. Increments queue size.
 *
 *  @param id The id given to the new node.
 *  @return Void.
 */

void enqueue(const int id) {
    queue_node_t* node = (queue_node_t*)malloc(sizeof(queue_node_t));
    node->id = id;
    node->next = NULL;
    if (head == NULL) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }

    q_size++;
}

/** @brief Removes a node from the front of the queue.
 *
 *  Gets the id from the node located at the head pointer and removes it. Decrements queue size.
 *
 *  @return The id of the removed node.
 */

int dequeue() {
    if (queue_size() == 0) {
        printf("Queue is empty, nothing to remove.\n");
        return -1;
    }

    int id = head->id;

    queue_node_t* temp = head;
    head = head->next;
    free(temp);
    q_size--;
    if (head == NULL) {
        tail = NULL;
    }
    return id;
}

/** @brief Returns the amount of nodes currently in the queue.
 *
 *  @return The size of the queue as an integer.
 */

int queue_size() {
    return q_size;
}
