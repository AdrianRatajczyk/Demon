/*
 * bufor.c
 *
 *  Created on: 7 paü 2015
 *      Author: Adrian Ratajczyk
 */

#include <stdint.h>
#include <stddef.h>
#include "bufor.h"

static void buforAddElement(Bufor *bufor, int16_t element);
static int16_t buforGetElement(Bufor *bufor, uint16_t index);
static void buforCalculateMean(Bufor *bufor);

Bufor * createBufor(size_t size)
{
	Bufor * bufor = malloc(sizeof(Bufor));

	bufor->size = size;
	bufor->length = 0;
	bufor->head_index = 0;
	bufor->tail_index = 0;
	bufor->mean = 0;

	bufor->tab = malloc(size * sizeof(int16_t));

	bufor->add = &buforAddElement;
	bufor->get = &buforGetElement;
	bufor->calculateMean = &buforCalculateMean;

	return bufor;
}

void destroyBufor(Bufor * bufor)
{
	free(bufor);
}

static void buforCalculateMean(Bufor *bufor)
{
	int32_t mean = 0;

	uint16_t index = 0;

	while(index < bufor->length)
	{
		mean += bufor->get(bufor, index);
		index++;
	}

	mean /= bufor->length;

	bufor->mean = mean;
}

static void buforAddElement(Bufor *bufor, int16_t element)
{
	// UPDATING PARAMETERS OF BUFOR STRUCTURE

	// if bufor is empty
	if(bufor->length == 0)
	{
		// don't update tail index and head index
		bufor->length++;
	}

	// if bufor is not full
	else if(bufor->length < bufor->size)
	{
		// don't update head index
		bufor->length++;
		bufor->tail_index++;
		bufor->tail_index %= bufor->size;
	}

	// if bufor is full
	else if(bufor->length == bufor->size)
	{
		// don't update length
		bufor->tail_index++;
		bufor->tail_index %= bufor->size;
		bufor->head_index++;
		bufor->head_index %= bufor->size;
	}

	// ADDING NEW ELEMENT TO BUFOR
	*(bufor->tab + bufor->tail_index) = element;
}

static int16_t buforGetElement(Bufor *bufor, uint16_t index)
{
	int16_t element;

	index += bufor->head_index;
	index %= bufor->size;

	element = *(bufor->tab + index);

	return element;
}
