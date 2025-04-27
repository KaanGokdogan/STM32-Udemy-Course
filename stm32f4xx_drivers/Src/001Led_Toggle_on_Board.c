/*
 * 001Led_Toggle_on_Board.c
 *
 *  Created on: Nov 28, 2024
 *      Author: MONSTER
 */

#include <stm32f407xx_i2c_driver.h>

void delay(void)
{
	for(uint32_t i = 0; i < 500000; i++);
}

int main()
{

	GPIO_Handle_t gpioLed;

	gpioLed.pGPIOx = GPIOD;
	gpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	gpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	gpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP; // OD olursa led yanmıyor ama Pull up yaparsan OD deyken çok az bir voltaj geçtiği için led az yanıyor.
	gpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_Init(&gpioLed);


	for(;;)
	{
		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_15);
		delay();
	}
	return 0;
}
