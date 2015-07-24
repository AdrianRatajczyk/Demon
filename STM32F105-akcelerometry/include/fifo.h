/*
 * fifo.h
 *
 *  Created on: 9 lip 2015
 *      Author: Adrian Ratajczyk
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdint.h>

typedef struct
{
	uint8_t * first_byte;
	unsigned int n;
} Element;

typedef struct
{
	Element element;
	struct Node * next_node;
} Node;

typedef struct
{
	Node * head;
	Node * tail;
	unsigned int length;

	void (* add) (uint8_t * first_byte, unsigned int number_of_bytes, struct Queue * queue);
	Element (* get) (struct Queue * queue);
	unsigned int (* getLength) (struct Queue * queue);
} Queue;

Queue * createQueue();
Element * createElement(uint8_t * firstByte, unsigned int n);

#endif /* FIFO_H_ */
