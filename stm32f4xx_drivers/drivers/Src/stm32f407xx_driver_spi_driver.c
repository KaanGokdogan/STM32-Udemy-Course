/*
 * stm32f407xx_driver_spi_driver.c
 *
 *  Created on: Dec 5, 2024
 *      Author: MONSTER
 */

#include <stm32f407xx_spi_driver.h>

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void  spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void  spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle);


uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}

	return FLAG_RESET;
}
/*
 * Peripheral Clock setup
 */
/************************************************************************
 * @fn				- SPI_PeriClockControl
 *
 * @brief			-
 *
 * @param[in]		-
 * @param[in]		-
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 ************************************************************************/
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
		else if(pSPIx == SPI4)
		{
			SPI4_PCLK_EN();
		}
	}
	else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_DI();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_DI();
		}
		else if(pSPIx == SPI4)
		{
			SPI4_PCLK_DI();
		}
	}
}
/*
 * Init and De-init
 */
/************************************************************************
 * @fn				- SPI_Init
 *
 * @brief			-
 *
 * @param[in]		-
 * @param[in]		-
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 ************************************************************************/
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	// Peripheral clock enable
	SPI_PeriClockControl(pSPIHandle->pSPIx , ENABLE);
	// first lets configure the SPI_CR1 register
	uint32_t tempReg = 0;

	// 1. Configure the device mode
	tempReg |= pSPIHandle->SPI_Config.SPI_DeviceMode << SPI_CR1_MSTR;

	// 2. Configure the bus config
	if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		// bidi mode should be cleared
		tempReg &= ~(1 << SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		// bidi mode should be set
		tempReg |= (1 << SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		// bidi mode should be cleared
		tempReg &= ~(1 << SPI_CR1_BIDIMODE);

		// bidi mode should be set
		tempReg |= (1 << SPI_CR1_RXONLY);
	}

	// 3. Configure the DFF
	tempReg |= pSPIHandle->SPI_Config.SPI_DFF << SPI_CR1_DFF;
	// 4 Configure the CPHA
	tempReg |= pSPIHandle->SPI_Config.SPI_CPHA << SPI_CR1_CPHA;
	// 5. Configure the CPOL
	tempReg |= pSPIHandle->SPI_Config.SPI_CPOL << SPI_CR1_CPOL;
	// 6. Configure the SPI serial clock speed (baud rate)
	tempReg |= pSPIHandle->SPI_Config.SPI_SclkSpeed << SPI_CR1_BR;

	pSPIHandle->pSPIx->CR1 = tempReg;




}

/************************************************************************
 * @fn				- SPI_DeInit
 *
 * @brief			-
 *
 * @param[in]		-
 * @param[in]		-
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 ************************************************************************/
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1)
	{
		SPI1_REG_RESET();
	}
	else if(pSPIx == SPI2)
	{
		SPI2_REG_RESET();
	}
	else if(pSPIx == SPI3)
	{
		SPI3_REG_RESET();
	}
	else if(pSPIx == SPI4)
	{
		SPI4_REG_RESET();
	}
}

/*
 * Data Send and Receive
 */
/************************************************************************
 * @fn				- SPI_SendData
 *
 * @brief			-
 *
 * @param[in]		-
 * @param[in]		-
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- This is blocking call
 ************************************************************************/
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer,uint32_t Length)
{
	while(Length > 0)
	{
		// 1. Wait until TXE is set
		// potential to block permanently, POLLING
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

		// 2. check the DFF bit in CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			// 16 bit DFF
			// 1. load the data in to the DR
			pSPIx->DR = *( (uint16_t*)pTxBuffer);
			Length--;
			Length--;
			(uint16_t*)pTxBuffer++;
		}
		else
		{
			// 8 bit DFF
			pSPIx->DR = *pTxBuffer;
			Length--;
			pTxBuffer++;
		}
	}
}
/************************************************************************
 * @fn				- SPI_ReceiveData
 *
 * @brief			-
 *
 * @param[in]		-
 * @param[in]		-
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 ************************************************************************/
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer,uint32_t Length)
{

}


/*
 * IRQ Configuration and ISR handling
 */
/************************************************************************
 * @fn				- SPI_IRQInterruptConfig
 *
 * @brief			-
 *
 * @param[in]		-
 * @param[in]		-
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 ************************************************************************/
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{

}
/************************************************************************
 * @fn				- SPI_IRQPriorityConfig
 *
 * @brief			-
 *
 * @param[in]		-
 * @param[in]		-
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 ************************************************************************/
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{

}
/************************************************************************
 * @fn				- SPI_IRQHandle
 *
 * @brief			-
 *
 * @param[in]		-
 * @param[in]		-
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 ************************************************************************/
void SPI_IRQHandle(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp1, temp2;
	//first lets check for TXE
	temp1 = pSPIHandle->pSPIx->SR & ( 1 << SPI_SR_TXE);
	temp2 = pSPIHandle->pSPIx->CR2 & ( 1 << SPI_CR2_TXEIE);

	if(temp1 && temp2)
	{
		// handle TXE
		spi_txe_interrupt_handle(pSPIHandle);
	}

	//check for RXNE
	temp1 = pSPIHandle->pSPIx->SR & ( 1 << SPI_SR_RXNE);
	temp2 = pSPIHandle->pSPIx->CR2 & ( 1 << SPI_CR2_RXNEIE);

	if(temp1 && temp2)
	{
		// handle RXNE
		spi_rxne_interrupt_handle(pSPIHandle);
	}

	//check for ovr flag
	temp1 = pSPIHandle->pSPIx->SR & ( 1 << SPI_SR_OVR);
	temp2 = pSPIHandle->pSPIx->CR2 & ( 1 << SPI_CR2_ERRIE);

	if(temp1 && temp2)
	{
		// handle ovr error
		spi_ovr_err_interrupt_handle(pSPIHandle);
	}
}

// Some helper function implementations
static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	// 2. check the DFF bit in CR1
	if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))
	{
		// 16 bit DFF
		// 1. load the data in to the DR
		pSPIHandle->pSPIx->DR = *( (uint16_t*)pSPIHandle->pTxBuffer);
		pSPIHandle->TxLength--;
		pSPIHandle->TxLength--;
		(uint16_t*)pSPIHandle->pTxBuffer++;
	}
	else
	{
		// 8 bit DFF
		pSPIHandle->pSPIx->DR = *pSPIHandle->pTxBuffer;
		pSPIHandle->TxLength--;
		pSPIHandle->pTxBuffer++;
	}

	if(pSPIHandle->TxLength)
	{
		// TxLength is zero so close the spi transmission and inform the application that
		// Tx is over
		// this prevents interrupts from setting up of TXE flag

		SPI_CloseTransmission(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_TX_COMPLT);
	}
}
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	// do rxing as per dff
	if(pSPIHandle->pSPIx->CR1 & (1 << 11))
	{
		// 16 bit DFF
		*( (uint16_t*)pSPIHandle->pRxBuffer) = *( (uint16_t*)pSPIHandle->pSPIx->DR);
		pSPIHandle->RxLength -=2;
		pSPIHandle->pRxBuffer--;
		pSPIHandle->pRxBuffer--;
	}
	else
	{
		// 8 bit
		*(pSPIHandle->pRxBuffer) = (uint8_t) pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLength--;
		pSPIHandle->pRxBuffer--;
	}

	if(! pSPIHandle->RxLength)
	{
		// reception is complete
		SPI_CloseReception(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_RX_COMPLT);
	}
}
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp;
	// 1. clear the ovr flag
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX)
	{
		temp = pSPIHandle->pSPIx->DR;
		temp = pSPIHandle->pSPIx->SR;
	}
	(void) temp;
	// 2. inform the application
	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_RX_COMPLT);

}

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &=  ~( 1 << SPI_CR2_TXEIE);
	pSPIHandle->pTxBuffer = NULL;
	pSPIHandle->TxLength = 0;
	pSPIHandle->TxState = SPI_READY;
}
void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &=  ~( 1 << SPI_CR2_RXNEIE);
	pSPIHandle->pRxBuffer = NULL;
	pSPIHandle->RxLength = 0;
	pSPIHandle->RxState = SPI_READY;
}

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{
	uint8_t temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;
	(void) temp;
}





/*
 * Other Peripheral and ISR handling
 */

/************************************************************************
 * @fn				- SPI_PeripheralControl
 *
 * @brief			-
 *
 * @param[in]		-
 * @param[in]		-
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 ************************************************************************/
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}

}

/************************************************************************
 * @fn				- SPI_SSIConfig
 *
 * @brief			-
 *
 * @param[in]		-
 * @param[in]		-
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 ************************************************************************/
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	}else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}


/************************************************************************
 * @fn				- SPI_SSOEConfig
 *
 * @brief			-
 *
 * @param[in]		-
 * @param[in]		-
 * @param[in]		-
 *
 * @return			- none
 *
 * @Note			- none
 ************************************************************************/
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	}else
	{
		pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	}
}

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer,uint32_t Length)
{
	uint8_t state = pSPIHandle->TxState;

	if(state != SPI_BUSY_IN_TX)
	{
		// 1. Save the Tx buffer address and Len information in some global variables
		pSPIHandle->pTxBuffer = pTxBuffer;
		pSPIHandle->TxLength = Length;

		// 2. Mark the SPI state as busy in transmission so that
		//	  no other code can take over same SPI peripheral until transmission is over
		pSPIHandle->TxState = SPI_BUSY_IN_TX;

		// 3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR
		pSPIHandle->pSPIx->CR2 |= ( 1 << SPI_CR2_TXEIE);

		// 4. Data transmission will be handled by the ISR code (will implement later)
	}


	return state;

}

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer,uint32_t Length)
{
	uint8_t state = pSPIHandle->RxState;

		if(state != SPI_BUSY_IN_RX)
		{
			// 1. Save the Tx buffer address and Len information in some global variables
			pSPIHandle->pRxBuffer = pRxBuffer;
			pSPIHandle->RxLength = Length;

			// 2. Mark the SPI state as busy in transmission so that
			//	  no other code can take over same SPI peripheral until transmission is over
			pSPIHandle->RxState = SPI_BUSY_IN_RX;

			// 3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR
			pSPIHandle->pSPIx->CR2 |= ( 1 << SPI_CR2_RXNEIE);

			// 4. Data transmission will be handled by the ISR code (will implement later)
		}


		return state;
}


__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pHandle, uint8_t AppEvent)
{
	// This is a weak implementation the application may override function
}
