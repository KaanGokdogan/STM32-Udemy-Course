/*
 * stm32f407xx.h
 *
 *  Created on: Nov 27, 2024
 *      Author: MONSTER
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stddef.h>
#include <stdint.h>

#define __vo volatile
#define __weak __attribute__((weak))

/************************************START: Processor Specific Details***********************************/
/*
 * ARM Cortex Mx Processor NVIC ISERx register addresses
 */
#define NVIC_ISER0			( (__vo uint32_t*) 0xE000E100)
#define NVIC_ISER1			( (__vo uint32_t*) 0xE000E104)
#define NVIC_ISER2			( (__vo uint32_t*) 0xE000E108)
#define NVIC_ISER3			( (__vo uint32_t*) 0xE000E10C)

/*
 * ARM Cortex Mx Processor NVIC ICERx register addresses
 */
#define NVIC_ICER0			( (__vo uint32_t*) 0xE000E180)
#define NVIC_ICER1			( (__vo uint32_t*) 0xE000E184)
#define NVIC_ICER2			( (__vo uint32_t*) 0xE000E188)
#define NVIC_ICER3			( (__vo uint32_t*) 0xE000E18C)

/*
 * ARM Cortex Mx Processor priority  register address calculation
 */
#define NVIC_PR_BASE_ADDR	( (__vo uint32_t*) 0xE000E400)

/*
 * ARM Cortex Mx Processor number of priority  bit implemented in Priority register
 */
#define NO_PR_BITS_IMPLEMENTED	4

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
#define PERIPH_BASEADDR				0x40000000U
#define APB1PERIPH_BASEADDR			PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR			0x40010000U
#define AHB1PERIPH_BASEADDR			0x40020000U
#define AHB2PERIPH_BASEADDR			0x50000000U

/*
 * Base addresses of peripherals which are hanging on AHB1 Bus
 */
#define GPIOA_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0C00)
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
#define SPI4_BASEADDR				(APB2PERIPH_BASEADDR + 0x3400)
#define SYSCFG_BASEADDR				(APB2PERIPH_BASEADDR + 0x3800)
#define USART1_BASEADDR				(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR				(APB2PERIPH_BASEADDR + 0x1400)



/**************** Peripheral Register Definition Structures ****************/

/*
 * Peripheral register definition structure for GPIO
 */
typedef struct
{
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


/*
 * Peripheral register definition structure for RCC
 */
typedef struct
{
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
 * Peripheral register definition structure for EXTI
 */

typedef struct
{
	__vo uint32_t IMR;					// Address offset: 0x00		Interrupt mask register
	__vo uint32_t EMR;					// Address offset: 0x04		Event mask register
	__vo uint32_t RTSR;					// Address offset: 0x08		Rising trigger selection register
	__vo uint32_t FTSR;					// Address offset: 0x0C		Falling trigger selection register
	__vo uint32_t SWIER;				// Address offset: 0x10		Software interrupt event register
	__vo uint32_t PR;					// Address offset: 0x14		Pending register
}EXTI_RegDef_t;

/*
 * Peripheral register definition structure for SYSCFG
 */
typedef struct
{
	__vo uint32_t MEMRMP;				// Address offset: 0x00					SYSCFG memory remap register
	__vo uint32_t PMC;					// Address offset: 0x04					SYSCFG peripheral mode configuration register
	__vo uint32_t EXTICR[4];			// Address offset: 0x08, 0C, 10, 14		SYSCFG external interrupt configuration register 1
	uint32_t RESERVED[2];				// Address offset: 0x18, 1C
	__vo uint32_t CMPCR;				// Address offset: 0x20					Compensation cell control register
}SYSCFG_RegDef_t;

/*
 * Peripheral register definition structure for SPI
 */
typedef struct
{
	__vo uint32_t CR1;					// Address offset: 0x00			SPI control register 1
	__vo uint32_t CR2;					// Address offset: 0x04			SPI control register 2
	__vo uint32_t SR;					// Address offset: 0x08			SPI status register
	__vo uint32_t DR;					// Address offset: 0x0C			SPI data register
	__vo uint32_t CRCPR;				// Address offset: 0x10			SPI CRC polynomial register
	__vo uint32_t RXCRCR;				// Address offset: 0x14			SPI RX CRC register
	__vo uint32_t TXCRCR;				// Address offset: 0x18			SPI TX CRC register
	__vo uint32_t I2SCFGR;				// Address offset: 0x1C			SPI_I2S configuration register
	__vo uint32_t I2SPR;				// Address offset: 0x20			SPI_I2S prescaler register
}SPI_RegDef_t;

/*
 *  Peripheral register definition structure for I2C
 */
typedef struct
{
	__vo uint32_t CR1;					// Address offset: 0x00			I2C Control register 1
	__vo uint32_t CR2;					// Address offset: 0x04			I2C Control register 2
	__vo uint32_t OAR1;					// Address offset: 0x08			I2C Own address register 1
	__vo uint32_t OAR2;					// Address offset: 0x0C			I2C Own address register 2
	__vo uint32_t DR;					// Address offset: 0x10			I2C Data register
	__vo uint32_t SR1;					// Address offset: 0x14			I2C Status register 1
	__vo uint32_t SR2;					// Address offset: 0x18			I2C Status register 2
	__vo uint32_t CCR;					// Address offset: 0x1C			I2C Clock control register
	__vo uint32_t TRISE;				// Address offset: 0x20			I2C TRISE register
	__vo uint32_t FLTR;					// Address offset: 0x24			I2C FLTR register
}I2C_RegDef_t;



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

#define EXTI				((EXTI_RegDef_t*) EXTI_BASEADDR)

#define SYSCFG 				((SYSCFG_RegDef_t*) SYSCFG_BASEADDR)

#define SPI1				((SPI_RegDef_t*) SPI1_BASEADDR)
#define SPI2				((SPI_RegDef_t*) SPI2_BASEADDR)
#define SPI3				((SPI_RegDef_t*) SPI3_BASEADDR)
#define SPI4				((SPI_RegDef_t*) SPI4_BASEADDR)

#define I2C1				((I2C_RegDef_t*) I2C1_BASEADDR)
#define I2C2				((I2C_RegDef_t*) I2C2_BASEADDR)
#define I2C3				((I2C_RegDef_t*) I2C3_BASEADDR)

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
#define SPI2_PCLK_EN() 	(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN() 	(RCC->APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN() 	(RCC->APB2ENR |= (1 << 13))

/*
 * Clock Enable Macros for USARTx peripherals
 */
#define USART1_PCLK_EN() 	(RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN() 	(RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN() 	(RCC->APB1ENR |= (1 << 18))
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
#define GPIOH_PCLK_DI() 	(RCC->AHB1ENR &= ~(1 << 7))

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
#define SPI2_PCLK_DI() 	(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI() 	(RCC->APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DI() 	(RCC->APB2ENR &= ~(1 << 13))

/*
 * Clock Disable Macros for USARTx peripherals
 */
#define USART1_PCLK_DI() 	(RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI() 	(RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCLK_DI() 	(RCC->APB1ENR &= ~(1 << 18))
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

/*
 * Macros to reset GPIOx peripherals
 */
#define GPIOA_REG_RESET()			do{ ( RCC->AHB1RSTR |= ( 1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0));}while(0)
#define GPIOB_REG_RESET()			do{ ( RCC->AHB1RSTR |= ( 1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1));}while(0)
#define GPIOC_REG_RESET()			do{ ( RCC->AHB1RSTR |= ( 1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2));}while(0)
#define GPIOD_REG_RESET()			do{ ( RCC->AHB1RSTR |= ( 1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3));}while(0)
#define GPIOE_REG_RESET()			do{ ( RCC->AHB1RSTR |= ( 1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4));}while(0)
#define GPIOF_REG_RESET()			do{ ( RCC->AHB1RSTR |= ( 1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5));}while(0)
#define GPIOG_REG_RESET()			do{ ( RCC->AHB1RSTR |= ( 1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6));}while(0)
#define GPIOH_REG_RESET()			do{ ( RCC->AHB1RSTR |= ( 1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7));}while(0)

/*
 * Macros to reset SPIx peripherals
 */
#define SPI1_REG_RESET()			do{ ( RCC->APB2RSTR |= ( 1 << 12)); (RCC->APB1RSTR &= ~(1 << 12));}while(0)
#define SPI2_REG_RESET()			do{ ( RCC->APB1RSTR |= ( 1 << 14)); (RCC->APB1RSTR &= ~(1 << 14));}while(0)
#define SPI3_REG_RESET()			do{ ( RCC->APB1RSTR |= ( 1 << 15)); (RCC->APB1RSTR &= ~(1 << 15));}while(0)
#define SPI4_REG_RESET()			do{ ( RCC->APB2RSTR |= ( 1 << 13)); (RCC->APB1RSTR &= ~(1 << 13));}while(0)

/*
 * Macros to reset I2Cx peripherals
 */
#define I2C1_REG_RESET()			do{ ( RCC->APB1RSTR |= ( 1 << 21)); (RCC->APB1RSTR &= ~(1 << 21 ));}while(0)
#define I2C2_REG_RESET()			do{ ( RCC->APB1RSTR |= ( 1 << 22)); (RCC->APB1RSTR &= ~(1 << 22 ));}while(0)
#define I2C3_REG_RESET()			do{ ( RCC->APB1RSTR |= ( 1 << 23)); (RCC->APB1RSTR &= ~(1 << 23 ));}while(0)

/*
 *  Returns port code for given GPIOx base address
 */
#define GPIO_BASEADDR_TO_CODE(x)  (	(x == GPIOA) ? 0:\
									(x == GPIOB) ? 1:\
									(x == GPIOC) ? 2:\
									(x == GPIOD) ? 3:\
									(x == GPIOE) ? 4:\
									(x == GPIOF) ? 5:\
									(x == GPIOG) ? 6:\
									(x == GPIOH) ? 7:0 )

/*
 * IRQ (interrupt request) number
 */
#define IRQ_NO_EXTI0				6
#define IRQ_NO_EXTI1				7
#define IRQ_NO_EXTI2				8
#define IRQ_NO_EXTI3				9
#define IRQ_NO_EXTI4				10
#define IRQ_NO_EXTI9_5				23
#define IRQ_NO_EXTI15_10			40

/*
 * Macros for all the possible priority levels
 */
#define NVIC_IRQ_PRIO0				0
#define NVIC_IRQ_PRIO1				1
#define NVIC_IRQ_PRIO2				2
#define NVIC_IRQ_PRIO3				3
#define NVIC_IRQ_PRIO4				4
#define NVIC_IRQ_PRIO5				5
#define NVIC_IRQ_PRIO6				6
#define NVIC_IRQ_PRIO7				7
#define NVIC_IRQ_PRIO8				8
#define NVIC_IRQ_PRIO9				9
#define NVIC_IRQ_PRIO10				10
#define NVIC_IRQ_PRIO11				11
#define NVIC_IRQ_PRIO12				12
#define NVIC_IRQ_PRIO13				13
#define NVIC_IRQ_PRIO14				14
#define NVIC_IRQ_PRIO15				15
/*
 * Some generic macros
 */
#define ENABLE 				1
#define DISABLE 			0
#define SET					ENABLE
#define RESET				DISABLE
#define GPIO_PIN_SET		SET
#define GPIO_PIN_RESET		RESET
#define FLAG_RESET			RESET
#define FLAG_SET			SET


/*******************************************************************
 * Bit position definitions of SPI peripheral
 *******************************************************************/
/*
 * Bit position definitions SPI_CR1
 */
#define SPI_CR1_CPHA					0
#define SPI_CR1_CPOL					1
#define SPI_CR1_MSTR					2
#define SPI_CR1_BR						3
#define SPI_CR1_SPE						6
#define SPI_CR1_LSBFIRST				7
#define SPI_CR1_SSI						8
#define SPI_CR1_SSM						9
#define SPI_CR1_RXONLY					10
#define SPI_CR1_DFF						11
#define SPI_CR1_CRCNEXT					12
#define SPI_CR1_CRCEN					13
#define SPI_CR1_BIDIOE					14
#define SPI_CR1_BIDIMODE				15

/*
 * Bit position definitions SPI_CR2
 */
#define SPI_CR2_RXDMAEN					0
#define SPI_CR2_TXDMAEN					1
#define SPI_CR2_SSOE					2
#define SPI_CR2_FRF						4
#define SPI_CR2_ERRIE					5
#define SPI_CR2_RXNEIE					6
#define SPI_CR2_TXEIE					7

/*
 * Bit position definitions SPI_SR
 */
#define SPI_SR_RXNE						0
#define SPI_SR_TXE						1
#define SPI_SR_CHSIDE					2
#define SPI_SR_UDR						3
#define SPI_SR_CRCERR					4
#define SPI_SR_MODF						5
#define SPI_SR_OVR						6
#define SPI_SR_BSY						7
#define SPI_SR_FRE						8


/*******************************************************************
 * Bit position definitions of I2C peripheral
 *******************************************************************/
/*
 * Bit position definitions I2C_CR1
 */
#define I2C_CR1_PE						0
#define I2C_CR1_SMBUS					1
#define I2C_CR1_SMBTYPE					3
#define I2C_CR1_ENARP					4
#define I2C_CR1_ENPEC					5
#define I2C_CR1_ENGC					6
#define I2C_CR1_NOSTRETCH				7
#define I2C_CR1_START					8
#define I2C_CR1_STOP					9
#define I2C_CR1_ACK						10
#define I2C_CR1_POS						11
#define I2C_CR1_PEC						12
#define I2C_CR1_ALERT					13
#define I2C_CR1_SWRST					15

/*
 * Bit position definitions I2C_CR2
 */
#define I2C_CR2_FREQ					0
#define I2C_CR2_ITERREN					8
#define I2C_CR2_ITEVTEN					9
#define I2C_CR2_ITBUFEN					10
#define I2C_CR2_DMAEN					11
#define I2C_CR2_LAST					012

/*
 * Bit position definitions I2C_SR1
 */
#define I2C_SR1_SB						0
#define I2C_SR1_ADDR					1
#define I2C_SR1_BTF						2
#define I2C_SR1_ADD10					3
#define I2C_SR1_STOPF					4
#define I2C_SR1_RXNE					6
#define I2C_SR1_TXE						7
#define I2C_SR1_BERR					8
#define I2C_SR1_ARLO					9
#define I2C_SR1_AF						10
#define I2C_SR1_OVR						11
#define I2C_SR1_PECERR					12
#define I2C_SR1_TIMEOUT					14
#define I2C_SR1_SMBALERT				15

/*
 * Bit position definitions I2C_SR2
 */
#define I2C_SR2_MSL						0
#define I2C_SR2_BUSY					1
#define I2C_SR2_TRA						2
#define I2C_SR2_GENCALL					4
#define I2C_SR2_SMBDEFAULT				5
#define I2C_SR2_SMBHOST					6
#define I2C_SR2_DUALF					7
#define I2C_SR2_PEC						8

/*
 * Bit position definitions I2C_CRR
 */
#define I2C_CCR_CCR						0
#define I2C_CCR_DUTY					14
#define I2C_CCR_FS						15

#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_spi_driver.h"
#include "stm32f407xx_i2c_driver.h"

#endif /* INC_STM32F407XX_H_ */
