/*
 * main.c
 *
 *  Created on: Nov 30, 2024
 *      Author: MONSTER
 */

#include "stm32f407xx.h"
#include <string.h>


void delay(void)
{
	for(uint32_t i = 0; i < 2500000; i++);
}

int main(void)
{

	GPIO_Handle_t gpioLed,gpioButton;
	//memset(&gpioLed,0,sizeof(gpioLed));
	//memset(&gpioButton,0,sizeof(gpioButton));

		// This is led configuration
		gpioLed.pGPIOx = GPIOD;
		gpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
		gpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
		gpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
		gpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
		gpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

		GPIO_PeriClockControl(GPIOD, ENABLE);
		GPIO_Init(&gpioLed);

		// This is button configuration
		gpioLed.pGPIOx = GPIOD;
		gpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
		gpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
		gpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
		gpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PU;

		GPIO_PeriClockControl(GPIOD, ENABLE);
		GPIO_Init(&gpioButton);

		// IRQ configurations
		GPIO_IRQPriorityConfig(IRQ_NO_EXTI9_5, NVIC_IRQ_PRIO15);
		GPIO_IRQInterruptConfig(IRQ_NO_EXTI9_5, ENABLE);


		for(;;);
}



void EXTI9_5_IRQHandler(void)
{
	delay();
	GPIO_IRQHandling(GPIO_PIN_NO_5);
	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
}


