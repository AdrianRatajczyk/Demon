/*
 * LSM9DS0.c
 *
 *  Created on: 10 mar 2015
 *      Author: Adrian Ratajczyk
 */

#include "spi.h"
#include "config.h"
#include "LSM9DS0.h"


/*---------------------------------------------------------------------------------------------------------------------+
| SPI functions
+---------------------------------------------------------------------------------------------------------------------*/

static void LSM9DS0_SPI_Init()
{
	// Configuring GPIO
	RCC_APB2PeriphClockCmd(LSM9DS0_CS_RCC_GPIO, ENABLE);
	RCC_APB2PeriphClockCmd(LSM9DS0_XM_RCC_GPIO, ENABLE);
	RCC_APB2PeriphClockCmd(LSM9DS0_G_RCC_GPIO, ENABLE);

	GPIO_InitTypeDef Struktura_GPIO;

	// CS_XM pin
	Struktura_GPIO.GPIO_Speed = LSM9DS0_GPIO_SPEED;
	Struktura_GPIO.GPIO_Pin = LSM9DS0_CS_XM_PIN;
	Struktura_GPIO.GPIO_Mode = LSM9DS0_CS_XM_MODE;
	GPIO_Init(LSM9DS0_CS_XM_GPIO, &Struktura_GPIO);

	// CS_G pin
	Struktura_GPIO.GPIO_Speed = LSM9DS0_GPIO_SPEED;
	Struktura_GPIO.GPIO_Pin = LSM9DS0_CS_G_PIN;
	Struktura_GPIO.GPIO_Mode = LSM9DS0_CS_G_MODE;
	GPIO_Init(LSM9DS0_CS_G_GPIO, &Struktura_GPIO);

//	// MISO_XM pin
//	Struktura_GPIO.GPIO_Speed = LSM9DS0_GPIO_SPEED;
//	Struktura_GPIO.GPIO_Pin = LSM9DS0_XM_MISO_PIN;
//	Struktura_GPIO.GPIO_Mode = LSM9DS0_XM_MISO_MODE;
//	GPIO_Init(LSM9DS0_XM_MISO_GPIO, &Struktura_GPIO);

	// MISO_G pin
	Struktura_GPIO.GPIO_Speed = LSM9DS0_GPIO_SPEED;
	Struktura_GPIO.GPIO_Pin = LSM9DS0_G_MISO_PIN;
	Struktura_GPIO.GPIO_Mode = LSM9DS0_G_MISO_MODE;
	GPIO_Init(LSM9DS0_G_MISO_GPIO, &Struktura_GPIO);

	// MOSI
	Struktura_GPIO.GPIO_Speed = LSM9DS0_GPIO_SPEED;
	Struktura_GPIO.GPIO_Pin = LSM9DS0_MOSI_PIN;
	Struktura_GPIO.GPIO_Mode = LSM9DS0_MOSI_MODE;
	GPIO_Init(LSM9DS0_MOSI_GPIO, &Struktura_GPIO);

	// SCLK
	Struktura_GPIO.GPIO_Speed = LSM9DS0_GPIO_SPEED;
	Struktura_GPIO.GPIO_Pin = LSM9DS0_SCLK_PIN;
	Struktura_GPIO.GPIO_Mode = LSM9DS0_SCLK_MODE;
	GPIO_Init(LSM9DS0_SCLK_GPIO, &Struktura_GPIO);

	// Configuring SPI_G
	RCC_APB2PeriphClockCmd(LSM9DS0_G_RCC_SPI, ENABLE);

	SPI_InitTypeDef Struktura_SPI;
	Struktura_SPI.SPI_BaudRatePrescaler = LSM9DS0_SPI_G_BAUDRATEPRESCALLER;
	Struktura_SPI.SPI_CPHA = LSM9DS0_SPI_G_CPHA;
	Struktura_SPI.SPI_CPOL = LSM9DS0_SPI_G_CPOL;
	Struktura_SPI.SPI_DataSize = LSM9DS0_SPI_G_DATASIZE;
	Struktura_SPI.SPI_Direction = LSM9DS0_SPI_G_DIRECTION;
	Struktura_SPI.SPI_FirstBit = LSM9DS0_SPI_G_FIRSTBIT;
	Struktura_SPI.SPI_Mode = LSM9DS0_SPI_G_MODE;
	Struktura_SPI.SPI_NSS = LSM9DS0_SPI_G_NSS;
	SPI_Init(LSM9DS0_SPI_G, &Struktura_SPI);

	// Enabling SPI_G
	SPI_Cmd(LSM9DS0_SPI_G, ENABLE);

//	// Configuring SPI_XM
//	RCC_APB1PeriphClockCmd(LSM9DS0_XM_RCC_SPI, ENABLE);
//
//	Struktura_SPI.SPI_BaudRatePrescaler = LSM9DS0_SPI_XM_BAUDRATEPRESCALLER;
//	Struktura_SPI.SPI_CPHA = LSM9DS0_SPI_XM_CPHA;
//	Struktura_SPI.SPI_CPOL = LSM9DS0_SPI_XM_CPOL;
//	Struktura_SPI.SPI_DataSize = LSM9DS0_SPI_XM_DATASIZE;
//	Struktura_SPI.SPI_Direction = LSM9DS0_SPI_XM_DIRECTION;
//	Struktura_SPI.SPI_FirstBit = LSM9DS0_SPI_XM_FIRSTBIT;
//	Struktura_SPI.SPI_Mode = LSM9DS0_SPI_XM_MODE;
//	Struktura_SPI.SPI_NSS = LSM9DS0_SPI_XM_NSS;
//	SPI_Init(LSM9DS0_SPI_XM, &Struktura_SPI);
//
//	// Enabling SPI_XM
//	SPI_Cmd(LSM9DS0_SPI_XM, ENABLE);

	LSM9DS0_G_SpiStop();
	LSM9DS0_XM_SpiStop();
}

static void LSM9DS0_XM_SpiRead(uint8_t* rx, uint8_t number)
{
	while (number--)
	{
		SPIx->DR = 255;

		while (!SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE));

		*(rx++) = SPIx->DR;
	}
}

static void LSM9DS0_G_SpiRead(uint8_t* rx, uint8_t number)
{
	while (number--)
	{
		LSM9DS0_SPI_G->DR = 255;

		while (!SPI_I2S_GetFlagStatus(LSM9DS0_SPI_G, SPI_I2S_FLAG_RXNE));

		*(rx++) = LSM9DS0_SPI_G->DR;
	}
}

static void LSM9DS0_SpiSend(uint8_t* tx, uint8_t number)
{
	while(number--)
	{
		SPI_I2S_SendData(LSM9DS0_SPI_G, *(tx++));

		while(!SPI_I2S_GetFlagStatus(LSM9DS0_SPI_G, SPI_I2S_FLAG_RXNE));

		SPI_I2S_ReceiveData(LSM9DS0_SPI_G);
	}
}

static void LSM9DS0_XM_SpiStart()
{
	GPIO_WriteBit(LSM9DS0_CS_XM_GPIO, LSM9DS0_CS_XM_PIN, Bit_RESET);
}

static void LSM9DS0_G_SpiStart()
{
	GPIO_WriteBit(LSM9DS0_CS_G_GPIO, LSM9DS0_CS_G_PIN, Bit_RESET);
}

static void LSM9DS0_XM_SpiStop()
{
	GPIO_WriteBit(LSM9DS0_CS_XM_GPIO, LSM9DS0_CS_XM_PIN, Bit_SET);
}

static void LSM9DS0_G_SpiStop()
{
	GPIO_WriteBit(LSM9DS0_CS_G_GPIO, LSM9DS0_CS_G_PIN, Bit_SET);
}


/*---------------------------------------------------------------------------------------------------------------------+
| LSM9DS0 functions
+---------------------------------------------------------------------------------------------------------------------*/

void LSM9DS0_Init()
{
	LSM9DS0_SPI_Init();

	uint8_t tab;
	tab = LSM9DS0_READ | LSM9DS0_SINGLE_BYTE | LSM9DS0_WHO_AM_I_G;

	LSM9DS0_G_SpiStart();
	LSM9DS0_SpiSend(&tab, 1);
	LSM9DS0_G_SpiRead(&tab, 1);
	LSM9DS0_G_SpiStop();

	tab = LSM9DS0_READ | LSM9DS0_SINGLE_BYTE | LSM9DS0_WHO_AM_I_XM;

	LSM9DS0_XM_SpiStart();
	LSM9DS0_SpiSend(&tab, 1);
	LSM9DS0_G_SpiRead(&tab, 1);
	LSM9DS0_XM_SpiStop();


}

void LSM9DS0_Read(int16_t *x, int16_t *y, int16_t *z)
{

}
