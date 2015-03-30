/*
 * MMA9551L.c
 *
 *  Created on: 25 mar 2015
 *      Author: Adrian Ratajczyk
 */

#include "spi.h"
#include "config.h"
#include "MMA9551L.h"

/*---------------------------------------------------------------------------------------------------------------------+
| SPI functions
+---------------------------------------------------------------------------------------------------------------------*/

void MMA9551L_SpiRead(uint8_t* rx, uint8_t number)
{
	SPI_Read(rx, number);
}

void MMA9551L_SpiSend(uint8_t* tx, uint8_t number)
{
	SPI_Send(tx, number);
}

void MMA9551L_SpiStart()
{
	SPI_StartTransmission();
}

void MMA9551L_SpiStop()
{
	SPI_StopTransmission();
}

/*---------------------------------------------------------------------------------------------------------------------+
| MMA9551L functions
+---------------------------------------------------------------------------------------------------------------------*/

void MMA9551L_SpiInit()
{
	SPI_Initialize(MMA9551L_SPI_CPOL, MMA9551L_SPI_CPHA);
}

void MMA9551L_CheckVersion()
{
	MMA9551L_SpiStart();

	uint8_t tab[17];
	tab[0] = 0x00;
	tab[1] = 0x00;
	tab[2] = 0x00;
	tab[3] = 0x0C;

	MMA9551L_SpiSend(tab, 4);
	MMA9551L_SpiRead(tab, 17);

	MMA9551L_SpiStop();
}
