#include "stm32f10x.h"
#include <stdio.h>
#include "ADXL343.h"
#include "config.h"
#include "stm32f10x_usart.h"
#include "pomiar.h"
#include "uart.h"
#include "defines.h"
#include "LIS3DH.h"

/*---------------------------------------------------------------------------------------------------------------------+
| global variables
+---------------------------------------------------------------------------------------------------------------------*/


volatile uint16_t Rx;

volatile uint16_t czas=0;

volatile uint8_t pomiar_w_toku=0;
volatile uint8_t odlicz_pomiar=0;
volatile uint8_t wyslano_koniec=1;

volatile int czas_pomiaru=CZAS_POMIARU;

volatile char buf[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void pomiar()
{
	int16_t x;
	int16_t y;
	int16_t z;
	uint8_t test;
	uint8_t test1;

	int i;

	while(1)
	{
		if(pomiar_w_toku)
		{
			//for(i=0;i<10000;i++){};



			#if defined(ADXL343)
				ADXL343_Read(&x, &y, &z);
			#elif defined(LSM9DS0)
				LSM9DS0_Acc_Read(&x, &y, &z);
			#else
				LIS3DH_Read(&x, &y, &z);
			#endif

			#if defined(UART_RAW)
				UART_Send_int16_raw(czas);
				UART_Send_int16_raw(x);
				UART_Send_int16_raw(y);
				UART_Send_int16_raw(z);
			#elif defined(UART_HEX_ASCII)
				UART_Send_hex((uint8_t)(czas >> 8));
				UART_Send_hex((uint8_t)(czas & 0xFF));
				UART_Send_hex((uint8_t)(x >> 8));
				UART_Send_hex((uint8_t)(x & 0xFF));
				UART_Send_hex((uint8_t)(y >> 8));
				UART_Send_hex((uint8_t)(y & 0xFF));
				UART_Send_hex((uint8_t)(z >> 8));
				UART_Send_hex((uint8_t)(z & 0xFF));
			#else
				UART_Send_int16(czas, buf, 5);
				UART_Send_int16(x, buf, 7);
				UART_Send_int16(y, buf, 7);
				UART_Send_int16(z, buf, 7);
			#endif

			UART_Send_CRLF();

			if (!pomiar_w_toku && !wyslano_koniec)
			{
				UART_Send_char('#');
				UART_Send_CRLF();
				wyslano_koniec = 1;
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
		if(czas>czas_pomiaru)
		{
			pomiar_w_toku=0;
		}
	}
}

void USART2_IRQHandler(void)
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
				czas_pomiaru=-1;
				break;
			default:
				break;
		}
	}
}
