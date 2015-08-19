#define CZAS_POMIARU				10000

#include "fifo.h"

enum akcelerometr
{
	lis3dh = 1,
	adxl343 = 2,
	lsm9ds0 = 3
};

void pomiar();
void push_uint8_to_bufor_in_asciiHex(uint8_t x, uint8_t * bufor, int index);
int push_int16_to_bufor_in_asciiHex(int16_t x, uint8_t * bufor, int index);
int push_CRLF_to_bufor(uint8_t * bufor, int index);
