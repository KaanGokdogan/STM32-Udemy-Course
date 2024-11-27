/*
 * stm32f407xx.h
 *
 *  Created on: Nov 27, 2024
 *      Author: MONSTER
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>

#define __vo volatile

/*
 * Base addresses of Flash and SRAM memories
 */
#define FLASH_BASEADDR				0x08000000U
#define	SRAM1_BASEADDR				0x20000000U // 112 KB -> 114,688 Byte -> 1C00
#define	SRAM2_BASEADDR				0x20001C00U
#define ROM_BASEADDR				0x1FFF0000U
#define SRAM						SRAM1_BASEADDR

/*
 * AHBx and APXx Bus Peripheral base addresses
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
#define RCC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x3800)

/*
 * Base addresses of peripherals which are hanging on APB1 bus
 */
#define I2C1_BASEADDR				(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR				(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR				(APB1PERIPH_BASEADDR + 0x5C00)

#define SPI2_BASEADDR				(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR				(APB1PERIPH_BASEADDR + 0x3C00)

#define USART2_BASEADDR				(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR				(APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR				(APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR				(APB1PERIPH_BASEADDR + 0x5000)

/*
 * Base addresses of peripherals which are hanging on APB2 bus
 */
#define EXTI_BASEADDR				(APB2PERIPH_BASEADDR + 0x3C00)
#define SPI1_BASEADDR				(APB2PERIPH_BASEADDR + 0x3000)
#define SYSCFG_BASEADDR				(APB2PERIPH_BASEADDR + 0x3800)
#define USART1_BASEADDR				(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR				(APB2PERIPH_BASEADDR + 0x1400)


/**************** Peripheral Register Definition Structures ****************/
typedef struct{
	__vo uint32_t MODER;				//GPIO port mode register						Address offset: 0x00
	__vo uint32_t OTYPER;				//GPIO port output type register
	__vo uint32_t OSPEEDR;				//GPIO port output speed register
	__vo uint32_t PUPDR;				//GPIO port pull-up/pull-down register
	__vo uint32_t IDR;					//GPIO port input data register
	__vo uint32_t ODR;					//GPIO port output data register
	__vo uint32_t BSRR;					//GPIO port bit set/reset register
	__vo uint32_t LCKR;					//GPIO port configuration lock register
	__vo uint32_t AFR[2];				//AFR[0]: GPIO alternate function low register, AFR[1]:GPIO alternate function high register
}GPIO_RegDef_t;

typedef struct{
	__vo uint32_t CR;						// Address offset:0x00		clock control register
	__vo uint32_t PLLCFGR;					// Address offset:0x04		PLL configuration register
	__vo uint32_t CFGR;						// Address offset:0x08		clock configuration register
	__vo uint32_t CIR;						// Address offset:0x0C		clock interrupt register
	__vo uint32_t AHB1RSTR;					// Address offset:0x10		AHB1 peripheral reset register
	__vo uint32_t AHB2RSTR;					// Address offset:0x14		AHB2 peripheral reset register
	__vo uint32_t AHB3RSTR;					// Address offset:0x18		AHB3 peripheral reset register
	 uint32_t RESERVED1;				// Address offset:0x1C
	__vo uint32_t APB1RSTR;					// Address offset:0x20		APB1 peripheral reset register
	__vo uint32_t APB2RSTR;					// Address offset:0x24		APB2 peripheral reset register
	 uint32_t RESERVED2[2];				// Address offset:0x28, 2C
	__vo uint32_t AHB1ENR;					// Address offset:0x30		AHB1 peripheral clock enable register
	__vo uint32_t AHB2ENR;					// Address offset:0x34		AHB2 peripheral clock enable register
	__vo uint32_t AHB3ENR;					// Address offset:0x38		AHB3 peripheral clock enable register
	 uint32_t RESERVED3;					// Address offset:0x3c
	__vo uint32_t APB1ENR;					// Address offset:0x40		APB1 peripheral clock enable register
	__vo uint32_t APB2ENR;					// Address offset:0440		APB2 peripheral clock enable register
	 uint32_t RESERVED4[2];				// Address offset:0x48, 4C
	__vo uint32_t AHB1LPENR;				// Address offset:0x50		AHB1 peripheral clock enable in low power mode register
	__vo uint32_t AHB2LPENR;				// Address offset:0x54		AHB2 peripheral clock enable in low power mode register
	__vo uint32_t AHB3LPENR;				// Address offset:0x58		AHB3 peripheral clock enable in low power mode register
	uint32_t RESERVED5;					// Address offset:0x5C
	__vo uint32_t APB1LPENR;				// Address offset:0x60		APB1 peripheral clock enable in low power mode register
	__vo uint32_t APB2LPENR;				// Address offset:0x64		APB2 peripheral clock enabled in low power mode register
	 uint32_t RESERVED6[2];				// Address offset:0x68, 6C
	__vo uint32_t BDCR;						// Address offset:0x70		Backup domain control register
	__vo uint32_t CSR;						// Address offset:0x74		clock control & status register
	 uint32_t RESERVED7[2];				// Address offset:0x78, 7C
	__vo uint32_t SSCGR;					// Address offset:0x80		Spread spectrum clock generation register
	__vo uint32_t PLLI2SCFGR;				// Address offset:0x84		PLLI2S configuration register

}RCC_RegDef_t;






/*
 * Peripheral definitions ( Peripheral base addresses type casted to xxx_RegDef_t
 */
#define GPIOA				((GPIO_RegDef_t*) GPIOA_BASEADDR)
#define GPIOB				((GPIO_RegDef_t*) GPIOB_BASEADDR)
#define GPIOC				((GPIO_RegDef_t*) GPIOC_BASEADDR)
#define GPIOD				((GPIO_RegDef_t*) GPIOD_BASEADDR)
#define GPIOE				((GPIO_RegDef_t*) GPIOE_BASEADDR)
#define GPIOF				((GPIO_RegDef_t*) GPIOF_BASEADDR)
#define GPIOG				((GPIO_RegDef_t*) GPIOG_BASEADDR)
#define GPIOH				((GPIO_RegDef_t*) GPIOH_BASEADDR)
#define GPIOI				((GPIO_RegDef_t*) GPIOI_BASEADDR)

#define RCC					((RCC_RegDef_t*) RCC_BASEADDR)


/*
 * Clock Enable Macros for GPIOx peripherals
 */
#define GPIOA_PCLK_EN() 	(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN() 	(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN() 	(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN() 	(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN() 	(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN() 	(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN() 	(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN() 	(RCC->AHB1ENR |= (1 << 7))

/*
 * Clock Enable Macros for I2Cx peripherals
 */
#define I2C1_PCLK_EN() 	(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN() 	(RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN() 	(RCC->APB1ENR |= (1 << 23))

/*
 * Clock Enable Macros for SPIx peripherals
 */
#define SPI1_PCLK_EN() 	(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN() 	(RCC->APB1ENR |= (1 << 13))
#define SPI3_PCLK_EN() 	(RCC->APB1ENR |= (1 << 14))
#define SPI4_PCLK_EN() 	(RCC->APB2ENR |= (1 << 15))

/*
 * Clock Enable Macros for USARTx peripherals
 */
#define USART1_PCLK_EN() 	(RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN() 	(RCC->APB2ENR |= (1 << 17))
#define USART3_PCLK_EN() 	(RCC->APB2ENR |= (1 << 18))
#define USART6_PCLK_EN() 	(RCC->APB2ENR |= (1 << 5))

/*
 * Clock Enable Macros for UARTx peripherals
 */
#define UART4_PCLK_EN() 	(RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN() 	(RCC->APB1ENR |= (1 << 20))

/*
 * Clock Enable Macros for SYSCFGx peripherals
 */
#define SYSCFG1_PCLK_EN() 	(RCC->APB2ENR |= (1 << 12))



/*
 * Clock Disable Macros for GPIOx peripherals
 */
#define GPIOA_PCLK_DI() 	(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI() 	(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI() 	(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI() 	(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI() 	(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI() 	(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI() 	(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOI_PCLK_DI() 	(RCC->AHB1ENR &= ~(1 << 7))

/*
 * Clock Disable Macros for I2Cx peripherals
 */
#define I2C1_PCLK_DI() 	(RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI() 	(RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI() 	(RCC->APB1ENR &= ~(1 << 23))

/*
 * Clock Disable Macros for SPIx peripherals
 */
#define SPI1_PCLK_DI() 	(RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI() 	(RCC->APB1ENR &= ~(1 << 13))
#define SPI3_PCLK_DI() 	(RCC->APB1ENR &= ~(1 << 14))
#define SPI4_PCLK_DI() 	(RCC->APB2ENR &= ~(1 << 15))

/*
 * Clock Disable Macros for USARTx peripherals
 */
#define USART1_PCLK_DI() 	(RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI() 	(RCC->APB2ENR &= ~(1 << 17))
#define USART3_PCLK_DI() 	(RCC->APB2ENR &= ~(1 << 18))
#define USART6_PCLK_DI() 	(RCC->APB2ENR &= ~(1 << 5))

/*
 * Clock Disable Macros for UARTx peripherals
 */
#define UART4_PCLK_DI() 	(RCC->APB1ENR &= ~(1 << 19))
#define UART5_PCLK_DI() 	(RCC->APB1ENR &= ~(1 << 20))

/*
 * Clock Disable Macros for SYSCFGx peripherals
 */
#define SYSCFG1_PCLK_DI() 	(RCC->APB2ENR &= ~(1 << 12))










#endif /* INC_STM32F407XX_H_ */
