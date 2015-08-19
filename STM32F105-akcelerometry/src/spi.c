#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "config.h"
#include "spi.h"

void SPI_Initialize(enum spi_CPOL cpol, enum spi_CPHA cpha)
{
	RCC_PCLK2Config(RCC_HCLK_Div2);

	// Configuring GPIO
	RCC_APB2PeriphClockCmd(SPIx_RCC_GPIO | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitTypeDef Struktura_GPIO;

	// NSS PIN
	Struktura_GPIO.GPIO_Speed=SPIx_GPIO_SPEED;
	Struktura_GPIO.GPIO_Pin=SPIx_NSS_PIN;
	Struktura_GPIO.GPIO_Mode=SPIx_NSS_MODE;
	GPIO_Init(SPIx_GPIO, &Struktura_GPIO);

	// CS PIN
	Struktura_GPIO.GPIO_Speed=SPIx_GPIO_SPEED;
	Struktura_GPIO.GPIO_Pin=SPIx_CS_PIN;
	Struktura_GPIO.GPIO_Mode=SPIx_CS_MODE;
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
	Struktura_SPI.SPI_CPHA=cpha;
	Struktura_SPI.SPI_CPOL=cpol;
	Struktura_SPI.SPI_DataSize=SPIx_DATASIZE;
	Struktura_SPI.SPI_Direction=SPIx_DIRECTION;
	Struktura_SPI.SPI_FirstBit=SPIx_FIRSTBIT;
	Struktura_SPI.SPI_Mode=SPIx_MODE;
	Struktura_SPI.SPI_NSS=SPIx_NSS;
	SPI_Init(SPIx, &Struktura_SPI);

	// Enabling SPI
	SPI_Cmd(SPIx, ENABLE);

	SPI_StopTransmission(SPIx_NSS_PIN);
	SPI_StopTransmission(SPIx_CS_PIN);
}

void SPI_Init_CS(uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef Struktura_GPIO;

	// NSS/CS PIN
	Struktura_GPIO.GPIO_Speed = SPIx_GPIO_SPEED;
	Struktura_GPIO.GPIO_Pin = GPIO_Pin;
	Struktura_GPIO.GPIO_Mode = SPIx_NSS_MODE;
	GPIO_Init(SPIx_GPIO, &Struktura_GPIO);
}

void SPI_StartTransmission(uint16_t GPIO_Pin)
{
	GPIO_WriteBit(SPIx_GPIO, GPIO_Pin, Bit_RESET);
}

void SPI_StopTransmission(uint16_t GPIO_Pin)
{
	GPIO_WriteBit(SPIx_GPIO, GPIO_Pin, Bit_SET);
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
