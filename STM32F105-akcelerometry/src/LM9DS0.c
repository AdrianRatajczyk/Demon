/*
 * LSM9DS0.c
 *
 *  Created on: 10 mar 2015
 *      Author: Adrian Ratajczyk
 */

#include "spi.h"
#include "config.h"
#include "ADXL343.h"


/*---------------------------------------------------------------------------------------------------------------------+
| SPI functions
+---------------------------------------------------------------------------------------------------------------------*/

void LSM9DS0_XM_SpiRead(uint8_t* rx, uint8_t number)
{
	SPI_Read(rx, number);
}

void LSM9DS0_G_SpiRead(uint8_t* rx, uint8_t number)
{
	SPI_Read(rx, number);
}

void LSM9DS0_SpiSend(uint8_t* tx, uint8_t number)
{
	SPI_Send(tx, number);
}

void LSM9DS0_XM_SpiStart()
{
	SPI_StartTransmission();
}

void LSM9DS0_G_SpiStart()
{
	SPI_StartTransmission();
}

void LSM9DS0_XM_SpiStop()
{
	SPI_StopTransmission();
}

void LSM9DS0_G_SpiStop()
{
	SPI_StopTransmission();
}


/*---------------------------------------------------------------------------------------------------------------------+
| ADXL343 functions
+---------------------------------------------------------------------------------------------------------------------*/

