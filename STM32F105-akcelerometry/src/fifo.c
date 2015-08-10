/*
 * fifo.c
 *
 *  Created on: 9 lip 2015
 *      Author: Adrian Ratajczyk
 */

#include "fifo.h"

static void queueAdd(uint8_t * first, int n, Queue * queue)
{
	Element element;
	element.first_byte = first;
	element.n = n;

	Node * node = malloc(sizeof(Node));
	node->element = element;

	if(queue->length == 0)
	{
		queue->head = node;
		queue->tail = node;
		node->next_node = 0;
	}
	else if(queue->length > 0)
	{
		queue->tail->next_node = node;
		queue->tail = node;
	}
	queue->length++;
}

static Element queueGetHead(Queue * queue)
{
	Element element;
	if(queue->length > 0)
	{
		Node * node = queue->head;
		element = queue->head->element;
		queue->head = queue->head->next_node;
		free(node);
		queue->length--;
	}
	else
	{
		element.first_byte = 0;
		element.n = 0;
	}
	return element;
}

static unsigned int queueGetLength(Queue * queue)
{
	return queue->length;
}

Queue * createQueue()
{
	Queue * queue = malloc(sizeof(Queue));
	if(queue == 0)
	{
		return 0;
	}
	queue->length = 0;
	queue->head = 0;
	queue->tail = 0;
	queue->add = &queueAdd;
	queue->get = &queueGetHead;
	queue->getLength = &queueGetLength;

	return queue;
}

Element * createElement(uint8_t * firstByte, unsigned int n)
{
	Element * element = malloc(sizeof(Element));
	element->first_byte = firstByte;
	element->n = n;

	return element;
}


