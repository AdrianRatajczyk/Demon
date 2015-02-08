/*
 * ADXL343.c
 *
 *  Created on: 13 sty 2015
 *      Author: Adrian
 */

#include "spi.h"
#include "config.h"
#include "ADXL343.h"

/*---------------------------------------------------------------------------------------------------------------------+
| SPI functions
+---------------------------------------------------------------------------------------------------------------------*/

void ADXL343_SpiRead(uint8_t* rx, uint8_t number)
{
	SPI_Read(rx, number);
}

void ADXL343_SpiSend(uint8_t* tx, uint8_t number)
{
	SPI_Send(tx, number);
}

void ADXL343_SpiStart()
{
	SPI_StartTransmission();
}

void ADXL343_SpiStop()
{
	SPI_StopTransmission();
}


/*---------------------------------------------------------------------------------------------------------------------+
| ADXL343 functions
+---------------------------------------------------------------------------------------------------------------------*/

void ADXL343_Init()
{
	uint8_t rx;
	uint8_t tx[2];

	tx[0] = ADXL343_READ | ADXL343_SINGLE_BYTE | ADXL343_DEV_ID;

	ADXL343_SpiStart();
	ADXL343_SpiSend(tx,1);
	ADXL343_SpiRead(&rx,1);
	ADXL343_SpiStop();

	tx[0] = ADXL343_WRITE | ADXL343_SINGLE_BYTE | ADXL343_POWER_CTL;
	tx[1] = ADXL343_POWER_CTL_MEASURE;

	ADXL343_SpiStart();
	ADXL343_SpiSend(tx,2);
	ADXL343_SpiStop();

	tx[0] = ADXL343_READ | ADXL343_SINGLE_BYTE | ADXL343_POWER_CTL;

	ADXL343_SpiStart();
	ADXL343_SpiSend(tx,1);
	ADXL343_SpiRead(&rx,1);
	ADXL343_SpiStop();
}

void ADXL343_Read(int16_t *x, int16_t *y, int16_t *z)
{
	uint8_t bufor[2];

	bufor[0] =	ADXL343_READ | ADXL343_MULTIPLE_BYTE | ADXL343_DATAX0;

	ADXL343_SpiStart();
	ADXL343_SpiSend(bufor,1);
	ADXL343_SpiRead(bufor,2);
	*x = ( (int16_t)((bufor[1]) << 8) | (int16_t)bufor[0]);
	ADXL343_SpiRead(bufor,2);
	*y = ( (int16_t)((bufor[1]) << 8) | (int16_t)bufor[0]);
	ADXL343_SpiRead(bufor,2);
	*z = ( (int16_t)((bufor[1]) << 8) | (int16_t)bufor[0]);
	ADXL343_SpiStop();
}


