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


/*****************************************************************************************************
 * 									APIs supported by this driver
 * 			For more information about the APIs check the function definitions
 *****************************************************************************************************/
/*
 * Peripheral Clock setup
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
/*
 * Init and De-init
 */
void SPI_Init(SPI_RegDef_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*
 * Data Send and Receive
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer,uint32_t Length);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer,uint32_t Length);


/*
 * IRQ Configuration and ISR handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandle(SPI_Handle_t *pHandle);

/*
 * Other Peripheral and ISR handling
 */
#endif /* INC_STM32F407XX_DRIVER_SPI_DRIVER_H_ */
