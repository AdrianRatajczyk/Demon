/*
 * bufor.h
 *
 *  Created on: 7 paü 2015
 *      Author: Adrian Ratajczyk
 */

#ifndef BUFOR_H_
#define BUFOR_H_

typedef struct
{
	uint16_t size; // size of bufor in nuber of elements
	uint16_t length; // actual number of data stored in bufor
	uint16_t head_index; // index in bufor which contains the oldest element
	uint16_t tail_index; // index in bufor which contains the newest element

	int16_t * tab;
} Bufor;

Bufor * createBufor(size_t size);

void destroyBufor(Bufor * bufor);


#endif /* BUFOR_H_ */
