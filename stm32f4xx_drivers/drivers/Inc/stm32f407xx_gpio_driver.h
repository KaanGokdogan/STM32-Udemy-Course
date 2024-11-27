/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: Nov 27, 2024
 *      Author: MONSTER
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"
/*
 * This is a Configuration structure for a GPIO pin
 */
typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFuncMode;
}GPIO_PinConfig_t;
/*
 * This is a Handle structure for a GPIO pin
 */
typedef struct
{
	// pointer to hold the base address of the GPIO peripheral
	GPIO_RegDef_t *pGPIOx;					// This hold the base address of the GPIO port to which the pin belong
	GPIO_PinConfig_t GPIO_PinConfig; 		// This hold PIO pin configuration settings
}GPIO_Handle_t;

#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */
