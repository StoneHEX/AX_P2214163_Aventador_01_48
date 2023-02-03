/*
 * Term_Menus.c
 *
 *  Created on: Feb 2, 2023
 *      Author: fil
 */
#include "main.h"

static void PrintVersions(void)
{
	sprintf((char *)System.usb_tx_buf,"** Versions **\n\rBoard : %s\n\rHw %s\n\rSW %s\r\n\r\n",
					BOARD_NAME,
					HW_VERSION,
					SW_VERSION);
}

static void PrintVoltages(void)
{
	if ( PowerStateMachineGetState() == CHECK_FOR_PWRON_PRESSED)
		sprintf((char *)System.usb_tx_buf,"** Powers are OFF **\n\r1V2: %2.2f\r\n1V8: %2.2f\r\n3V3: %2.2f\r\n5V : %2.2f\r\nVIN: %2.2f\r\n\r\n",
			System.SENSE_1V2,System.SENSE_1V8,System.SENSE_3V3,System.SENSE_5V,System.SENSE_VIN);
	else
		sprintf((char *)System.usb_tx_buf,"** Powers are ON **\n\r1V2: %2.2f\r\n1V8: %2.2f\r\n3V3: %2.2f\r\n5V : %2.2f\r\nVIN: %2.2f\r\n\r\n",
			System.SENSE_1V2,System.SENSE_1V8,System.SENSE_3V3,System.SENSE_5V,System.SENSE_VIN);

}

static void PrintHelp(void)
{
	sprintf((char *)System.usb_tx_buf,"Aventador Menu\n\rp : displays voltages\n\rv : displays versions\r\nh : this help\r\n\r\n");
}

void ClearTerminal(void)
{
	sprintf((char *)System.usb_tx_buf,"\x1b[2J");
	HAL_Delay(50);
	USB_Tx(System.usb_tx_buf);
	HAL_Delay(50);
}

void Term_Menus(void)
{
	if (( System.usb_flags & USB_FLAGS_RTS_CHANGE) == USB_FLAGS_RTS_CHANGE)
	{
		PrintHelp();
		HAL_Delay(50);
		USB_Tx(System.usb_tx_buf);
		HAL_Delay(50);
		System.usb_flags &= ~USB_FLAGS_RTS_CHANGE;
	}
	if (( System.usb_flags & USB_FLAGS_RX_BUF) == USB_FLAGS_RX_BUF)
	{
		switch ( System.usb_rx_buf[0])
		{
		case	'p':
		case	'P':
			PrintVoltages();
			break;
		case	'v':
		case	'V':
			PrintVersions();
			break;
		case	'h':
		case	'H':
			PrintHelp();
			break;
		default:
			sprintf((char *)System.usb_tx_buf,"Unknown command\n\r");
			break;
		}
		USB_Tx(System.usb_tx_buf);
		System.usb_flags &= ~USB_FLAGS_RX_BUF;
	}
}

