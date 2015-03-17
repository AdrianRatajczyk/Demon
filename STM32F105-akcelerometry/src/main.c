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

/*---------------------------------------------------------------------------------------------------------------------+
| global functions' prototypes
+---------------------------------------------------------------------------------------------------------------------*/

void Periph_Initialize();

void konf_zegary();
/*static void Delay(__IO uint32_t nTime);

static void TimingDelay_Decrement(void);

void SysTick_Handler(void);*/

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

	konf_zegary();

	/* Use SysTick as reference for the timer */
	//SysTick_Config(SystemCoreClock / SYSTICK_FREQUENCY_HZ);
	SysTick_Config(8000);

	Periph_Initialize();

	int16_t x;
	int16_t y;
	int16_t z;

	uint32_t i;

	char buf[20];

	//pomiar();

	while (1)
	{
		//LSM9DS0_Gyro_Read(&x, &y, &z);
		//LSM9DS0_Acc_Read(&x, &y, &z);
		LSM9DS0_Magn_Read(&x, &y, &z);
		//ADXL343_Read(&x, &y, &z);

		//LIS3DH_Read(&x, &y, &z);

		//USART_SendData(USARTx, 65);

		UART_Send_int16(x, buf, 6);

		UART_Send_int16(y, buf, 6);

		UART_Send_int16(z, buf, 6);

		UART_Send_CRLF();

		for(i=0;i<10000;i++);
	}
}

// ----------------------------------------------------------------------------

void Periph_Initialize()
{
	//SPI_Initialize();

	LSM9DS0_Init();

	//ADXL343_Init();

	//LIS3DH_Init();

	UART_Initialize();
}


//static __IO uint32_t uwTimingDelay;

/**
 * @brief  Inserts a delay time.
 * @param  nTime: specifies the delay time length, in SysTick ticks.
 * @retval None
 */
/*void Delay(__IO uint32_t nTime)
{
  uwTimingDelay = nTime;

  while (uwTimingDelay != 0)
    ;
}*/

/**
 * @brief  Decrements the TimingDelay variable.
 * @param  None
 * @retval None
 */
/*void TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
    {
      uwTimingDelay--;
    }
}*/

// ----------------------------------------------------------------------------

/**
 * @brief  This function is the SysTick Handler.
 * @param  None
 * @retval None
 */
/*void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}*/

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


