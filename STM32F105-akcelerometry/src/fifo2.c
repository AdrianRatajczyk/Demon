/*
 ============================================================================
 Name        : FIFO.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "fifo2.h"

/**
 * This sample is about how to implement a queue in c
 *
 * Type of item is int
 * Add item to tail
 * Get item from head
 * Can get the size
 * Can display all content
 */

/**
 * Push an item into queue, if this is the first item,
 * both queue->head and queue->tail will point to it,
 * otherwise the oldtail->next and tail will point to it.
 */
void push(CAN_Item_t item, Queue_t* queue) {
	// Create a new node
	Node_t* n = (Node_t*) malloc(sizeof(Node_t));
	n->item = item;
	n->next = NULL;

	if (queue->head == NULL) { // no head
		queue->head = n;
	} else {
		queue->tail->next = n;
	}
	queue->tail = n;
	queue->size++;
}
/**
 * Return and remove the first item.
 */
CAN_Item_t pop(Queue_t* queue) {
	// get the first item
	Node_t* head = queue->head;
	CAN_Item_t item = head->item;

	// move head pointer to next node, decrease size
	queue->head = head->next;
	queue->size--;

	// free the memory of original head
	free(head);
	return item;
}
/**
 * Return but not remove the first item.
 */
CAN_Item_t peek(Queue_t* queue) {
	Node_t* head = queue->head;
	return head->item;
}
/**
 * Create and initiate a Queue
 */
Queue_t* new_Queue() {
	static Queue_t *drv_queue;
	drv_queue = (Queue_t *) malloc(sizeof(Queue_t));

	drv_queue->size = 0;
	drv_queue->head = NULL;
	drv_queue->tail = NULL;

	drv_queue->push = &push;
	drv_queue->pop = &pop;
	drv_queue->peek = &peek;
	return drv_queue;
}
