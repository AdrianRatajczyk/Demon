#include "stm32f10x.h"
#include <stdio.h>
#include "ADXL343.h"
#include "spi.h"
#include "config.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "uart.h"
#include "pomiar.h"
#include "LSM9DS0.h"
#include "MMA9551L.h"
#include "defines.h"
#include "LIS3DH.h"
#include "fifo.h"

/*---------------------------------------------------------------------------------------------------------------------+
| global functions' prototypes
+---------------------------------------------------------------------------------------------------------------------*/

void Periph_Initialize();

void konf_zegary();

void Delay(__IO uint32_t nTime);

static void TimingDelay_Decrement(void);

void SysTick_Handler(void);

//volatile char buf[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int main(void)
{
  /*
   * At this stage the microcontroller clock setting is already configured,
   * this is done through SystemInit() function which is called from startup
   * file (startup_cm.c) before to branch to application main.
   * To reconfigure the default setting of SystemInit() function, refer to
   * system_stm32f10x.c file
   */

	//konf_zegary();

	/* Use SysTick as reference for the timer */
	SysTick_Config(SystemCoreClock / SYSTICK_FREQUENCY_HZ);
	//SysTick_Config(72000);

	Periph_Initialize();

	int16_t x;
	int16_t y;
	int16_t z;

	uint32_t i;

	uint8_t a = 1;
	uint8_t b = 2;
	uint8_t c = 3;

	unsigned int l=0;

	char buf[20];

	Queue * kolejka = createQueue();

	kolejka->add(&a, 1, kolejka);
	kolejka->add(&b, 1, kolejka);
	kolejka->add(&c, 1, kolejka);

	Element e1;
	Element e2;
	Element e3;

	l=kolejka->getLength(kolejka);

	e1 = kolejka->get(kolejka);
	e2 = kolejka->get(kolejka);
	e3 = kolejka->get(kolejka);

	l=kolejka->getLength(kolejka);

	//pomiar();

	while (1)
	{
		UART_Send_char(65);
		buf[0]=USART_ReceiveData(USARTx);

//		if (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) != RESET)
//		{
//			uint16_t x = USART_ReceiveData(USARTx);
//
//		    while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
//
//		    USART_SendData(USARTx, x);
//		}
	}
}

// ----------------------------------------------------------------------------

void Periph_Initialize()
{
	SPI_Initialize(LSM9DS0_SPI_CPOL, LSM9DS0_SPI_CPHA);

	#if defined(ADXL343)
		ADXL343_Init();
	#elif defined(LSM9DS0)
		LSM9DS0_Init();
	#else
		LIS3DH_Init();
	#endif

	UART_Initialize();
}


static __IO uint32_t uwTimingDelay;

/**
 * @brief  Inserts a delay time.
 * @param  nTime: specifies the delay time length, in SysTick ticks.
 * @retval None
 */
void Delay(__IO uint32_t nTime)
{
  uwTimingDelay = nTime;

  while (uwTimingDelay != 0)
    ;
}

/**
 * @brief  Decrements the TimingDelay variable.
 * @param  None
 * @retval None
 */
void TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
    {
      uwTimingDelay--;
    }
}

// ----------------------------------------------------------------------------

/**
 * @brief  This function is the SysTick Handler.
 * @param  None
 * @retval None
 */
//void SysTick_Handler(void)
//{
//  TimingDelay_Decrement();
//}

void konf_zegary(void)
{
  ErrorStatus HSEStartUpStatus;

  // Reset ustawien RCC
  RCC_DeInit();
  // Wlacz HSE
  RCC_HSEConfig(RCC_HSE_ON);
  // Czekaj za HSE bedzie gotowy
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  if(HSEStartUpStatus == SUCCESS)
  {
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        // zwloka dla pamieci Flash
        FLASH_SetLatency(FLASH_Latency_2);
        // HCLK = SYSCLK
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        // PCLK2 = HCLK
        RCC_PCLK2Config(RCC_HCLK_Div1);
        // PCLK1 = HCLK/2
        RCC_PCLK1Config(RCC_HCLK_Div2);
        // PLLCLK = 8MHz * 9 = 72 MHz
        RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
        // Wlacz PLL
        RCC_PLLCmd(ENABLE);
        // Czekaj az PLL poprawnie sie uruchomi
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
        // PLL bedzie zrodlem sygnalu zegarowego
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        // Czekaj az PLL bedzie sygnalem zegarowym systemu
        while(RCC_GetSYSCLKSource() != 0x08);
  }
}

// ----------------------------------------------------------------------------


