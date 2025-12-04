/*
 * 014UART_TxOny.c
 *
 *  Created on: Jun 29, 2025
 *      Author: MONSTER
 */
#include "stm32f407xx.h"
#include "stdio.h"
#include "string.h"

char msg[1024] = "UART Tx testing...\n\r";

USART_Handle_t Usart2_handle;
void USART2_INIT()
{
	Usart2_handle.pUSARTx = USART2;
	Usart2_handle.USART_Config.USART_Baud = USART_STD_BAUD_115200;
	Usart2_handle.USART_Config.USART_HWFLowControl = USART_HW_FLOW_CTRL_NONE;
	Usart2_handle.USART_Config.USART_Mode = USART_MODE_ONLY_TX;
	Usart2_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	Usart2_handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	Usart2_handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	USART_Init(&Usart2_handle);
}
void USART_GPIO_INIT()
{
	GPIO_Handle_t usart_gpios;

		usart_gpios.pGPIOx = GPIOA;
		usart_gpios.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
		usart_gpios.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
		usart_gpios.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
		usart_gpios.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
		usart_gpios.GPIO_PinConfig.GPIO_PinAltFuncMode =7;

		//USART2 TX
		usart_gpios.GPIO_PinConfig.GPIO_PinNumber  = GPIO_PIN_NO_2;
		GPIO_Init(&usart_gpios);

		//USART2 RX
		usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
		GPIO_Init(&usart_gpios);
}

int main(void)
{
	USART2_INIT();
	USART_GPIO_INIT();

	USART_PeripheralControl(USART2, ENABLE);
	USART_SendData(&Usart2_handle, (uint8_t*)msg, strlen(msg));


	while(0);
	return 0;
}
