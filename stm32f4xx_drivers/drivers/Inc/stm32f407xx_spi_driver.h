/*
 * stm32f407xx_driver_spi_driver.h
 *
 *  Created on: Dec 5, 2024
 *      Author: MONSTER
 */

#ifndef INC_STM32F407XX_SPI_DRIVER_H_
#define INC_STM32F407XX_SPI_DRIVER_H_

#include <stm32f407xx_i2c_driver.h>

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
	SPI_RegDef_t *pSPIx;		// This holds the base address of SPIx peripherals
	SPI_Config_t SPI_Config;
	uint8_t *pTxBuffer; 		// To store the app. Tx buffer address
	uint8_t *pRxBuffer; 		// To store the app. Rx buffer address
	uint8_t TxState;			// To store the Tx state
	uint8_t RxState;			// To store the Rx state
	uint8_t TxLength;				// To store the Tx Length
	uint8_t RxLength;				// To store the Rx Length

}SPI_Handle_t;

/*
 * @SPI_DeviceMode
 */
#define SPI_DEVICE_MODE_MASTER		1
#define SPI_DEVICE_MODE_SLAVE		0

/*
 * @SPI_BusConfig
 */
#define SPI_BUS_CONFIG_FD 					1
#define SPI_BUS_CONFIG_HD					2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY		3

/*
 * @SPI_DFF
 */
#define SPI_DFF_8BITS		0
#define SPI_DFF_16BITS		1

/*
 * @SPI_CPHA
 */
#define SPI_CPHA_HIGH		1
#define SPI_CPHA_LOW		0

/*
 * @SPI_CPOL
 */
#define SPI_CPOL_HIGH		1
#define SPI_CPOL_LOW		0

/*
 * @SPI_SSM
 */
#define SPI_SSM_EN			1
#define SPI_SSM_DIS			0

/*
 * @SPI_SclkSpeed
 */
#define SPI_SCLK_SPEED_DIV2				0
#define SPI_SCLK_SPEED_DIV4				1
#define SPI_SCLK_SPEED_DIV8				2
#define SPI_SCLK_SPEED_DIV16			3
#define SPI_SCLK_SPEED_DIV32			4
#define SPI_SCLK_SPEED_DIV64			5
#define SPI_SCLK_SPEED_DIV128			6
#define SPI_SCLK_SPEED_DIV256			7

/*
 * SPI related status flags definitions
 */
#define SPI_TXE_FLAG		(1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG		(1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG		(1 << SPI_SR_BSY)

/*
 * SPI application states
 */
#define SPI_READY				0
#define SPI_BUSY_IN_RX			1
#define SPI_BUSY_IN_TX			2

/*
 *  Possible SPI Application events
 */
#define SPI_EVENT_TX_COMPLT			1
#define SPI_EVENT_RX_COMPLT			2
#define SPI_EVENT_OVR_COMPLT		3
#define SPI_EVENT_CRC_COMPLT		4

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
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*
 * Data Send and Receive
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer,uint32_t Length);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer,uint32_t Length);

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer,uint32_t Length);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer,uint32_t Length);


/*
 * IRQ Configuration and ISR handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandle(SPI_Handle_t *pHandle);

/*
 * Other Peripheral Control API's
 */
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);
void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx);
void SPI_CloseTransmission(SPI_Handle_t *pHandle);
void SPI_CloseReception(SPI_Handle_t *pHandle);

/*
 * Application callback
 */
void SPI_ApplicationEventCallback(SPI_Handle_t *pHandle, uint8_t AppEvent);

#endif /* INC_STM32F407XX_SPI_DRIVER_H_ */
