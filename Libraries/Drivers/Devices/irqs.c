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

#ifdef	UARTRX_IRQ

void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
{
	System.uart_flags |= UART_FLAGS_RX_CHAR;
	TIM7->CNT &= 0x0; // restart the timer
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





