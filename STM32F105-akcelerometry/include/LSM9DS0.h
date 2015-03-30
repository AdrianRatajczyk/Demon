/*
 * LSM9DS0.h
 *
 *  Created on: 09 mar 2015
 *      Author: Adrian Ratajczyk
 */

#ifndef LSM9DS0_H_
#define LSM9DS0_H_

/*---------------------------------------------------------------------------------------------------------------------+
| SPI settings
+---------------------------------------------------------------------------------------------------------------------*/

#define LSM9DS0_SPI_CPOL							SPI_CPOL_High
#define LSM9DS0_SPI_CPHA							SPI_CPHA_2Edge

/*---------------------------------------------------------------------------------------------------------------------+
| Register mapping
+---------------------------------------------------------------------------------------------------------------------*/

#define LSM9DS0_READ								(1 << 7)
#define LSM9DS0_WRITE								0
#define LSM9DS0_SINGLE_BYTE							0
#define LSM9DS0_MULTIPLE_BYTE						(1 << 6)

#define LSM9DS0_WHO_AM_I_G 							0x0F
#define LSM9DS0_CTRL_REG1_G							0x20
#define LSM9DS0_CTRL_REG2_G 						0x21
#define LSM9DS0_CTRL_REG3_G  						0x22
#define LSM9DS0_CTRL_REG4_G 						0x23
#define LSM9DS0_CTRL_REG5_G 						0x24
#define LSM9DS0_REFERENCE_G 						0x25
#define LSM9DS0_STATUS_REG_G  						0x27
#define LSM9DS0_OUT_X_L_G  							0x28
#define LSM9DS0_OUT_X_H_G  							0x29
#define LSM9DS0_OUT_Y_L_G 							0x2A
#define LSM9DS0_OUT_Y_H_G 							0x2B
#define LSM9DS0_OUT_Z_L_G    						0x2C
#define LSM9DS0_OUT_Z_H_G 							0x2D
#define LSM9DS0_FIFO_CTRL_REG_G 					0x2E
#define LSM9DS0_FIFO_SRC_REG_G 						0x2F
#define LSM9DS0_INT1_CFG_G 							0x30
#define LSM9DS0_INT1_SRC_G 							0x31
#define LSM9DS0_INT1_TSH_XH_G  						0x32
#define LSM9DS0_INT1_TSH_XL_G 						0x33
#define LSM9DS0_INT1_TSH_YH_G  						0x34
#define LSM9DS0_INT1_TSH_YL_G  						0x35
#define LSM9DS0_INT1_TSH_ZH_G  						0x36
#define LSM9DS0_INT1_TSH_ZL_G  						0x37
#define LSM9DS0_INT1_DURATION_G 					0x38

#define LSM9DS0_OUT_TEMP_L_XM 						0x05
#define LSM9DS0_OUT_TEMP_H_XM 						0x06
#define LSM9DS0_STATUS_REG_M      			        0x07
#define LSM9DS0_OUT_X_L_M  							0x08
#define LSM9DS0_OUT_X_H_M 							0x09
#define LSM9DS0_OUT_Y_L_M  							0x0A
#define LSM9DS0_OUT_Y_H_M  							0x0B
#define LSM9DS0_OUT_Z_L_M  							0x0C
#define LSM9DS0_OUT_Z_H_M  							0x0D

#define LSM9DS0_WHO_AM_I_XM 						0x0F
#define LSM9DS0_INT_CTRL_REG_M 						0x12
#define LSM9DS0_INT_SRC_REG_M  						0x13
#define LSM9DS0_INT_THS_L_M 						0x14
#define LSM9DS0_INT_THS_H_M 						0x15
#define LSM9DS0_OFFSET_X_L_M  						0x16
#define LSM9DS0_OFFSET_X_H_M  						0x17
#define LSM9DS0_OFFSET_Y_L_M  						0x18
#define LSM9DS0_OFFSET_Y_H_M 						0x19
#define LSM9DS0_OFFSET_Z_L_M  						0x1A
#define LSM9DS0_OFFSET_Z_H_M  						0x1B
#define LSM9DS0_REFERENCE_X  						0x1C
#define LSM9DS0_REFERENCE_Y  						0x1D
#define LSM9DS0_REFERENCE_Z  						0x1E
#define LSM9DS0_CTRL_REG0_XM  						0x1F
#define LSM9DS0_CTRL_REG1_XM  						0x20
#define LSM9DS0_CTRL_REG2_XM  						0x21
#define LSM9DS0_CTRL_REG3_XM  						0x22
#define LSM9DS0_CTRL_REG4_XM  						0x23
#define LSM9DS0_CTRL_REG5_XM  						0x24
#define LSM9DS0_CTRL_REG6_XM  						0x25
#define LSM9DS0_CTRL_REG7_XM 						0x26

#define LSM9DS0_STATUS_REG_A 						0x27
#define LSM9DS0_OUT_X_L_A 							0x28
#define LSM9DS0_OUT_X_H_A 							0x29
#define LSM9DS0_OUT_Y_L_A 							0x2A
#define LSM9DS0_OUT_Y_H_A  							0x2B
#define LSM9DS0_OUT_Z_L_A  							0x2C
#define LSM9DS0_OUT_Z_H_A 							0x2D
#define LSM9DS0_FIFO_CTRL_REG  						0x2E
#define LSM9DS0_FIFO_SRC_REG   						0x2F
#define LSM9DS0_INT_GEN_1_REG   					0x30
#define LSM9DS0_INT_GEN_1_SRC  						0x31
#define LSM9DS0_INT_GEN_1_THS 						0x32
#define LSM9DS0_INT_GEN_1_DURATION  				0x33
#define LSM9DS0_INT_GEN_2_REG   					0x34
#define LSM9DS0_INT_GEN_2_SRC  						0x35
#define LSM9DS0_INT_GEN_2_THS  						0x36
#define LSM9DS0_INT_GEN_2_DURATION  				0x37
#define LSM9DS0_CLICK_CFG  							0x38
#define LSM9DS0_CLICK_SRC  							0x39
#define LSM9DS0_CLICK_THS  							0x3A
#define LSM9DS0_TIME_LIMIT 	 						0x3B
#define LSM9DS0_TIME_LATENCY  						0x3C
#define LSM9DS0_TIME_WINDOW  						0x3D
#define LSM9DS0_Act_THS  							0x3E
#define LSM9DS0_Act_DUR  							0x3F

/**
 * CTRL_REG1_G bit definition
 */
#define LSM9DS0_CTRL_REG1_G_Yen						1
#define LSM9DS0_CTRL_REG1_G_Xen						2
#define LSM9DS0_CTRL_REG1_G_Zen						4
#define LSM9DS0_CTRL_REG1_G_PD						8
#define LSM9DS0_CTRL_REG1_G_BW0						16
#define LSM9DS0_CTRL_REG1_G_BW1						32
#define LSM9DS0_CTRL_REG1_G_DR0						64
#define LSM9DS0_CTRL_REG1_G_DR1						128

// Output data rate for gyroscope
#define LSM9DS0_CTRL_REG1_G_DR_95Hz					(0b00 << 6)
#define LSM9DS0_CTRL_REG1_G_DR_190Hz				(0b01 << 6)
#define LSM9DS0_CTRL_REG1_G_DR_380Hz				(0b10 << 6)
#define LSM9DS0_CTRL_REG1_G_DR_760Hz				(0b11 << 6)

//#define CTRL_REG1_G_BW_12Hz				(0b00 << 4)
//#define CTRL_REG1_G_BW_25Hz				(0b01 << 4)
//#define CTRL_REG1_G_BW_50Hz				(0b10 << 4)
//#define CTRL_REG1_G_BW_70Hz				(0b11 << 4)

/**
 * CTRL_REG1_XM bit definition
 */
#define LSM9DS0_CTRL_REG1_XM_AXEN					1
#define LSM9DS0_CTRL_REG1_XM_AYEN					2
#define LSM9DS0_CTRL_REG1_XM_AZEN					4
#define LSM9DS0_CTRL_REG1_XM_BDU					8
#define LSM9DS0_CTRL_REG1_XM_AODR0					16
#define LSM9DS0_CTRL_REG1_XM_AODR1					32
#define LSM9DS0_CTRL_REG1_XM_AODR2					64
#define LSM9DS0_CTRL_REG1_XM_AODR3					128

// Output data rate for accelerometer
#define LSM9DS0_CTRL_REG1_XM_AODR_PD				(0b0000 << 4)
#define LSM9DS0_CTRL_REG1_XM_AODR_3Hz				(0b0001 << 4)
#define LSM9DS0_CTRL_REG1_XM_AODR_6Hz				(0b0010 << 4)
#define LSM9DS0_CTRL_REG1_XM_AODR_12Hz				(0b0011 << 4)
#define LSM9DS0_CTRL_REG1_XM_AODR_25Hz				(0b0100 << 4)
#define LSM9DS0_CTRL_REG1_XM_AODR_50Hz				(0b0101 << 4)
#define LSM9DS0_CTRL_REG1_XM_AODR_100Hz				(0b0110 << 4)
#define LSM9DS0_CTRL_REG1_XM_AODR_200Hz				(0b0111 << 4)
#define LSM9DS0_CTRL_REG1_XM_AODR_400Hz				(0b1000 << 4)
#define LSM9DS0_CTRL_REG1_XM_AODR_800Hz				(0b1001 << 4)
#define LSM9DS0_CTRL_REG1_XM_AODR_1600Hz			(0b1010 << 4)



/*---------------------------------------------------------------------------------------------------------------------+
| global functions' prototypes
+---------------------------------------------------------------------------------------------------------------------*/

void LSM9DS0_Init(void);

void LSM9DS0_Gyro_Read(int16_t *x, int16_t *y, int16_t *z);

void LSM9DS0_Acc_Read(int16_t *x, int16_t *y, int16_t *z);

void LSM9DS0_Magn_Read(int16_t *x, int16_t *y, int16_t *z);

/*---------------------------------------------------------------------------------------------------------------------+
| private functions' prototypes
+---------------------------------------------------------------------------------------------------------------------*/

static void LSM9DS0_SPI_Init();

static void LSM9DS0_XM_SpiRead(uint8_t* rx, uint8_t number);

static void LSM9DS0_G_SpiRead(uint8_t* rx, uint8_t number);

static void LSM9DS0_SpiSend(uint8_t* tx, uint8_t number);

static void LSM9DS0_XM_SpiStart();

static void LSM9DS0_G_SpiStart();

static void LSM9DS0_XM_SpiStop();

static void LSM9DS0_G_SpiStop();


#endif /* ADXL343_H_ */
