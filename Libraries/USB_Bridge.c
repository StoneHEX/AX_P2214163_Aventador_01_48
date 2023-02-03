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

#ifdef IRQ_MODE
static void process_serial(void)
{
	if ((( System.uart_flags & UART_FLAGS_TOUTRX) == UART_FLAGS_TOUTRX) || (( System.uart_flags & UART_FLAGS_RX_CHAR) == UART_FLAGS_RX_CHAR))
	{
		__disable_irq();
		if (( System.uart_flags & UART_FLAGS_TOUTRX) == UART_FLAGS_TOUTRX)
			System.uart_flags &= ~UART_FLAGS_TOUTRX;
		if (( System.uart_flags & UART_FLAGS_RX_CHAR) == UART_FLAGS_RX_CHAR)
			System.uart_flags &= ~UART_FLAGS_RX_CHAR;
		__enable_irq();
		System.usb_serial2usb_buf_len = 0;
		while(System.uart_rx_extraction_index != System.uart_rx_insertion_index)
		{
			System.usb_serial2usb_buf[System.usb_serial2usb_buf_len] = System.uart_rx_buf[System.uart_rx_extraction_index];
			System.uart_rx_extraction_index++;
			System.uart_rx_extraction_index &= UART_BUF_LEN_MASK;
			System.usb_serial2usb_buf_len ++;
		}
		if (( System.usb_serial2usb_buf_len  != 0 ) || ( System.usb_serial2usb_buf_len  > (USB_BUF_LEN/2)))
		{
			CDC_Transmit_FS(System.usb_serial2usb_buf,System.usb_serial2usb_buf_len );
			if ( System.usb_serial2usb_buf_len  > System.usb_serial2usb_max_buflen)
				System.usb_serial2usb_max_buflen = System.usb_serial2usb_buf_len ;
		}
	}
}

void USB_Bridge(void)
{
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
		if ((( System.uart_flags & UART_FLAGS_TOUTRX) == UART_FLAGS_TOUTRX) || (( System.uart_flags & UART_FLAGS_RX_CHAR) == UART_FLAGS_RX_CHAR))
		{
			process_serial();
		}
		HAL_UART_Receive_IT(&SERIAL_PORT, &System.uart_rx_char, 1);
	}
}

#else
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
#endif

