################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Drivers/Devices/adc_dma.c \
../Libraries/Drivers/Devices/irqs.c \
../Libraries/Drivers/Devices/ticks.c 

OBJS += \
./Libraries/Drivers/Devices/adc_dma.o \
./Libraries/Drivers/Devices/irqs.o \
./Libraries/Drivers/Devices/ticks.o 

C_DEPS += \
./Libraries/Drivers/Devices/adc_dma.d \
./Libraries/Drivers/Devices/irqs.d \
./Libraries/Drivers/Devices/ticks.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Drivers/Devices/%.o Libraries/Drivers/Devices/%.su: ../Libraries/Drivers/Devices/%.c Libraries/Drivers/Devices/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Libraries -I../Libraries/Drivers/Devices -I../Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC -I../Libraries/Drivers/Usb/STM32_USB_Device_Library/Core -I../Libraries/Drivers/Usb/Usb_Device/Cdc -I../Libraries/Drivers/Usb/Usb_Device/Target -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-Drivers-2f-Devices

clean-Libraries-2f-Drivers-2f-Devices:
	-$(RM) ./Libraries/Drivers/Devices/adc_dma.d ./Libraries/Drivers/Devices/adc_dma.o ./Libraries/Drivers/Devices/adc_dma.su ./Libraries/Drivers/Devices/irqs.d ./Libraries/Drivers/Devices/irqs.o ./Libraries/Drivers/Devices/irqs.su ./Libraries/Drivers/Devices/ticks.d ./Libraries/Drivers/Devices/ticks.o ./Libraries/Drivers/Devices/ticks.su

.PHONY: clean-Libraries-2f-Drivers-2f-Devices

