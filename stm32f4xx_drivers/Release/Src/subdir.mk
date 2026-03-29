################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/001Led_Toggle_on_Board.c \
../Src/002Led_Toggle_with_Button.c \
../Src/003Led_Toggle_External_Button_and_Led.c \
../Src/004.Button_Interrupt.c \
../Src/005SPI_Tx_Testing.c \
../Src/006SPI_TxOnly_Arduino.c \
../Src/007I2C_Master_TX_Testıng.c \
../Src/014UART_TxOny.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/001Led_Toggle_on_Board.o \
./Src/002Led_Toggle_with_Button.o \
./Src/003Led_Toggle_External_Button_and_Led.o \
./Src/004.Button_Interrupt.o \
./Src/005SPI_Tx_Testing.o \
./Src/006SPI_TxOnly_Arduino.o \
./Src/007I2C_Master_TX_Testıng.o \
./Src/014UART_TxOny.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/001Led_Toggle_on_Board.d \
./Src/002Led_Toggle_with_Button.d \
./Src/003Led_Toggle_External_Button_and_Led.d \
./Src/004.Button_Interrupt.d \
./Src/005SPI_Tx_Testing.d \
./Src/006SPI_TxOnly_Arduino.d \
./Src/007I2C_Master_TX_Testıng.d \
./Src/014UART_TxOny.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/001Led_Toggle_on_Board.cyclo ./Src/001Led_Toggle_on_Board.d ./Src/001Led_Toggle_on_Board.o ./Src/001Led_Toggle_on_Board.su ./Src/002Led_Toggle_with_Button.cyclo ./Src/002Led_Toggle_with_Button.d ./Src/002Led_Toggle_with_Button.o ./Src/002Led_Toggle_with_Button.su ./Src/003Led_Toggle_External_Button_and_Led.cyclo ./Src/003Led_Toggle_External_Button_and_Led.d ./Src/003Led_Toggle_External_Button_and_Led.o ./Src/003Led_Toggle_External_Button_and_Led.su ./Src/004.Button_Interrupt.cyclo ./Src/004.Button_Interrupt.d ./Src/004.Button_Interrupt.o ./Src/004.Button_Interrupt.su ./Src/005SPI_Tx_Testing.cyclo ./Src/005SPI_Tx_Testing.d ./Src/005SPI_Tx_Testing.o ./Src/005SPI_Tx_Testing.su ./Src/006SPI_TxOnly_Arduino.cyclo ./Src/006SPI_TxOnly_Arduino.d ./Src/006SPI_TxOnly_Arduino.o ./Src/006SPI_TxOnly_Arduino.su ./Src/007I2C_Master_TX_Testıng.cyclo ./Src/007I2C_Master_TX_Testıng.d ./Src/007I2C_Master_TX_Testıng.o ./Src/007I2C_Master_TX_Testıng.su ./Src/014UART_TxOny.cyclo ./Src/014UART_TxOny.d ./Src/014UART_TxOny.o ./Src/014UART_TxOny.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

