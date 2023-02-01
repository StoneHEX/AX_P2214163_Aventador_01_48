################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Drivers/Usb/Usb_Device/Target/usbd_cdc_conf.c 

OBJS += \
./Libraries/Drivers/Usb/Usb_Device/Target/usbd_cdc_conf.o 

C_DEPS += \
./Libraries/Drivers/Usb/Usb_Device/Target/usbd_cdc_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Drivers/Usb/Usb_Device/Target/%.o Libraries/Drivers/Usb/Usb_Device/Target/%.su: ../Libraries/Drivers/Usb/Usb_Device/Target/%.c Libraries/Drivers/Usb/Usb_Device/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Libraries -I../Libraries/Drivers/Devices -I../Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC -I../Libraries/Drivers/Usb/STM32_USB_Device_Library/Core -I../Libraries/Drivers/Usb/Usb_Device/Cdc -I../Libraries/Drivers/Usb/Usb_Device/Target -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-Drivers-2f-Usb-2f-Usb_Device-2f-Target

clean-Libraries-2f-Drivers-2f-Usb-2f-Usb_Device-2f-Target:
	-$(RM) ./Libraries/Drivers/Usb/Usb_Device/Target/usbd_cdc_conf.d ./Libraries/Drivers/Usb/Usb_Device/Target/usbd_cdc_conf.o ./Libraries/Drivers/Usb/Usb_Device/Target/usbd_cdc_conf.su

.PHONY: clean-Libraries-2f-Drivers-2f-Usb-2f-Usb_Device-2f-Target

