/*
 * autokorelacja.c
 *
 *  Created on: 7 paü 2015
 *      Author: Adrian Ratajczyk
 */

#include <stdint.h>
#include <stddef.h>

#include "bufor.h"
#include "autokorelacja.h"


int32_t autokorelacja(Bufor * bufor, size_t length, uint16_t m)
{
	int32_t autokorelacja = 0;

	uint16_t index = m;

	int32_t skladnik = 0;

	int16_t czynnik1;
	int16_t czynnik2;

	while(index < length)
	{
		czynnik1 = bufor->get(bufor, index);
		czynnik1 -= bufor->mean;

		czynnik2 = bufor->get(bufor, index-m);
		czynnik2 -= bufor->mean;

		skladnik = czynnik1 * czynnik2;
		autokorelacja += skladnik;
		index++;
	}

	return autokorelacja;
}
