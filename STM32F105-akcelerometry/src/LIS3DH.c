#include "spi.h"
#include "config.h"
#include "LIS3DH.h"

/*---------------------------------------------------------------------------------------------------------------------+
| SPI functions
+---------------------------------------------------------------------------------------------------------------------*/

void LIS3DH_SpiRead(uint8_t* rx, uint8_t number)
{
	SPI_Read(rx, number);
}

void LIS3DH_SpiSend(uint8_t* tx, uint8_t number)
{
	SPI_Send(tx, number);
}

void LIS3DH_SpiStart()
{
	SPI_StartTransmission();
}

void LIS3DH_SpiStop()
{
	SPI_StopTransmission();
}

/*---------------------------------------------------------------------------------------------------------------------+
| ADXL343 functions
+---------------------------------------------------------------------------------------------------------------------*/

void LIS3DH_Init()
{

}

void LIS3DH_Read(int16_t *x, int16_t *y, int16_t *z)
{

}
