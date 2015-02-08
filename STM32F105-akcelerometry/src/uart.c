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
	USART_InitTypeDef Struktura_USART;

	Struktura_USART.USART_BaudRate=USARTx_BAUDRATE;
	Struktura_USART.USART_HardwareFlowControl=USARTx_HARDWAREFLOWCONTROL;
	Struktura_USART.USART_Mode=USARTx_MODE;
	Struktura_USART.USART_Parity=USARTx_PARITY;
	Struktura_USART.USART_StopBits=USARTx_STOPBITS;
	Struktura_USART.USART_WordLength=USARTx_WORDLENGTH;
	USART_Init(USARTx, &Struktura_USART);

	USART_Cmd(USARTx, ENABLE);
}
