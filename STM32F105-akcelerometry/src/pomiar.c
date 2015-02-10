#include "stm32f10x.h"
#include <stdio.h>
#include "ADXL343.h"
#include "config.h"
#include "stm32f10x_usart.h"
#include "pomiar.h"

/*---------------------------------------------------------------------------------------------------------------------+
| global variables
+---------------------------------------------------------------------------------------------------------------------*/

volatile uint16_t Rx;

volatile unsigned long czas=0;

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

	uint8_t i;

	while(1)
	{
		if(pomiar_w_toku)
		{
			// Tutaj co ma byc wyslane
			sChar2Str(&buf, czas,5);
			for(i=0;buf[i]!='\0';i++)
			{
				USART_SendData(USARTx,buf[i]);
				while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
			}

			USART_SendData(USARTx,',');
			while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}

			ADXL343_Read(&x, &y, &z);
			//moj_sprintf(&buf, x, 5, 0);
			sChar2Str(&buf, x, 4);
			for(i=0;buf[i]!='\0';i++)
			{
				USART_SendData(USARTx,buf[i]);
				while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
			}

			USART_SendData(USARTx,',');
			while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}

			sChar2Str(&buf, y, 4);
			for(i=0;buf[i]!='\0';i++)
			{
				USART_SendData(USARTx,buf[i]);
				while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
			}

			USART_SendData(USARTx,',');
			while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}

			sChar2Str(&buf, z, 4);
			for(i=0;buf[i]!='\0';i++)
			{
				USART_SendData(USARTx,buf[i]);
				while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
			}

			USART_SendData(USARTx,10);
			while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
			USART_SendData(USARTx,13);
			while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
		}
		if(!pomiar_w_toku && !wyslano_koniec)
		{
			USART_SendData(USARTx,'#');
			while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
			USART_SendData(USARTx,10);
			while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
			USART_SendData(USARTx,13);
			while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
			wyslano_koniec=1;
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
