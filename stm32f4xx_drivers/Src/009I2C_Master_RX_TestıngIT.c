/*
 * 008I2C_Master_TX_Testıng.c
 *
 *  Created on: 29 Mar 2026
 *      Author: MONSTER
 */

#include <string.h>
#include <stdio.h>
#include "stm32f407xx.h"

extern void initialise_monitor_handles();

#define SLAVE_ADDR		0x68

I2C_Handle_t I2C1Handle;

// Receive Buffer
uint8_t receive_Buffer[32];

// Flag variable
uint8_t rxCmplt = RESET;

/*
 * PB6 -> SCL
 * PB7 -> SDA
 */

void delay(void)
{
	for(uint32_t i = 0; i < 50000000; i++);
}


void I2C1_GPIOInits(void)
{
	GPIO_Handle_t I2CPins;

	I2CPins.pGPIOx = GPIOB;
	I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	I2CPins.GPIO_PinConfig.GPIO_PinAltFuncMode = 4;
	I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// SCL
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&I2CPins);

	// SDA
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&I2CPins);

}
void I2C1_Inits(void)
{
	I2C1Handle.pI2Cx = I2C1;
	I2C1Handle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
	I2C1Handle.I2C_Config.I2C_DeviceAddress = SLAVE_ADDR;
	I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

	I2C_Init(&I2C1Handle);
}

void GPIO_ButtonInit(void)
{
	GPIO_Handle_t gpioButton;

	// This is button configuration
	gpioButton.pGPIOx = GPIOA;
	gpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	gpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	gpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&gpioButton);
}

int main(void)
{
	uint8_t len, commandCode;

	initialise_monitor_handles();
	printf("Appliocation is running\n");


	GPIO_ButtonInit();

	// I2C pin inits
	I2C1_GPIOInits();

	// I2C peripheral configuration
	I2C1_Inits();

	// I2C IRQ configuration
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_EV, ENABLE);
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_ER, ENABLE);

	// Enable the I2C peripheral
	I2C_PeripheralControl(I2C1, ENABLE);

	// ACK bit is made 1 after PE = 1
	I2C_ManageACKing(I2C1,I2C_ACK_ENABLE);


	while(1)
	{
		// wait till button is pressed
		while( !GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );

		// to avoid button de-bouncing related issues 200ms of delay
		delay();

		commandCode = 0x51;

		while( I2C_MasterSendDataIT(&I2C1Handle, &commandCode, 1, SLAVE_ADDR, I2C_ENABLE_SR) != I2C_READY );
		while( I2C_MasterReceiveDataIT(&I2C1Handle, &len, 1, SLAVE_ADDR, I2C_ENABLE_SR) != I2C_READY );

		commandCode = 0x52;

		while(I2C_MasterSendDataIT(&I2C1Handle, &commandCode, 1, SLAVE_ADDR, I2C_ENABLE_SR) != I2C_READY );
		while(I2C_MasterReceiveDataIT(&I2C1Handle, receive_Buffer, len, SLAVE_ADDR, I2C_DISABLE_SR) != I2C_READY );

		rxCmplt = RESET;

		// wait till rx completes
		while(rxCmplt != SET);

		receive_Buffer[len] = '\0';
		printf("Data : %s", receive_Buffer);

		rxCmplt = RESET;
	}

	return 0;
}



void I2C1_EV_IRQHandler(void)
{
	I2C_EV_IRQHandling(&I2C1Handle);
}

void I2C1_ER_IRQHandler(void)
{
	I2C_ER_IRQHandling(&I2C1Handle);
}


void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEvent)
{
	if(AppEvent == I2C_EV_TX_CMPLT)
	{
		printf("TX is completed");
	}
	else if (AppEvent == I2C_EV_RX_CMPLT)
	{
		printf("RX is completed");
		rxCmplt = SET;
	}
	else if (AppEvent == I2C_ERROR_AF)
	{
		printf("Error: ACK failure");
		// in master ACK failure happens when slave fails to send ACK for the byte
		// sent from the master.
		I2C_CloseSendData(pI2CHandle);

		// generate the stop condition to release the bus
		I2C_GenerateStopCondition(I2C1);

		// hang in infinite loop
		while(1);
	}

}

