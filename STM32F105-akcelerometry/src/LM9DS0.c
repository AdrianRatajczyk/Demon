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
	SPI_Init(LSM9DS0_SPIx, &Struktura_SPI);

	// Enabling LSM9DS0 SPI
	SPI_Cmd(LSM9DS0_SPIx, ENABLE);

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

	SPI_Init_CS();
	SPI_StopTransmission();
}

static void LSM9DS0_SpiRead(uint8_t* rx, uint8_t number)
{
	while (number--)
	{
		LSM9DS0_SPIx->DR = 255;

		while (!SPI_I2S_GetFlagStatus(LSM9DS0_SPIx, SPI_I2S_FLAG_RXNE));

		*rx = LSM9DS0_SPIx->DR;

		rx++;
	}
}

static void LSM9DS0_SpiSend(uint8_t* tx, uint8_t number)
{
	while(number--)
	{
		SPI_I2S_SendData(LSM9DS0_SPIx, *(tx++));

		while(!SPI_I2S_GetFlagStatus(LSM9DS0_SPIx, SPI_I2S_FLAG_RXNE));

		SPI_I2S_ReceiveData(LSM9DS0_SPIx);
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
	int i;

	LSM9DS0_SPI_Init();

	uint8_t tab[2];
	tab[0] = LSM9DS0_READ | LSM9DS0_SINGLE_BYTE | LSM9DS0_WHO_AM_I_G;

	LSM9DS0_G_SpiStart();
	LSM9DS0_SpiSend(tab, 1);
	LSM9DS0_SpiRead(tab, 1);
	LSM9DS0_G_SpiStop();

	for(i=0;i<10000;i++){};

	tab[0] = LSM9DS0_READ | LSM9DS0_SINGLE_BYTE | LSM9DS0_WHO_AM_I_XM;

	LSM9DS0_XM_SpiStart();
	LSM9DS0_SpiSend(tab, 1);
	LSM9DS0_SpiRead(tab, 1);
	LSM9DS0_XM_SpiStop();

	for(i=0;i<10000;i++){};

	tab[0] = LSM9DS0_WRITE | LSM9DS0_SINGLE_BYTE | LSM9DS0_CTRL_REG1_G;
	tab[1] = LSM9DS0_CTRL_REG1_G_Yen | LSM9DS0_CTRL_REG1_G_Xen | LSM9DS0_CTRL_REG1_G_Zen | LSM9DS0_CTRL_REG1_G_PD;

	LSM9DS0_G_SpiStart();
	LSM9DS0_SpiSend(tab, 2);
	LSM9DS0_G_SpiStop();

	for(i=0;i<10000;i++){};

	tab[0] = LSM9DS0_WRITE | LSM9DS0_SINGLE_BYTE | LSM9DS0_CTRL_REG1_XM;
	tab[1] = LSM9DS0_CTRL_REG1_XM_AXEN | LSM9DS0_CTRL_REG1_XM_AYEN | LSM9DS0_CTRL_REG1_XM_AZEN | LSM9DS0_CTRL_REG1_XM_AODR_400Hz;

	LSM9DS0_XM_SpiStart();
	LSM9DS0_SpiSend(tab, 2);
	LSM9DS0_XM_SpiStop();

	for(i=0;i<10000;i++){};

	tab[0] = LSM9DS0_WRITE | LSM9DS0_SINGLE_BYTE | LSM9DS0_CTRL_REG5_XM;
	tab[1] = (1 << 4); // Output data rate for magnetometer 50Hz

	LSM9DS0_XM_SpiStart();
	LSM9DS0_SpiSend(tab, 2);
	LSM9DS0_XM_SpiStop();

	for(i=0;i<10000;i++){};

	tab[0] = LSM9DS0_READ | LSM9DS0_SINGLE_BYTE | LSM9DS0_CTRL_REG5_XM;
	LSM9DS0_XM_SpiStart();
	LSM9DS0_SpiSend(tab, 1);
	LSM9DS0_SpiRead(tab, 1);
	LSM9DS0_XM_SpiStop();

	for(i=0;i<10000;i++){};

	tab[0] = LSM9DS0_WRITE | LSM9DS0_SINGLE_BYTE | LSM9DS0_CTRL_REG6_XM;
	tab[1] = (1 << 5); // Sensitivity for magnetometer +-4Gauss

	LSM9DS0_XM_SpiStart();
	LSM9DS0_SpiSend(tab, 2);
	LSM9DS0_XM_SpiStop();

	for(i=0;i<10000;i++){};

	tab[0] = LSM9DS0_READ | LSM9DS0_SINGLE_BYTE | LSM9DS0_CTRL_REG6_XM;
	LSM9DS0_XM_SpiStart();
	LSM9DS0_SpiSend(tab, 1);
	LSM9DS0_SpiRead(tab, 1);
	LSM9DS0_XM_SpiStop();

	for(i=0;i<10000;i++){};

	tab[0] = LSM9DS0_WRITE | LSM9DS0_SINGLE_BYTE | LSM9DS0_CTRL_REG7_XM;
	tab[1] = 0;    // Magnetometer in Continous-conversion mode

	LSM9DS0_XM_SpiStart();
	LSM9DS0_SpiSend(tab, 2);
	LSM9DS0_XM_SpiStop();

	for(i=0;i<10000;i++){};

	tab[0] = LSM9DS0_READ | LSM9DS0_SINGLE_BYTE | LSM9DS0_CTRL_REG7_XM;
	LSM9DS0_XM_SpiStart();
	LSM9DS0_SpiSend(tab, 1);
	LSM9DS0_SpiRead(tab, 1);
	LSM9DS0_XM_SpiStop();
}

void LSM9DS0_Gyro_Read(int16_t *x, int16_t *y, int16_t *z)
{
	uint8_t bufor[6];

	SPI_StartTransmission();
	LSM9DS0_G_SpiStart();

	bufor[0] = LSM9DS0_READ | LSM9DS0_MULTIPLE_BYTE | LSM9DS0_OUT_X_L_G;
	LSM9DS0_SpiSend(bufor, 1);
	LSM9DS0_SpiRead(bufor, 6);
	*x = ((int16_t) ((bufor[1]) << 8) | bufor[0]);
	*y = ((int16_t) ((bufor[3]) << 8) | bufor[2]);
	*z = ((int16_t) ((bufor[5]) << 8) | bufor[4]);

	LSM9DS0_G_SpiStop();
	SPI_StopTransmission();
}

void LSM9DS0_Acc_Read(int16_t *x, int16_t *y, int16_t *z)
{
	uint8_t bufor[6];

	SPI_StartTransmission();
	LSM9DS0_XM_SpiStart();

	bufor[0] = LSM9DS0_READ | LSM9DS0_MULTIPLE_BYTE | LSM9DS0_OUT_X_L_A;
	LSM9DS0_SpiSend(bufor, 1);
	LSM9DS0_SpiRead(bufor, 6);
	*x = ((int16_t) ((bufor[1]) << 8) | bufor[0]);
	*y = ((int16_t) ((bufor[3]) << 8) | bufor[2]);
	*z = ((int16_t) ((bufor[5]) << 8) | bufor[4]);

	LSM9DS0_XM_SpiStop();
	SPI_StopTransmission();
}

void LSM9DS0_Magn_Read(int16_t *x, int16_t *y, int16_t *z)
{
	uint8_t bufor[6];

	SPI_StartTransmission();
	LSM9DS0_XM_SpiStart();

	bufor[0] = LSM9DS0_READ | LSM9DS0_MULTIPLE_BYTE | LSM9DS0_OUT_X_L_M;
	LSM9DS0_SpiSend(bufor, 1);
	LSM9DS0_SpiRead(bufor, 6);
	*x = ((int16_t) ((bufor[1]) << 8) | bufor[0]);
	*y = ((int16_t) ((bufor[3]) << 8) | bufor[2]);
	*z = ((int16_t) ((bufor[5]) << 8) | bufor[4]);

	SPI_StopTransmission();
	LSM9DS0_XM_SpiStop();
}
