/*
 * 008I2C_Master_TX_Testıng.c
 *
 *  Created on: 29 Mar 2026
 *      Author: MONSTER
 */

#include <string.h>
#include <stdio.h>
#include "stm32f407xx.h"

#define SLAVE_ADDR		0x68

I2C_Handle_t I2C1Handle;

// Receive Buffer
uint8_t tx_Buffer[32] = "STM32 slave mode testing";


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
	GPIO_ButtonInit();

	// I2C pin inits
	I2C1_GPIOInits();

	// I2C peripheral configuration
	I2C1_Inits();

	// I2C IRQ configuration
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_EV, ENABLE);
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_ER, ENABLE);

	I2C_SlaveEnableDisableCallbackEvents(I2C1, ENABLE);

	// Enable the I2C peripheral
	I2C_PeripheralControl(I2C1, ENABLE);

	// ACK bit is made 1 after PE = 1
	I2C_ManageACKing(I2C1,I2C_ACK_ENABLE);


	while(1);

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
	static uint8_t commandCode = 0, count = 0;

	if(AppEvent == I2C_EV_DATA_REQ)
	{
		// Master wants some data. Slave has to send it.
		if(commandCode == 0x51)
		{
			// Send the length information to the master
			I2C_SlaveSendData(pI2CHandle->pI2Cx, strlen((char*)tx_Buffer));
		}
		else if(commandCode == 0x52)
		{
			// Send the contents of tx_Buffer
			I2C_SlaveSendData(pI2CHandle->pI2Cx, tx_Buffer[count++]);
		}
	}
	else if(AppEvent == I2C_EV_DATA_RCV)
	{
		// Data is waiting for the slave to read. Slave has to read it.
		commandCode = I2C_SlaveReceiveData(pI2CHandle->pI2Cx);
	}
	else if(AppEvent == I2C_ERROR_AF)
	{
		// This happens only during slave TXing.
		// Master has sent the NACK. So slave should understand that master doesnt need
		// more data.
		commandCode = 0xFF;
		count = 0;
	}
	else if(AppEvent == I2C_EV_STOP)
	{
		// This happens only during slave reception
		// Master has ended the I2C communication with the slave
	}
}

