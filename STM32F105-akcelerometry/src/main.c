#include "stm32f10x.h"
#include <stdio.h>
#include "ADXL343.h"
#include "spi.h"
#include "config.h"
#include "stm32f10x_usart.h"
#include "uart.h"
#include "pomiar.h"

/*---------------------------------------------------------------------------------------------------------------------+
| global functions' prototypes
+---------------------------------------------------------------------------------------------------------------------*/

void Periph_Initialize();

/*static void Delay(__IO uint32_t nTime);

static void TimingDelay_Decrement(void);

void SysTick_Handler(void);*/


int main(void)
{
  /*
   * At this stage the microcontroller clock setting is already configured,
   * this is done through SystemInit() function which is called from startup
   * file (startup_cm.c) before to branch to application main.
   * To reconfigure the default setting of SystemInit() function, refer to
   * system_stm32f10x.c file
   */

   /* Use SysTick as reference for the timer */
   SysTick_Config(SystemCoreClock / SYSTICK_FREQUENCY_HZ);

   Periph_Initialize();

   int16_t x;
   int16_t y;
   int16_t z;

   uint32_t i;

   pomiar();

   while (1)
   {
	   ADXL343_Read(&x, &y, &z);

	   USART_SendData(USARTx, 65);

	   for(i=0;i<1000000;i++);
   }
}

// ----------------------------------------------------------------------------

void Periph_Initialize()
{
	SPI_Initialize();

	ADXL343_Init();

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

// ----------------------------------------------------------------------------


