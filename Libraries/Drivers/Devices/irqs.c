/*
 * irqs.c
 *
 *  Created on: Oct 11, 2022
 *      Author: fil
 */

#include "main.h"
#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

#ifdef IRQ_MODE
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
{
	if ( huart == &SERIAL_PORT)
	{
		System.uart_rx_buf[System.uart_rx_insertion_index] = System.uart_rx_char;
		System.uart_rx_insertion_index++;
		System.uart_rx_insertion_index &= UART_BUF_LEN_MASK;
		System.usb_serial2usb_count_rx++;
		if ( System.usb_serial2usb_count_rx > MAX_UART2USB_BUF_LEN )
		{
			System.usb_serial2usb_count_rx = 0;
			System.uart_flags |= UART_FLAGS_RX_CHAR;
		}
		TIM7->CNT = 0x0;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if ( htim == &TICK_TIMER )
		System.tick_flags |= TICK10ms_FLAG;
	if ( htim == &CDC_TIMER )
		System.uart_flags |= UART_FLAGS_TOUTRX;
}
#else
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if ( htim == &TICK_TIMER )
		System.tick_flags |= TICK10ms_FLAG;
}

#endif

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if ( huart == &SERIAL_PORT)
	{
		System.uart_flags |= UART_FLAGS_ERROR;
		System.uart_errors++;
	}
}





