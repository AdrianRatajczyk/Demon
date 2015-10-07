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


/*---------------------------------------------------------------------------------------------------------------------+
| global variables
+---------------------------------------------------------------------------------------------------------------------*/

volatile Queue * queue;

volatile uint16_t Rx;

volatile unsigned long czas=0;

volatile uint8_t pomiar_w_toku = 0;
volatile uint8_t odlicz_pomiar = 0;
volatile uint8_t wyslano_koniec = 1;
volatile uint8_t dma_wolne = 1;
volatile uint8_t wykonaj_pomiar = 1;

volatile uint8_t bufor[BUFOR_SIZE];
volatile uint8_t buforEnd [] = { 35 , 13 , 10 };
volatile uint8_t buforStart [] = { 36 , 13 , 10 };
volatile uint16_t index=0;
volatile int linieOdebrane=0;

volatile unsigned long czas_pomiaru=CZAS_POMIARU;
volatile int ile=0;
volatile int ile1=0;

volatile enum akcelerometr wybor = lis3dh;

volatile char buf[20] = {65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84};

void pomiar()
{

	int16_t x;
	int16_t y;
	int16_t z;

	queue = createQueue();

	//Element element;

	int i = 0;

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

			#if defined(UART_RAW)
				UART_Send_int16_raw(czas);
				UART_Send_int16_raw(x);
				UART_Send_int16_raw(y);
				UART_Send_int16_raw(z);

			#elif defined(UART_HEX_ASCII)
				UART_send_halfWord_in_asciiHex(czas);
				UART_send_halfWord_in_asciiHex(x);
				UART_send_halfWord_in_asciiHex(y);
				UART_send_halfWord_in_asciiHex(z);

			#elif defined(DMA_TRANSMISSION)
				linieOdebrane += 1;
				index = push_int16_to_bufor_in_asciiHex(czas, bufor, index);
				index = push_int16_to_bufor_in_asciiHex(x, bufor, index);
				index = push_int16_to_bufor_in_asciiHex(y, bufor, index);
				index = push_int16_to_bufor_in_asciiHex(z, bufor, index);
				index = push_CRLF_to_bufor(bufor, index);


				if (linieOdebrane % BUFOR_LINES_NUMBER == 0) {
					linieOdebrane = 0;
					queue->add(&bufor[index - BUFOR_FRAME_LENGTH], BUFOR_FRAME_LENGTH, queue);
					if ((index + BUFOR_FRAME_LENGTH) > BUFOR_SIZE) {
						index = 0;
					}
					ile++;
				}

			#else
				UART_Send_int16(czas, buf, 5);
				UART_Send_int16(x, buf, 7);
				UART_Send_int16(y, buf, 7);
				UART_Send_int16(z, buf, 7);
			#endif

			#if !defined(DMA_TRANSMISSION)
				UART_Send_CRLF();
			#endif

			if (!pomiar_w_toku && !wyslano_koniec)
			{
				//while(queue->getLength(queue)){};

				UART_Send_char('#');
				UART_Send_CRLF();
				wyslano_koniec = 1;
			}

		}

#if defined(DMA_TRANSMISSION)
		if (dma_wolne) {
			if (queue->getLength(queue)) {
				dma_wolne = 0;
				element = queue->get(queue);

				ile1++;

				DMA1_Channel7->CCR = 0;

				//DMA1_Channel7->CNDTR = 20;//element.n;//number of data to transfer
				DMA1_Channel7->CNDTR = element.n;
				DMA1_Channel7->CPAR = &USARTx->DR;	//peripheral address
				DMA1_Channel7->CMAR = element.first_byte;
				//DMA1_Channel7->CMAR = buf;//element.first_byte;	//memory address

				//channel enable //transfer complete interrupt enable //memory increment mode enable  //read from memory
				DMA1_Channel7->CCR = DMA_CCR7_EN | DMA_CCR7_TCIE | DMA_CCR7_MINC | DMA_CCR7_DIR;
			}
		}
#endif
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

#if defined (DMA_TRANSMISSION)
			queue->add(buforEnd, 3, queue);
#endif
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
#if defined (DMA_TRANSMISSION)
					while(queue->getLength(queue))
					{
						queue->get(queue);
					}
					//queue->add(buforStart, 3, queue);
					index=0;
#endif
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

void push_uint8_to_bufor_in_asciiHex(uint8_t x, uint8_t * bufor, int index)
{
	uint8_t second = (x % 16);
	uint8_t first = (x / 16);

	if (first > 9) {
		first += 55;
	} else {
		first += 48;
	}

	if (second > 9) {
		second += 55;
	} else {
		second += 48;
	}

	bufor[index] = first;
	bufor[index+1] = second;
}

int push_int16_to_bufor_in_asciiHex(int16_t x, uint8_t * bufor, int index)
{
	push_uint8_to_bufor_in_asciiHex((uint8_t)(x >> 8), bufor, index);
	push_uint8_to_bufor_in_asciiHex((uint8_t)(x & 0xFF), bufor, index+2);
	return index + 4;
}

int push_CRLF_to_bufor(uint8_t * bufor, int index)
{
	bufor[index++] = 13;
	bufor[index++] = 10;
	return index;
}
