/*
 * stm32f407xx_i2c_driver.c
 *
 *  Created on: Apr 27, 2025
 *      Author: MONSTER
 */

#include "stm32f407xx_i2c_driver.h"

/*
 * Static functions
 */
static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr);
static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr);
static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx);
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= (1 << I2C_CR1_START);
}

static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
	SlaveAddr = SlaveAddr << 1;
	SlaveAddr |= 1;			// SlaveAddr is Slave address + R/nW bit = 1
	pI2Cx->DR = SlaveAddr;
}

static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
	SlaveAddr = SlaveAddr << 1;
	SlaveAddr &= ~(1);			// SlaveAddr is Slave address + R/nW bit = 0
	pI2Cx->DR = SlaveAddr;
}

static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx)
{
	uint32_t dummyRead = pI2Cx->SR1;
	dummyRead = pI2Cx->SR2;
	(void)dummyRead;
}

static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}





/*
 * Peripheral Clock setup
 */
/************************************************************************
 * @fn				- I2C_PeriClockControl
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
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_EN();
		}
		else if(pI2Cx == I2C2)
		{
			I2C2_PCLK_EN();
		}
		else if(pI2Cx == I2C3)
		{
			I2C3_PCLK_EN();
		}
	}
	else
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_DI();
		}
		else if(pI2Cx == I2C2)
		{
			I2C2_PCLK_DI();
		}
		else if(pI2Cx == I2C3)
		{
			I2C3_PCLK_DI();
		}
	}
}


/*
 * Init and De-init
 */
/************************************************************************
 * @fn				- I2C_Init
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
void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	uint32_t tempreg = 0;

	// enable the clock for the i2cx peripheral
	I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);

	// ack control bit
	tempreg |= pI2CHandle->I2C_Config.I2C_ACKControl << 10;
	pI2CHandle->pI2Cx->CR1 = tempreg;

	// configure the FREQ field of CR2
	tempreg = 0;
	tempreg |= RCC_GetPCLK1Value() / 100000U;
	pI2CHandle->pI2Cx->CR2 =  (tempreg & 0x3F);

	// program the device own address
	tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress << 1;
	tempreg |= (1 << 14);
	pI2CHandle->pI2Cx->OAR1 = tempreg;

	// CCR calculation
	int16_t ccr_value = 0;
	tempreg = 0;

	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	{
		// mode is standard mode
		ccr_value = (RCC_GetPCLK1Value() / ( 2 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
		tempreg |= (ccr_value & 0xFFF);
	}
	else
	{
		// mode is fast mode
		tempreg |= ( 1 << 15);
		tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14);

		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
		{
			ccr_value = (RCC_GetPCLK1Value() / ( 3 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
		}
		else
		{
			ccr_value = (RCC_GetPCLK1Value() / ( 25 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
		}

		tempreg |= (ccr_value & 0xFFF);
	}
	pI2CHandle->pI2Cx->CCR = tempreg;

	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
		{
			// mode is standard mode
			tempreg = (RCC_GetPCLK1Value() / 1000000U ) + 1;
		}
		else
		{
			// mode is fast mode
			tempreg = ( (RCC_GetPCLK1Value() * 300 )/ 1000000000U ) + 1;
		}
	pI2CHandle->pI2Cx->TRISE = tempreg & 0x3F;
}

/************************************************************************
 * @fn				- I2C_DeInit
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
void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{
	if(pI2Cx == I2C1)
	{
		I2C1_REG_RESET();
	}
	else if(pI2Cx == I2C2)
	{
		I2C2_REG_RESET();
	}
	else if(pI2Cx == I2C3)
	{
		I2C3_REG_RESET();
	}
}

/************************************************************************
 * @fn				- I2C_MasterSendData
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
void I2C_MasterSendData (I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr)
{

	//1. Generate the START condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//2. confirm that start generation is completed by checking the SB flag in the SR1
	//   Note: Until SB is cleared SCL will be stretched (pulled to LOW)
	while( !( I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB) ) );

	//3. Send the address of the slave with r/nw bit set to w(0) (total 8 bits )
	I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx, SlaveAddr);

	//4. Confirm that address phase is completed by checking the ADDR flag in the SR1
	while( !( I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR) ) );

	//5. clear the ADDR flag according to its software sequence
	//	 Note: Until ADDR is cleared SCL will be stretched (pulled to LOW)
	I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

	//6. send the data until Len becomes 0
	while(Len > 0)
	{
		while( !( I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE) ) ); // wait till TXE set
		pI2CHandle->pI2Cx->DR = *pTxBuffer;
		pTxBuffer++;
		Len--;
	}

	//7. when Len becomes zero wait for TXE=1 and BTF=1 before generating the STOP condition
	//	 Note: TXE=1 , BTF=1 , means that both SR and DR are empty and next transmission should begin
	//	 when BTF=1 SCL will be stretched (pulled to LOW)
	while( !( I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE) ) );
	while( !( I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF) ) );

	//8. Generate STOP condition and master need not to wait for the completion of stop condition.
	//	 Note: generating STOP, automatically clears the BTF
	if(Sr == I2C_DISABLE_SR)
		I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

}


/************************************************************************
 * @fn				- I2C_MasterReceiveData
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

void I2C_MasterReceiveData (I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr)
{
	// 1. Generate the START condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	// 2. Confirm that start generation is completed by checking the SB flag in the SR1
	// Note: Until SB is cleared SCL will be stretched (pulled to LOW)
	while( !( I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB) ) );

	// 3. Send the address of the slave with R/nW bit set  to R(1) (total 8 bits)
	I2C_ExecuteAddressPhaseRead(pI2CHandle->pI2Cx, SlaveAddr);

	// 4. Wait until address phase is completed by checking the ADDR flag is the SR1
	while( !( I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR) ) );

	// Procedure to read only 1 byte from slave
	if(Len == 1)
	{
		// Disable ACKing
		I2C_ManageACKing(pI2CHandle->pI2Cx,I2C_ACK_DISABLE);

		// Clear the ADDR flag
		I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

		// Wait until RXNE becomes 1
		while( !( I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE) ) ); // wait till RXNE set

		// Generate STOP condition
		if(Sr == I2C_DISABLE_SR)
			I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

		// Read data in to buffer
		*pRxBuffer = pI2CHandle->pI2Cx->DR;
	}

	// Procedure to read data from slave when Len > 1
	if(Len > 1)
	{
		// Clear the ADDR flag
		I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

		// Read the data until Len becomes zero
		for(uint32_t i = Len; i > 0; i--)
		{
			// Wait until RXNE becomes 1
			while( !( I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE) ) ); // wait till RXNE set

			if(i == 2) // If last 2 bytes are remaining
			{
				// Clear the ACK bit
				I2C_ManageACKing(pI2CHandle->pI2Cx,I2C_ACK_DISABLE);

				// Generate STOP condition
				if(Sr == I2C_DISABLE_SR)
					I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
			}

			// Read the data from register in to buffer
			*pRxBuffer = pI2CHandle->pI2Cx->DR;
			// Increment the buffer address
			*pRxBuffer++;
		}
	}

	// Re-enable ACKing
	if(pI2CHandle->I2C_Config.I2C_ACKControl == I2C_ACK_ENABLE)
	{
		I2C_ManageACKing(pI2CHandle->pI2Cx,I2C_ACK_ENABLE);
	}
}


void I2C_ManageACKing(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == I2C_ACK_ENABLE)
	{
		// Enable the ACK
		pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
	}
	else
	{
		// Disable the ACK
		pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
	}
}



/*
 * Other Peripheral and ISR handling
 */

/************************************************************************
 * @fn				- I2C_PeripheralControl
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
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pI2Cx->CR1 |= (1 << I2C_CR1_PE);
	}
	else
	{
		pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
	}

}



uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName)
{
	if(pI2Cx->SR1 & FlagName)
	{
		return FLAG_SET;
	}

	return FLAG_RESET;
}












