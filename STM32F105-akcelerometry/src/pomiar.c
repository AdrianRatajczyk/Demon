#include "stm32f10x.h"
#include <stdio.h>
#include "ADXL343.h"
#include "config.h"
#include "stm32f10x_usart.h"
#include "pomiar.h"
#include "uart.h"
#include "defines.h"
#include "LIS3DH.h"
#include "fifo.h"
#include "config.h"
#include "stm32f10x.h"
#include "bufor.h"


/*---------------------------------------------------------------------------------------------------------------------+
| global variables
+---------------------------------------------------------------------------------------------------------------------*/

volatile uint16_t Rx;

volatile unsigned long czas=0;

volatile uint8_t pomiar_w_toku = 0;
volatile uint8_t odlicz_pomiar = 0;
volatile uint8_t wyslano_koniec = 1;
volatile uint8_t dma_wolne = 1;
volatile uint8_t wykonaj_pomiar = 1;

volatile int linieOdebrane=0;

volatile unsigned long czas_pomiaru=CZAS_POMIARU;

volatile enum akcelerometr wybor = lis3dh;

Bufor * bufor;

void pomiar()
{
	int16_t x;
	int16_t y;
	int16_t z;

	int i = 0;

	bufor = createBufor(128);

	while(1)
	{
		if(pomiar_w_toku && wykonaj_pomiar)
		{
			wykonaj_pomiar = 0;
			switch(wybor)
			{
				case lis3dh:
					LIS3DH_Read(&x, &y, &z);
					break;
				case adxl343:
					ADXL343_Read(&x, &y, &z);
					break;
				case lsm9ds0:
					LSM9DS0_Acc_Read(&x, &y, &z);
					break;
				default:
					break;
			}
		}
	}
}

void SysTick_Handler(void)
{
	//TimingDelay_Decrement();
	if(pomiar_w_toku)
	{
		czas++;
		if(czas%2 == 0)
		{
			wykonaj_pomiar = 1;
		}
		if(czas>czas_pomiaru)
		{
			pomiar_w_toku=0;
		}
	}
}

void DMA1_Channel7_IRQHandler(void)
{
	//transfer complete
	if(DMA1->ISR && DMA_ISR_TCIF7)
	{
		//clear TRANSFER COMPLETE FLAG
		DMA1->IFCR |= DMA_IFCR_CTCIF7;

		dma_wolne = 1;
	}
}

void USARTx_IRQHandler(void)
{
	if(USART_GetITStatus(USARTx,USARTx_IT) != RESET)
	{
		Rx=USART_ReceiveData(USARTx);
		USART_ClearITPendingBit(USARTx, USARTx_IT);
		switch(Rx)
		{
			// sygna³ do rozpoczecia pomiaru
			case 49:
				if(!pomiar_w_toku)
				{
					pomiar_w_toku=1;
					wyslano_koniec=0;
					czas=0;
					linieOdebrane=0;
				}
				break;
			// sygna³ do zakoñczenia pomiaru
			case 50:
				pomiar_w_toku=0;
				break;
			case 51:
				czas_pomiaru=CZAS_POMIARU;
				break;
			case 52:
				czas_pomiaru=1000000;
				break;
			case 53:
				ADXL343_Init();
				wybor = adxl343;
				break;
			case 54:
				LIS3DH_Init();
				wybor = lis3dh;
				break;
			case 55:
				LSM9DS0_Init();
				wybor = lsm9ds0;
				break;
			default:
				break;
		}
	}
}
