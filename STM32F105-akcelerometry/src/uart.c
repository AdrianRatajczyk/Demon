#include "stm32f10x_gpio.h"
#include "config.h"
#include "uart.h"
#include "stm32f10x_usart.h"
#include "defines.h"

void UART_Initialize()
{
	// Configuring GPIO
	RCC_APB2PeriphClockCmd(USARTx_RCC_GPIO, ENABLE);

	GPIO_InitTypeDef Struktura_GPIO;

	// TX
	Struktura_GPIO.GPIO_Speed=USARTx_GPIO_SPEED;
	Struktura_GPIO.GPIO_Pin=USARTx_TX_PIN;
	Struktura_GPIO.GPIO_Mode=USARTx_TX_MODE;
	GPIO_Init(USARTx_GPIO, &Struktura_GPIO);

	// RX
	Struktura_GPIO.GPIO_Speed=USARTx_GPIO_SPEED;
	Struktura_GPIO.GPIO_Pin=USARTx_RX_PIN;
	Struktura_GPIO.GPIO_Mode=USARTx_RX_MODE;
	GPIO_Init(USARTx_GPIO, &Struktura_GPIO);

	// Configuring USART
#if defined(NOWA_PLYTKA)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
#else
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
#endif

	USART_InitTypeDef Struktura_USART;

	Struktura_USART.USART_BaudRate=USARTx_BAUDRATE;
	Struktura_USART.USART_HardwareFlowControl=USARTx_HARDWAREFLOWCONTROL;
	Struktura_USART.USART_Mode=USARTx_MODE;
	Struktura_USART.USART_Parity=USARTx_PARITY;
	Struktura_USART.USART_StopBits=USARTx_STOPBITS;
	Struktura_USART.USART_WordLength=USARTx_WORDLENGTH;
	USART_Init(USARTx, &Struktura_USART);

	USART_Cmd(USARTx, ENABLE);

	// Configuring interrupt
	USART_ITConfig(USARTx, USARTx_IT, ENABLE);

	NVIC_InitTypeDef Struktura_NVIC;
	Struktura_NVIC.NVIC_IRQChannel=USARTx_NVIC_IRQCHannel;
	Struktura_NVIC.NVIC_IRQChannelCmd=USARTx_NVIC_IRQChannelCmd;
	Struktura_NVIC.NVIC_IRQChannelPreemptionPriority=USARTx_NVIC_IRQChannelPreemptionPriority;
	Struktura_NVIC.NVIC_IRQChannelSubPriority=USARTx_NVIC_IRQChannelSubPriority;
	NVIC_Init(&Struktura_NVIC);

	#if defined(DMA_TRANSMISSION)
	// Configuring UART for DMA transmission
	USARTx->CR3 |= USART_CR3_DMAT;

	// Configuring interrupt for DMA
	Struktura_NVIC.NVIC_IRQChannel=DMA1_Channel7_IRQn;
	Struktura_NVIC.NVIC_IRQChannelCmd=ENABLE;
	Struktura_NVIC.NVIC_IRQChannelPreemptionPriority=1;
	Struktura_NVIC.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&Struktura_NVIC);

	// Configuring DMA for transmission
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	#endif
}

void UART_Send_int16(int16_t tx, char* buf, uint8_t d)
{
	sprintf_int(buf, tx, d);
	uint8_t i;
	for(i=0;buf[i]!='\0';i++)
	{
		USART_SendData(USARTx,buf[i]);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
	}
}

void UART_Send_int16_raw(int16_t tx)
{
	uint8_t MSB, LSB;

	LSB = tx & 0xFF;
	MSB = tx >> 8;

	UART_Send_char(LSB);
	UART_Send_char(MSB);
}

void UART_Send_char(char tx)
{
	USART_SendData(USARTx,tx);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
}

void UART_Send_LFCR()
{
	USART_SendData(USARTx,10);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
	USART_SendData(USARTx,13);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
}

void UART_Send_CRLF()
{
	USART_SendData(USARTx,13);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
	USART_SendData(USARTx,10);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
}

//Funkcja konwertujaca liczbe 8-bitowa (od -128 do 127) ze znakiem na ciag typu String
void sChar2Str(char *pStr, int value, int charCount)
{
	//Ilosc rozrzadow konwertowanej liczby (bez uwzgledniania znaku)
	//unsigned char charCount=4;
	int a=charCount-1;

	//Jezeli wartosc jest ujemna to zapisz znak '-'
	if(value < 0)	*pStr = '-';
	else 	*pStr = ' ';

	//Ustaw wskaznik na adres komorki zawierajacej najmlodszy rozrzad liczby
	pStr = pStr + charCount + 1;
	*pStr = '\0';
	pStr--;

	//Konwertuj liczbe; jednosci, dziesiatki, setki
	do
	{
		*pStr-- = abs(value % 10) + '0';
		value /= 10;
	}
	while(--charCount);

	pStr++;
	while(charCount<a)
	{
		if(*pStr != '0') break;
		else *pStr=' ';
		pStr++;
		charCount++;
	}
}

/**
  * @brief  moj_sprintf
  * @param  *wsk 	- wskaŸnik do tablicy char
  * @param  liczba 	- liczba do przekonwertowania do tablicy char
  * @param  d 		- liczba miejsc ca³kowitych
  * @param  p 		- liczba miejsc po przecinku
  *
  * @retval None
  */
void moj_sprintf(char *wsk, float liczba, uint8_t d, uint8_t p)
{
	int i;
	for(i=0;i<p;i++)
	{
		liczba*=10;
	}

	int liczba_int=(int)(liczba);
	if(p)
	{
		wsk++;
	}
	wsk = wsk + p + d + 1;
	*wsk = '\0';
	wsk--;

	//Konwertuj liczbe; jednosci, dziesiatki, setki
	i= p + d;

	do
	{
		if(p && i==d)
		{
			*wsk='.';
			wsk--;
		}
		*wsk-- = abs(liczba_int % 10) + '0';
		liczba_int /= 10;
	}
	while(--i);

	wsk++;
	while(i<d-1)
	{
		if(*wsk != '0')
		{
			break;
		}
		else *wsk=' ';
		wsk++;
		i++;
	}
}

void sprintf_int(char* ptr, int16_t number, uint8_t d)
{
	int16_t copy=number;

	ptr = ptr + d + 1;
	*ptr = '\0';
	ptr--;

	uint8_t i=d;
	do
	{
		*ptr-- = abs(copy % 10) + '0';
		copy /= 10;
	}
	while(i--);

	i++;
	ptr++;
	while(i<=d-1)
	{
		if(*ptr != '0')
		{
			if(number<0)
			{
				ptr--;
				*ptr='-';
			}
			break;
		}
		else *ptr=' ';
		ptr++;
		i++;
	}
}

void UART_Send_byte_in_asciiHex(uint8_t byte)
{
	uint8_t second = (byte%16);
	uint8_t first = (byte/16);

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

	UART_Send_char(first);
	UART_Send_char(second);
}

void UART_send_halfWord_in_asciiHex(int16_t halfWord)
{
	UART_Send_byte_in_asciiHex((uint8_t)(halfWord >> 8));
	UART_Send_byte_in_asciiHex((uint8_t)(halfWord & 0xFF));
}


