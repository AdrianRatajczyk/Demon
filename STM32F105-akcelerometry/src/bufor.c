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

Bufor * createBufor(size_t size)
{
	Bufor * bufor = malloc(sizeof(Bufor));

	bufor->size = size;
	bufor->length = 0;
	bufor->head_index = 0;
	bufor->tail_index = 0;

	bufor->tab = malloc(size * sizeof(int16_t));

	return bufor;
}

void destroyBufor(Bufor * bufor)
{
	free(bufor);
}

static void buforAddElement(Bufor *bufor, int16_t element)
{
//	// if bufor is empty
//	if(bufor->length == 0)
//	{
//		// don't update tail index
//
//	}

	// if bufor is not full
	if(bufor->length < bufor->size)
	{

	}
}
