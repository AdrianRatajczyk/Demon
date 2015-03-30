#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include "stm32f10x_spi.h"

/*---------------------------------------------------------------------------------------------------------------------+
| enums
+---------------------------------------------------------------------------------------------------------------------*/

enum spi_CPOL
{
	spi_CPOL_LOW = SPI_CPOL_Low,
	spi_CPOL_HIGH = SPI_CPOL_High
};

enum spi_CPHA
{
	spi_CPHA_1edge = SPI_CPHA_1Edge,
	spi_CPHA_2edge = SPI_CPHA_2Edge
};

/*---------------------------------------------------------------------------------------------------------------------+
| global functions' prototypes
+---------------------------------------------------------------------------------------------------------------------*/

void SPI_Initialize(enum spi_CPOL cpol, enum spi_CPHA cpha);

void SPI_Init_CS();

void SPI_StartTransmission();

void SPI_StopTransmission();

void SPI_Send(uint8_t* tx, uint8_t number);

void SPI_Read(uint8_t* rx, uint8_t number);

#endif /* SPI_H_ */
