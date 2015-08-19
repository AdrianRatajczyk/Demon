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
	//SPI_StartTransmission();
}

void MMA9551L_SpiStop()
{
	//SPI_StopTransmission();
}

void MMA9551L_ResetB_Low()
{
	GPIO_WriteBit(MMA9551L_RESETB_GPIO, MMA9551L_RESETB_PIN, Bit_RESET);
}

void MMA9551L_ResetB_High()
{
	GPIO_WriteBit(MMA9551L_RESETB_GPIO, MMA9551L_RESETB_PIN, Bit_SET);
}

/*---------------------------------------------------------------------------------------------------------------------+
| MMA9551L functions
+---------------------------------------------------------------------------------------------------------------------*/

void MMA9551L_SpiInit()
{
	SPI_Initialize(MMA9551L_SPI_CPOL, MMA9551L_SPI_CPHA);

	//RCC_APB2PeriphClockCmd(MMA9551L_RESETB_GPIO, ENABLE);

	//RCC_APB2PeriphClockCmd(LSM9DS0_CS_RCC_GPIO, ENABLE);

	GPIO_InitTypeDef Struktura_GPIO;

//	// RESETB PIN
//	Struktura_GPIO.GPIO_Speed = MMA9551L_GPIO_SPEED;
//	Struktura_GPIO.GPIO_Pin = MMA9551L_RESETB_PIN;
//	Struktura_GPIO.GPIO_Mode = MMA9551L_RESETB_MODE;
//	GPIO_Init(MMA9551L_RESETB_GPIO, &Struktura_GPIO);

	// CS_G pin
	Struktura_GPIO.GPIO_Speed = LSM9DS0_GPIO_SPEED;
	Struktura_GPIO.GPIO_Pin = LSM9DS0_CS_G_PIN;
	Struktura_GPIO.GPIO_Mode = LSM9DS0_CS_G_MODE;
	GPIO_Init(LSM9DS0_CS_G_GPIO, &Struktura_GPIO);


	MMA9551L_SpiStart();
	MMA9551L_ResetB_Low();
	Delay(100);
	MMA9551L_ResetB_High();
	Delay(100);
	MMA9551L_SpiStop();
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
	MMA9551L_SpiSend(tab, 1);
	MMA9551L_SpiRead(tab, 17);

	MMA9551L_SpiStop();
}

void MMA9551L_WakeUp()
{
	uint8_t tab[5];

	MMA9551L_SpiStart();

	MMA9551L_SpiSend(tab, 5);
	tab[0] = 0x12;
	tab[1] = 0x10;
	tab[2] = 0x06;
	tab[3] = 1;
	MMA9551L_SpiSend(tab, 4);
	MMA9551L_SpiRead(tab, 5);
	MMA9551L_SpiStop();

	MMA9551L_SpiStart();
	tab[0] = 0x12;
	tab[1] = (2 << 4);
	tab[2] = 0x06;
	tab[3] = 1;
	tab[4] = 0;
	MMA9551L_SpiSend(tab, 5);
	MMA9551L_SpiStop();


	MMA9551L_SpiStart();
	tab[0] = 0x12;
	tab[1] = 0x10;
	tab[2] = 0x06;
	tab[3] = 1;
	MMA9551L_SpiSend(tab, 4);
	MMA9551L_SpiRead(tab, 5);
	MMA9551L_SpiStop();
}
