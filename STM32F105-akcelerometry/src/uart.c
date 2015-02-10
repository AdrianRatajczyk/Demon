#include "stm32f10x_gpio.h"
#include "config.h"
#include "uart.h"
#include "stm32f10x_usart.h"

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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

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


