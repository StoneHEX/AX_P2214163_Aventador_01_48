################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_core.c \
../Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_ctlreq.c \
../Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_ioreq.c 

OBJS += \
./Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_core.o \
./Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_ctlreq.o \
./Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_ioreq.o 

C_DEPS += \
./Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_core.d \
./Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_ctlreq.d \
./Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/%.o Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/%.su: ../Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/%.c Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Libraries -I../Libraries/Drivers/Devices -I../Libraries/Drivers/Usb/STM32_USB_Device_Library/Class/CDC -I../Libraries/Drivers/Usb/STM32_USB_Device_Library/Core -I../Libraries/Drivers/Usb/Usb_Device/Cdc -I../Libraries/Drivers/Usb/Usb_Device/Target -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-Drivers-2f-Usb-2f-STM32_USB_Device_Library-2f-Core

clean-Libraries-2f-Drivers-2f-Usb-2f-STM32_USB_Device_Library-2f-Core:
	-$(RM) ./Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_core.d ./Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_core.o ./Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_core.su ./Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_ctlreq.d ./Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_ctlreq.o ./Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_ctlreq.su ./Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_ioreq.d ./Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_ioreq.o ./Libraries/Drivers/Usb/STM32_USB_Device_Library/Core/usbd_ioreq.su

.PHONY: clean-Libraries-2f-Drivers-2f-Usb-2f-STM32_USB_Device_Library-2f-Core

