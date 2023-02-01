################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/App_Main.c \
../Libraries/Power_StateMachine.c \
../Libraries/USB_Bridge.c 

OBJS += \
./Libraries/App_Main.o \
./Libraries/Power_StateMachine.o \
./Libraries/USB_Bridge.o 

C_DEPS += \
./Libraries/App_Main.d \
./Libraries/Power_StateMachine.d \
./Libraries/USB_Bridge.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/%.o Libraries/%.su: ../Libraries/%.c Libraries/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Libraries -I../Libraries/Drivers/Devices -I../Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC -I../Libraries/Drivers/Usb/STM32_USB_Device_Library/Core -I../Libraries/Drivers/Usb/Usb_Device/Cdc -I../Libraries/Drivers/Usb/Usb_Device/Target -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries

clean-Libraries:
	-$(RM) ./Libraries/App_Main.d ./Libraries/App_Main.o ./Libraries/App_Main.su ./Libraries/Power_StateMachine.d ./Libraries/Power_StateMachine.o ./Libraries/Power_StateMachine.su ./Libraries/USB_Bridge.d ./Libraries/USB_Bridge.o ./Libraries/USB_Bridge.su

.PHONY: clean-Libraries

