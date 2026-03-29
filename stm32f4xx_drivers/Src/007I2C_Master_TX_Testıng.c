/*
 * 007I2C_Master_TX_Testıng.c
 *
 *  Created on: 26 Mar 2026
 *      Author: MONSTER
 */

#include <string.h>
#include "stm32f407xx.h"

#define SLAVE_ADDR		0x68

I2C_Handle_t I2C1Handle;

// some data
uint8_t user_data[] = "We are testing I2C master Tx";

/*
 * PB6 -> SCL
 * PB9 -> SDA
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

	// Enable the I2C peripheral
	I2C_PeripheralControl(I2C1, ENABLE);



	while(1)
	{
		// wait till button is pressed
		while( !GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );

		// to avoid button de-bouncing related issues 200ms of delay
		delay();

		// send some data to slave
		I2C_MasterSendData(&I2C1Handle, user_data, strlen(user_data), SLAVE_ADDR);
	}

	return 0;
}
