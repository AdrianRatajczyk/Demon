#ifndef CONFIG_H_
#define CONFIG_H_

#include "stm32f10x_rcc.h"

/*---------------------------------------------------------------------------------------------------------------------+
| Systick
+---------------------------------------------------------------------------------------------------------------------*/

#define SYSTICK_FREQUENCY_HZ       		1000

/*---------------------------------------------------------------------------------------------------------------------+
| SPI
+---------------------------------------------------------------------------------------------------------------------*/

#define SPIx							SPI1

#define SPIx_RCC_GPIO					RCC_APB2Periph_GPIOA

#define SPIx_GPIO						GPIOA
#define SPIx_GPIO_SPEED					GPIO_Speed_50MHz

#define	SPIx_NSS_PIN					GPIO_Pin_4
#define SPIx_NSS_MODE					GPIO_Mode_Out_PP
#define SPIx_SCLK_PIN					GPIO_Pin_5
#define SPIx_SCLK_MODE					GPIO_Mode_AF_PP
#define	SPIx_MISO_PIN					GPIO_Pin_6
#define SPIx_MISO_MODE					GPIO_Mode_AF_OD
#define SPIx_MOSI_PIN					GPIO_Pin_7
#define SPIx_MOSI_MODE					GPIO_Mode_AF_PP

#define SPIx_DIRECTION					SPI_Direction_2Lines_FullDuplex
#define SPIx_MODE                		SPI_Mode_Master
#define SPIx_DATASIZE        			SPI_DataSize_8b
#define SPIx_CPOL						SPI_CPOL_High   //SPI_CPOL_Low
#define SPIx_CPHA        				SPI_CPHA_2Edge  //SPI_CPHA_1Edge
#define SPIx_NSS						SPI_NSS_Soft
#define SPIx_BAUDRATEPRESCALLER   		SPI_BaudRatePrescaler_2
#define SPIx_FIRSTBIT					SPI_FirstBit_MSB

/*---------------------------------------------------------------------------------------------------------------------+
| SPI2
+---------------------------------------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------------------------------------+
| USART
+---------------------------------------------------------------------------------------------------------------------*/

#define USARTx									USART2

#define USARTx_RCC_GPIO							RCC_APB2Periph_GPIOA

#define USARTx_GPIO								GPIOA
#define USARTx_GPIO_SPEED						GPIO_Speed_50MHz

#define USARTx_TX_PIN							GPIO_Pin_2
#define USARTx_TX_MODE							GPIO_Mode_AF_PP
#define USARTx_RX_PIN							GPIO_Pin_3
#define USARTx_RX_MODE							GPIO_Mode_AF_PP

#define USARTx_BAUDRATE           	 			115200
#define USARTx_WORDLENGTH         				USART_WordLength_8b
#define USARTx_STOPBITS           				USART_StopBits_1
#define USARTx_PARITY           				USART_Parity_No
#define USARTx_MODE            					USART_Mode_Rx | USART_Mode_Tx
#define USARTx_HARDWAREFLOWCONTROL				USART_HardwareFlowControl_None

#define USARTx_IT								USART_IT_RXNE

#define USARTx_NVIC_IRQCHannel						USART2_IRQn
#define USARTx_NVIC_IRQChannelPreemptionPriority	1
#define USARTx_NVIC_IRQChannelSubPriority			1
#define USARTx_NVIC_IRQChannelCmd					ENABLE


/*---------------------------------------------------------------------------------------------------------------------+
| LSM9DS0
+---------------------------------------------------------------------------------------------------------------------*/

#define LSM9DS0_CS_RCC_GPIO						RCC_APB2Periph_GPIOC
#define LSM9DS0_XM_RCC_GPIO						RCC_APB2Periph_GPIOB
#define LSM9DS0_G_RCC_GPIO						RCC_APB2Periph_GPIOA

#define LSM9DS0_XM_RCC_SPI						RCC_APB1Periph_SPI2
#define LSM9DS0_G_RCC_SPI						RCC_APB2Periph_SPI1

#define LSM9DS0_SPIx							SPI1
//#define LSM9DS0_SPI_XM							SPI2

#define LSM9DS0_GPIO_SPEED						GPIO_Speed_50MHz

#define LSM9DS0_CS_XM_GPIO						GPIOC
#define LSM9DS0_CS_XM_PIN						GPIO_Pin_0
#define LSM9DS0_CS_XM_MODE 						GPIO_Mode_Out_PP

#define LSM9DS0_CS_G_GPIO						GPIOC
#define LSM9DS0_CS_G_PIN						GPIO_Pin_1
#define LSM9DS0_CS_G_MODE 						GPIO_Mode_Out_PP

#define LSM9DS0_G_MISO_GPIO						GPIOA
#define LSM9DS0_G_MISO_PIN						GPIO_Pin_6
#define LSM9DS0_G_MISO_MODE						GPIO_Mode_AF_OD

#define LSM9DS0_XM_MISO_GPIO					GPIOB
#define LSM9DS0_XM_MISO_PIN						GPIO_Pin_14
#define LSM9DS0_XM_MISO_MODE					GPIO_Mode_AF_OD

#define LSM9DS0_MOSI_GPIO						GPIOA
#define LSM9DS0_MOSI_PIN						GPIO_Pin_7
#define LSM9DS0_MOSI_MODE						GPIO_Mode_AF_PP

#define LSM9DS0_SCLK_GPIO						GPIOA
#define LSM9DS0_SCLK_PIN						GPIO_Pin_5
#define LSM9DS0_SCLK_MODE						GPIO_Mode_AF_PP

#define LSM9DS0_SPI_G_DIRECTION					SPI_Direction_2Lines_FullDuplex
#define LSM9DS0_SPI_G_MODE                		SPI_Mode_Master
#define LSM9DS0_SPI_G_DATASIZE        			SPI_DataSize_8b
#define LSM9DS0_SPI_G_CPOL						SPI_CPOL_High   //SPI_CPOL_Low
#define LSM9DS0_SPI_G_CPHA        				SPI_CPHA_2Edge  //SPI_CPHA_1Edge
#define LSM9DS0_SPI_G_NSS						SPI_NSS_Soft
#define LSM9DS0_SPI_G_BAUDRATEPRESCALLER   		SPI_BaudRatePrescaler_2
#define LSM9DS0_SPI_G_FIRSTBIT					SPI_FirstBit_MSB

#define LSM9DS0_SPI_XM_DIRECTION				SPI_Direction_2Lines_FullDuplex
#define LSM9DS0_SPI_XM_MODE                		SPI_Mode_Master
#define LSM9DS0_SPI_XM_DATASIZE        			SPI_DataSize_8b
#define LSM9DS0_SPI_XM_CPOL						SPI_CPOL_High   //SPI_CPOL_Low
#define LSM9DS0_SPI_XM_CPHA        				SPI_CPHA_2Edge  //SPI_CPHA_1Edge
#define LSM9DS0_SPI_XM_NSS						SPI_NSS_Soft
#define LSM9DS0_SPI_XM_BAUDRATEPRESCALLER   	SPI_BaudRatePrescaler_2
#define LSM9DS0_SPI_XM_FIRSTBIT					SPI_FirstBit_MSB


#endif /* CONFIG_H_ */
