################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Drivers/Usb/Usb_Device/Cdc/usb_device.c \
../Libraries/Drivers/Usb/Usb_Device/Cdc/usbd_cdc_if.c \
../Libraries/Drivers/Usb/Usb_Device/Cdc/usbd_desc.c 

OBJS += \
./Libraries/Drivers/Usb/Usb_Device/Cdc/usb_device.o \
./Libraries/Drivers/Usb/Usb_Device/Cdc/usbd_cdc_if.o \
./Libraries/Drivers/Usb/Usb_Device/Cdc/usbd_desc.o 

C_DEPS += \
./Libraries/Drivers/Usb/Usb_Device/Cdc/usb_device.d \
./Libraries/Drivers/Usb/Usb_Device/Cdc/usbd_cdc_if.d \
./Libraries/Drivers/Usb/Usb_Device/Cdc/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Drivers/Usb/Usb_Device/Cdc/%.o Libraries/Drivers/Usb/Usb_Device/Cdc/%.su: ../Libraries/Drivers/Usb/Usb_Device/Cdc/%.c Libraries/Drivers/Usb/Usb_Device/Cdc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Libraries -I../Libraries/Drivers/Devices -I../Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC -I../Libraries/Drivers/Usb/STM32_USB_Device_Library/Core -I../Libraries/Drivers/Usb/Usb_Device/Cdc -I../Libraries/Drivers/Usb/Usb_Device/Target -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-Drivers-2f-Usb-2f-Usb_Device-2f-Cdc

clean-Libraries-2f-Drivers-2f-Usb-2f-Usb_Device-2f-Cdc:
	-$(RM) ./Libraries/Drivers/Usb/Usb_Device/Cdc/usb_device.d ./Libraries/Drivers/Usb/Usb_Device/Cdc/usb_device.o ./Libraries/Drivers/Usb/Usb_Device/Cdc/usb_device.su ./Libraries/Drivers/Usb/Usb_Device/Cdc/usbd_cdc_if.d ./Libraries/Drivers/Usb/Usb_Device/Cdc/usbd_cdc_if.o ./Libraries/Drivers/Usb/Usb_Device/Cdc/usbd_cdc_if.su ./Libraries/Drivers/Usb/Usb_Device/Cdc/usbd_desc.d ./Libraries/Drivers/Usb/Usb_Device/Cdc/usbd_desc.o ./Libraries/Drivers/Usb/Usb_Device/Cdc/usbd_desc.su

.PHONY: clean-Libraries-2f-Drivers-2f-Usb-2f-Usb_Device-2f-Cdc

