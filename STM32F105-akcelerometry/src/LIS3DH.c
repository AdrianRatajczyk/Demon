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

uint8_t LIS3DH_Init()
{
	uint8_t tx[2];

	tx[0] = LIS3DH_READ | LIS3DH_SINGLE_BYTE | LIS3DH_WHO_AM_I;
	LIS3DH_SpiStart();
	LIS3DH_SpiSend(tx,1);
	LIS3DH_SpiRead(&tx[1],1);
	LIS3DH_SpiStop();

	if(tx[1] != LIS3DH_NAME) return 0;

	tx[0] = LIS3DH_WRITE | LIS3DH_SINGLE_BYTE | LIS3DH_TEMP_CFG_REG;
	tx[1] = LIS3DH_TEMP_CFG_REG_ADC_PD;
	LIS3DH_SpiStart();
	LIS3DH_SpiSend(tx,2);
	LIS3DH_SpiStop();

	tx[0] = LIS3DH_WRITE | LIS3DH_SINGLE_BYTE | LIS3DH_CTRL_REG1;
	tx[1] = LIS3DH_CTRL_REG1_400_HZ | LIS3DH_CTRL_REG1_ZEN | LIS3DH_CTRL_REG1_YEN | LIS3DH_CTRL_REG1_XEN;
	LIS3DH_SpiStart();
	LIS3DH_SpiSend(tx,2);
	LIS3DH_SpiStop();

	return 1;
}

void LIS3DH_Read(int16_t *x, int16_t *y, int16_t *z)
{
	uint8_t bufor[2];

	bufor[0] =	LIS3DH_READ | LIS3DH_MULTIPLE_BYTE | LIS3DH_OUT_X_L;

	LIS3DH_SpiStart();
	LIS3DH_SpiSend(bufor,1);
	LIS3DH_SpiRead(bufor,2);
	*x = ( (int16_t)((bufor[1]) << 8) | (int16_t)bufor[0]);
	LIS3DH_SpiRead(bufor,2);
	*y = ( (int16_t)((bufor[1]) << 8) | (int16_t)bufor[0]);
	LIS3DH_SpiRead(bufor,2);
	*z = ( (int16_t)((bufor[1]) << 8) | (int16_t)bufor[0]);
	LIS3DH_SpiStop();
}
