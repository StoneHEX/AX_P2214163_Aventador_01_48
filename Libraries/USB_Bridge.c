/*
 * USB_Bridge.c
 *
 *  Created on: Dec 6, 2022
 *      Author: fil
 */

#include "main.h"

void UsbPktReceived(uint8_t* Buf, uint32_t Len)
{
	System.usb_rx_buf_len = Len;
	memcpy(System.usb_rx_buf,Buf,System.usb_rx_buf_len);
	System.usb_flags |= USB_FLAGS_RX_BUF;
}

void UsbControlCallback(uint8_t cmd, uint8_t* pbuf, uint16_t length)
{
	if ( pbuf[0] == '!' )
	{
		if ( (pbuf[2] & USB_FLAGS_DTR_STATUS ) == USB_FLAGS_DTR_STATUS)
		{
			if (( System.usb_flags & USB_FLAGS_DTR_STATUS) == 0 )
			{
				System.usb_flags |= USB_FLAGS_DTR_STATUS;
				System.usb_flags |= USB_FLAGS_DTR_CHANGE;
			}
		}
		else
		{
			if (( System.usb_flags & USB_FLAGS_DTR_STATUS) == USB_FLAGS_DTR_STATUS )
			{
				System.usb_flags &= ~USB_FLAGS_DTR_STATUS;
				System.usb_flags |= USB_FLAGS_DTR_CHANGE;
			}
		}
		if ( (pbuf[2] & USB_FLAGS_RTS_STATUS ) == USB_FLAGS_RTS_STATUS)
		{
			if (( System.usb_flags & USB_FLAGS_RTS_STATUS) == 0 )
			{
				System.usb_flags |= USB_FLAGS_RTS_STATUS;
				System.usb_flags |= USB_FLAGS_RTS_CHANGE;
			}
		}
		else
		{
			if (( System.usb_flags & USB_FLAGS_RTS_STATUS) == USB_FLAGS_RTS_STATUS )
			{
				System.usb_flags &= ~USB_FLAGS_RTS_STATUS;
				System.usb_flags |= USB_FLAGS_RTS_CHANGE;
			}
		}
		if (( System.usb_flags & USB_FLAGS_DTR_STATUS ) == 1)
		{
			if (( System.usb_flags & USB_FLAGS_RTS_STATUS ) == 0)
				System.usb_flags |= USB_FLAGS_MENU_MODE;
			else
				System.usb_flags &= ~USB_FLAGS_MENU_MODE;
		}
	}
}

uint8_t	max_buflen = 0;

void USB_Bridge(void)
{
uint8_t		buflen;

	if (( System.usb_flags & USB_FLAGS_MENU_MODE ) == USB_FLAGS_MENU_MODE)
	{
			Term_Menus();
	}
	else if ((( System.usb_flags & USB_FLAGS_RTS_STATUS ) == USB_FLAGS_RTS_STATUS) && (( System.usb_flags & USB_FLAGS_RTS_CHANGE) == USB_FLAGS_RTS_CHANGE))
	{
		ClearTerminal();
		System.usb_flags &= ~USB_FLAGS_RTS_CHANGE;
		System.usb_flags &= ~USB_FLAGS_MENU_MODE;
	}
	else
	{
		if (( System.usb_flags & USB_FLAGS_RX_BUF) == USB_FLAGS_RX_BUF)
		{
			HAL_UART_Transmit_DMA(&SERIAL_PORT, System.usb_rx_buf, System.usb_rx_buf_len);
			System.usb_flags &= ~USB_FLAGS_RX_BUF;
		}
		else
		{
			HAL_UART_Receive(&SERIAL_PORT, System.uart_rx_buf, RING_BUFFER_LEN,SERIAL_PORT_TO);
			buflen = RING_BUFFER_LEN - SERIAL_PORT.RxXferCount;
			if ( buflen > max_buflen)
				max_buflen = buflen;
			CDC_Transmit_FS(System.uart_rx_buf,buflen);
		}
	}
}

