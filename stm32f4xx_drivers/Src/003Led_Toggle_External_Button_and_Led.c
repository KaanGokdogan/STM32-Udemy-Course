/*
 * 003Led_Toggle_External_Button_and_Led.c
 *
 *  Created on: Nov 28, 2024
 *      Author: MONSTER
 */

#include "stm32f407xx.h"

#define LOW 0
#define BTN_PRESSED LOW

void delay(void)
{
	for(uint32_t i = 0; i < 50000000; i++);
}

int main()
{

	GPIO_Handle_t gpioLed,gpioButton;

	// This is led configuration
	gpioLed.pGPIOx = GPIOA;
	gpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
	gpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	gpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP; // OD olursa led yanmıyor ama Pull up yaparsan OD deyken çok az bir voltaj geçtiği için led az yanıyor.
	gpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_Init(&gpioLed);

	// This is button configuration
	gpioLed.pGPIOx = GPIOB;
	gpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	gpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	gpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PU;

	GPIO_PeriClockControl(GPIOB, ENABLE);
	GPIO_Init(&gpioButton);



	for(;;)
	{
		if(GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_12) == BTN_PRESSED)
		{
			delay();
			GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_8);
		}

	}
	return 0;
}

