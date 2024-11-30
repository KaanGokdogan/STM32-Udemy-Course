/*
 * main.c
 *
 *  Created on: Nov 30, 2024
 *      Author: MONSTER
 */

#include "stm32f407xx.h"

int main(void)
{

}

void EXTI0_IRQHandler(void)
{
	// Handle the interrupt
	GPIO_IRQHandling(0);
}
