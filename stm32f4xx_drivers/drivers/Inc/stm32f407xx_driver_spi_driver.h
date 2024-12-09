/*
 * stm32f407xx_driver_spi_driver.h
 *
 *  Created on: Dec 5, 2024
 *      Author: MONSTER
 */

#ifndef INC_STM32F407XX_DRIVER_SPI_DRIVER_H_
#define INC_STM32F407XX_DRIVER_SPI_DRIVER_H_

#include "stm32f407xx.h"

/*
 * This is a Configuration structure for a SPIx peripheral
 */
typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_DFF;
	uint8_t SPI_CPHA;
	uint8_t SPI_CPOL;
	uint8_t SPI_SSM;
	uint8_t SPI_SclkSpeed;
}SPI_Config_t;

/*
 *  This is a Handle structure for a SPIx peripheral
 */
typedef struct
{
	SPI_RegDef_t *pSPIx;
	SPI_Config_t SPI_Config;
}SPI_Handle_t;


#endif /* INC_STM32F407XX_DRIVER_SPI_DRIVER_H_ */
