/*
 * FIFO.h
 *
 *  Created on: 9 lut 2015
 *      Author: Adrian
 */

#ifndef FIFO2_H_
#define FIFO2_H_

/**
 * The contender for CAN data
 */
typedef struct {
	uint8_t data[8];
	uint8_t lenght;
	uint32_t ID;
} CAN_Item_t;

/**
 * The Node struct,
 * contains item and the pointer that point to next node.
 */
typedef struct Node {
	CAN_Item_t item;
	struct Node* next;
} Node_t;


/**
 * The Queue struct, contains the pointers that
 * point to first node and last node, the size of the Queue,
 * and the function pointers.
 */
typedef struct Queue{
	Node_t* head;
	Node_t* tail;

	/**
	 * 	add item to tail
	 */
	void (*push)(CAN_Item_t item, struct Queue* q); //

	/**
	 * 	get item from head and remove it from queue
	 */
	CAN_Item_t (*pop)(struct Queue* q);

	/**
	 * 	get item from head but keep it in queue
	 */
	CAN_Item_t (*peek)(struct Queue* q);

	/**
	 * 	size of this queue
	 */
	int size;
} Queue_t;

Queue_t* new_Queue();

#endif /* FIFO2_H_ */
