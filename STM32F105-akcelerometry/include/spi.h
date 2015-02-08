#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

/*---------------------------------------------------------------------------------------------------------------------+
| global functions' prototypes
+---------------------------------------------------------------------------------------------------------------------*/

void SPI_Initialize();

void SPI_StartTransmission();

void SPI_StopTransmission();

void SPI_Send(uint8_t* tx, uint8_t number);

void SPI_Read(uint8_t* rx, uint8_t number);

#endif /* SPI_H_ */
