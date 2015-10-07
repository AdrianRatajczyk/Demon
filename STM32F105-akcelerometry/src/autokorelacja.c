/*
 * autokorelacja.c
 *
 *  Created on: 7 paü 2015
 *      Author: Adrian Ratajczyk
 */

#include <stdint.h>
#include <stddef.h>

int32_t autokorelacja(int16_t* x, size_t length, uint16_t m)
{
	int32_t autokorelacja = 0;

	uint16_t index = m;

	int32_t skladnik = 0;

	while(index < length)
	{
		skladnik = (int32_t)((*(x+index))*(*(x+index-m)));
		autokorelacja += skladnik;
		index++;
	}

	return autokorelacja;
}
