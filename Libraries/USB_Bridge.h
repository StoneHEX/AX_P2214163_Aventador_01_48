/*
 * USB_Bridge.h
 *
 *  Created on: Dec 6, 2022
 *      Author: fil
 */

#ifndef USB_BRIDGE_H_
#define USB_BRIDGE_H_

#define	CDC_RTS			0x01
#define	CDC_DTR			0x02

extern	void USB_Bridge(void);
extern	void UsbControlCallback(uint8_t cmd, uint8_t* pbuf, uint16_t length);

#endif /* USB_BRIDGE_H_ */
