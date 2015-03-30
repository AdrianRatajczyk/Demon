/*
 * MMA9551L.h
 *
 *  Created on: 25 mar 2015
 *      Author: Adrian Ratajczyk
 */

#ifndef MMA9551L_H_
#define MMA9551L_H_

/*---------------------------------------------------------------------------------------------------------------------+
| SPI settings
+---------------------------------------------------------------------------------------------------------------------*/

#define MMA9551L_SPI_CPOL							SPI_CPOL_High
#define MMA9551L_SPI_CPHA							SPI_CPHA_2Edge


/*---------------------------------------------------------------------------------------------------------------------+
| APP_ID definition
+---------------------------------------------------------------------------------------------------------------------*/

#define MMA9551L_VERSION_APP_ID							0x00
#define MMA9551L_SCHEDULER_APP_ID						0x01
#define MMA9551L_COMMUNICATIONS_APP_ID					0x02
#define MMA9551L_GPIO_APP_ID							0x03
#define MMA9551L_MAILBOX_APP_ID							0x04
#define MMA9551L_ANALOG_FRONT_END_APP_ID				0x06
#define MMA9551L_PORTRAIT_LANDSCAPE_APP_ID				0x07
#define MMA9551L_HIGH_G_DETECTION_APP_ID				0x08
#define MMA9551L_LOW_G_DETECTION_APP_ID					0x09
#define MMA9551L_TAP_DETECTION_APP_ID					0x0A
#define MMA9551L_TILT_APP_ID							0x0B
#define MMA9551L_FRAME_COUNTER_APP_ID					0x0E
#define MMA9551L_DATA_FIFO_APP_ID						0x0F
#define MMA9551L_EVENT_QUEUE_APP_ID						0x10
#define MMA9551L_STATUS_REGISTER_APP_ID					0x11
#define MMA9551L_SLEEP_AWAKE_APP_ID						0x12
#define MMA9551L_RESET_SUSPEND_CLEAR_APP_ID				0x17
#define MMA9551L_MBOX_CONFIG_APP_ID						0x18

/*---------------------------------------------------------------------------------------------------------------------+
| global functions' prototypes
+---------------------------------------------------------------------------------------------------------------------*/

void MMA9551L_SpiInit();

void MMA9551L_CheckVersion();

/*---------------------------------------------------------------------------------------------------------------------+
| private functions' prototypes
+---------------------------------------------------------------------------------------------------------------------*/

void MMA9551L_SpiRead(uint8_t* rx, uint8_t number);

void MMA9551L_SpiSend(uint8_t* tx, uint8_t number);

void MMA9551L_SpiStart();

void MMA9551L_SpiStop();



#endif /* MMA9551L_H_ */
