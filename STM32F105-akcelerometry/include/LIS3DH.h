#ifndef LIS3DH_H_
#define LIS3DH_H_

/*---------------------------------------------------------------------------------------------------------------------+
| SPI settings
+---------------------------------------------------------------------------------------------------------------------*/

#define LIS3DH_SPI_CPOL							SPI_CPOL_High
#define LIS3DH_SPI_CPHA							SPI_CPHA_2Edge

#define LIS3DH_READ									(1 << 7)
#define LIS3DH_WRITE								0
#define LIS3DH_SINGLE_BYTE							0
#define LIS3DH_MULTIPLE_BYTE						(1 << 6)


/*---------------------------------------------------------------------------------------------------------------------+
| Register adresses
+---------------------------------------------------------------------------------------------------------------------*/

#define LIS3DH_STATUS_REG_AUX						0x07
#define LIS3DH_OUT_ADC1_L							0x08
#define LIS3DH_OUT_ADC1_H							0x09
#define LIS3DH_OUT_ADC2_L							0x0A
#define LIS3DH_OUT_ADC2_H							0x0B
#define LIS3DH_OUT_ADC3_L							0x0C
#define LIS3DH_OUT_ADC3_H							0x0D
#define LIS3DH_INT_COUNTER_REG						0x0E
#define LIS3DH_WHO_AM_I								0x0F
#define LIS3DH_TEMP_CFG_REG							0x1F
#define LIS3DH_CTRL_REG1							0x20
#define LIS3DH_CTRL_REG2							0x21
#define LIS3DH_CTRL_REG3							0x22
#define LIS3DH_CTRL_REG4							0x23
#define LIS3DH_CTRL_REG5							0x24
#define LIS3DH_CTRL_REG6							0x25
#define LIS3DH_REFERENCE							0x26
#define LIS3DH_STATUS_REG2							0x27
#define LIS3DH_OUT_X_L								0x28
#define LIS3DH_OUT_X_H								0x29
#define LIS3DH_OUT_Y_L								0x2A
#define LIS3DH_OUT_Y_H								0x2B
#define LIS3DH_OUT_Z_L								0x2C
#define LIS3DH_OUT_Z_H								0x2D
#define LIS3DH_FIFO_CTRL_REG						0x2E
#define LIS3DH_FIFO_SRC_REG							0x2F
#define LIS3DH_INT1_CFG								0x30
#define LIS3DH_INT1_SOURCE							0x31
#define LIS3DH_INT1_THS								0x32
#define LIS3DH_INT1_DURATION						0x33
#define LIS3DH_CLICK_CFG							0x38
#define LIS3DH_CLICK_SRC							0x39
#define LIS3DH_CLICK_THS							0x3A
#define LIS3DH_TIME_LIMIT							0x3B
#define LIS3DH_TIME_LATENCY							0x3C
#define LIS3DH_TIME_WINDOW							0x3D

#define LIS3DH_NAME									51

#define LIS3DH_TEMP_CFG_REG_ADC_PD					(1 << 7)	// ADC enable bit in TEMP_CFG_REG
#define LIS3DH_TEMP_CFG_REG_TEMP_EN					(1 << 6)	// Temperature sensor enable bit in TEMP_CFG_REG

#define LIS3DH_CTRL_REG1_ZEN						4
#define LIS3DH_CTRL_REG1_YEN						2
#define LIS3DH_CTRL_REG1_XEN						1
#define LIS3DH_CTRL_REG1_LOW_POWER					(0 << 4)	// Low power mode enable bit in CTRL_REG1
#define LIS3DH_CTRL_REG1_1_HZ						(1 << 4)
#define LIS3DH_CTRL_REG1_10_HZ						(2 << 4)
#define LIS3DH_CTRL_REG1_25_HZ						(3 << 4)
#define LIS3DH_CTRL_REG1_50_HZ						(4 << 4)
#define LIS3DH_CTRL_REG1_100_HZ						(5 << 4)
#define LIS3DH_CTRL_REG1_200_HZ						(6 << 4)
#define LIS3DH_CTRL_REG1_400_HZ						(7 << 4)
#define LIS3DH_CTRL_REG1_1600_HZ					(8 << 4)
#define LIS3DH_CTRL_REG1_5000_HZ					(9 << 4)


/*---------------------------------------------------------------------------------------------------------------------+
| global functions' prototypes
+---------------------------------------------------------------------------------------------------------------------*/

uint8_t LIS3DH_Init(void);

void LIS3DH_Read(int16_t *x, int16_t *y, int16_t *z);

#endif /* LIS3DH_H_ */
