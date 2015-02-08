#ifndef CONFIG_H_
#define CONFIG_H_

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


#endif /* CONFIG_H_ */
