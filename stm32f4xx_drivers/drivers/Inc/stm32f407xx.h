/*
 * stm32f407xx.h
 *
 *  Created on: Nov 27, 2024
 *      Author: MONSTER
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

/*
 * Base addresses of Flash and SRAM memories
 */
#define FLASH_BASEADDR				0x08000000U
#define	SRAM1_BASEADDR				0x20000000U // 112 Kb -> 114,688 Byte -> 1C00
#define	SRAM2_BASEADDR				0x20001C00U
#define ROM_BASEADDR				0x1FFF0000U
#define SRAM						SRAM1_BASEADDR

/*
 * AHBx and APXx Bus Peripheral base adresses
 */
#define PERIPH_BASE					0x40000000U
#define APB1PERIPH_BASE				PERIPH_BASE
#define APB2PERIPH_BASE				0x40010000U
#define AHB1PERIPH_BASE				0x40020000U
#define AHB2PERIPH_BASE				0x50000000U

/*
 * Base addresses of peripherals which are hanging on AHB1 Bus
 */
#define GPIOA_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOE_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR				(AHB1PERIPH_BASEADDR + 0x2000)

/*
 * Base addresses of peripherals which are hanging on APB1 bus
 */
#define I2C1_BASEADDR				(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR				(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR				(APB1PERIPH_BASEADDR + 0x5C00)

#define SPI2_BASEADDR				(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR				(APB1PERIPH_BASEADDR + 0x3C00)
/*
 * Base addresses of peripherals which are hanging on APB2 bus
 */
#define EXTI_BASEADDR				(APB2PERIPH_BASEADDR + 0x3C00)
#endif /* INC_STM32F407XX_H_ */
