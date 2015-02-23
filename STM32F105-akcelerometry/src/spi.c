#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "config.h"
#include "spi.h"

void SPI_Initialize()
{
	// Configuring GPIO

	RCC_APB2PeriphClockCmd(SPIx_RCC_GPIO, ENABLE);

	GPIO_InitTypeDef Struktura_GPIO;

	// NSS PIN
	Struktura_GPIO.GPIO_Speed=SPIx_GPIO_SPEED;
	Struktura_GPIO.GPIO_Pin=SPIx_NSS_PIN;
	Struktura_GPIO.GPIO_Mode=SPIx_NSS_MODE;
	GPIO_Init(SPIx_GPIO, &Struktura_GPIO);

	// SCLK
	Struktura_GPIO.GPIO_Speed=SPIx_GPIO_SPEED;
	Struktura_GPIO.GPIO_Pin=SPIx_SCLK_PIN;
	Struktura_GPIO.GPIO_Mode=SPIx_SCLK_MODE;
	GPIO_Init(SPIx_GPIO, &Struktura_GPIO);

	// MISO
	Struktura_GPIO.GPIO_Speed=SPIx_GPIO_SPEED;
	Struktura_GPIO.GPIO_Pin=SPIx_MISO_PIN;
	Struktura_GPIO.GPIO_Mode=SPIx_MISO_MODE;
	GPIO_Init(SPIx_GPIO, &Struktura_GPIO);

	// MOSI
	Struktura_GPIO.GPIO_Speed=SPIx_GPIO_SPEED;
	Struktura_GPIO.GPIO_Pin=SPIx_MOSI_PIN;
	Struktura_GPIO.GPIO_Mode=SPIx_MOSI_MODE;
	GPIO_Init(SPIx_GPIO, &Struktura_GPIO);


	// Configuring SPI

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	SPI_InitTypeDef Struktura_SPI;
	Struktura_SPI.SPI_BaudRatePrescaler=SPIx_BAUDRATEPRESCALLER;
	Struktura_SPI.SPI_CPHA=SPIx_CPHA;
	Struktura_SPI.SPI_CPOL=SPIx_CPOL;
	Struktura_SPI.SPI_DataSize=SPIx_DATASIZE;
	Struktura_SPI.SPI_Direction=SPIx_DIRECTION;
	Struktura_SPI.SPI_FirstBit=SPIx_FIRSTBIT;
	Struktura_SPI.SPI_Mode=SPIx_MODE;
	Struktura_SPI.SPI_NSS=SPIx_NSS;
	SPI_Init(SPIx, &Struktura_SPI);

	// Enabling SPI
	SPI_Cmd(SPIx, ENABLE);

	SPI_StopTransmission();
}

void SPI_StartTransmission()
{
	GPIO_WriteBit(SPIx_GPIO, SPIx_NSS_PIN, Bit_RESET);
}

void SPI_StopTransmission()
{
	GPIO_WriteBit(SPIx_GPIO, SPIx_NSS_PIN, Bit_SET);
}

void SPI_Send(uint8_t* tx, uint8_t number)
{
	while(number--)
	{
		SPI_I2S_SendData(SPIx, *(tx++));

		while(!SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE));

		SPI_I2S_ReceiveData(SPIx);
	}
}

void SPI_Read(uint8_t* rx, uint8_t number)
{
	while(number--)
	{
		SPIx->DR = 255;

		while(!SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE));

		*(rx++)=SPIx->DR;
	}
}
