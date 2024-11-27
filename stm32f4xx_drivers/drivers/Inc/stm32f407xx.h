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
#define	SRAM1_BASEADDR				0x20000000U // 112 Kb -> 114,688 Byte ->1C00
#define	SRAM2_BASEADDR				0x20001C00U
#define ROM_BASEADDR				0x1FFF0000U
#define SRAM						SRAM1_BASEADDR


#endif /* INC_STM32F407XX_H_ */
