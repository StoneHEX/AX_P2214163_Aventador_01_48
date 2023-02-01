################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC/usbd_cdc.c 

OBJS += \
./Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC/usbd_cdc.o 

C_DEPS += \
./Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC/usbd_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC/%.o Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC/%.su: ../Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC/%.c Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Libraries -I../Libraries/Drivers/Devices -I../Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC -I../Libraries/Drivers/Usb/STM32_USB_Device_Library/Core -I../Libraries/Drivers/Usb/Usb_Device/Cdc -I../Libraries/Drivers/Usb/Usb_Device/Target -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-Drivers-2f-Usb-2f-STM32_USB_Device_Library-2f-Class-2f-CDC

clean-Libraries-2f-Drivers-2f-Usb-2f-STM32_USB_Device_Library-2f-Class-2f-CDC:
	-$(RM) ./Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC/usbd_cdc.d ./Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC/usbd_cdc.o ./Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC/usbd_cdc.su

.PHONY: clean-Libraries-2f-Drivers-2f-Usb-2f-STM32_USB_Device_Library-2f-Class-2f-CDC

