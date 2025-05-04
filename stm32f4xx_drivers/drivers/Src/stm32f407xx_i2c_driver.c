/*
 * stm32f407xx_i2c_driver.c
 *
 *  Created on: Apr 27, 2025
 *      Author: MONSTER
 */

#include "stm32f407xx_i2c_driver.h"

uint16_t AHB_PreScaler[8] = {2, 4, 8, 16, 64, 128, 256, 512};
uint8_t APB_PreScaler[4] = {2, 4, 8, 16};
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

uint32_t RCC_GetPLLOutputClock(void)
{
	return 0;
}

uint32_t RCC_GetPLCK1Value(void)
{
	uint32_t pclk1,SystemClk;

	uint8_t clksrc,temp,ahbp,apb1p;

	clksrc = ((RCC->CFGR >> 2) & 0x3);

	if(clksrc == 0)
	{
		SystemClk = 16000000;
	}
	else if(clksrc == 1)
	{
		SystemClk = 8000000;
	}
	else if(clksrc == 2)
	{
		SystemClk = RCC_GetPLLOutputClock();
	}

	//ahbp
	temp = ((RCC->CFGR >> 4) & 0xF);

	if(temp < 8)
	{
		ahbp = 1;
	}
	else
	{
		ahbp = AHB_PreScaler[temp-8];
	}

	//apb1
	temp = ((RCC->CFGR >> 10) & 0x7);

	if(temp < 4)
	{
		apb1p = 1;
	}
	else
	{
		apb1p = APB_PreScaler[temp-4];
	}

	pclk1 = (SystemClk / ahbp) / apb1p;

	return pclk1;
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

	tempreg |= pI2CHandle->I2C_Config.I2C_ACKControl << 10;
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
	}else
	{
		pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
	}

}












