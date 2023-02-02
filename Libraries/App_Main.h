/*
 * App_Main.h
 *
 *  Created on: Nov 7, 2022
 *      Author: fil
 */

#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#include <stdio.h>
#include <string.h>

extern	ADC_HandleTypeDef hadc1;
extern	ADC_HandleTypeDef hadc4;
extern	DMA_HandleTypeDef handle_GPDMA1_Channel0;
extern	UART_HandleTypeDef huart1;
extern	PCD_HandleTypeDef hpcd_USB_OTG_FS;
extern	TIM_HandleTypeDef htim2;
extern	TIM_HandleTypeDef htim3;
extern	TIM_HandleTypeDef htim6;
extern	TIM_HandleTypeDef htim7;

#define	ADC1_INPUTS		5

#define	OSC32K_TIMER	htim3
#define	OSC32K_CHANNEL	TIM_CHANNEL_4
#define	TICK_TIMER		htim6
#define	CDC_TIMER		htim7
#define	SERIAL_PORT		huart1
#define	SERIAL_PORT_TO	10
#define	USB_INIDELAY	10
#define	USB_TIMEOUT		100
#define	USB_BUF_LEN		64
#define	UART_BUF_LEN	128

#define CDC_RX_DATA_SIZE  2048
#define CDC_TX_DATA_SIZE  2048

#define	HW_VERSION		"0"
#define	SW_VERSION		"1.0.0"
#define	BOARD_NAME		"Aventador"

#define	MCOMASK		(3 << 16 )
#define	ALTMODE		(2 << 16 )
#define	MCOSHIFT	16

#define	ADC_CONVERSION_FACTOR	(3.3F/4096.0F)

/* 10k on 10k : 1.65V */
#define	SENSE_3V3_IDX	0
#define	SENSE_3V3_VAL	(ADC_CONVERSION_FACTOR * 1.75F)

/* 10k on 2.2k : 2.1639344262V */
#define	SENSE_VIN_IDX	1
#define	SENSE_VIN_VAL	(ADC_CONVERSION_FACTOR * 5.1F)
//#define	SENSE_VIN_VAL	(2.163F)

/* 10k on 10k : 2.5V */
#define	SENSE_5V_IDX	2
#define	SENSE_5V_VAL	(ADC_CONVERSION_FACTOR * 1.8F)

/* direct 1.8V */
#define	SENSE_1V8_IDX	3
#define	SENSE_1V8_VAL	(ADC_CONVERSION_FACTOR*0.85F)

/* direct 1.2V */
#define	SENSE_1V2_IDX	4
#define	SENSE_1V2_VAL	(ADC_CONVERSION_FACTOR)

#define	RING_BUFFER_MASK	0x0f
#define	RING_BUFFER_LEN	48

typedef struct _SystemParametersTypeDef
{
	char		Header[8];
	char		Version[4];
}SystemParametersTypeDef;

typedef struct _SystemTypeDef
{
	uint8_t			system_flags;
	uint8_t			tick_flags;
	uint8_t 		usb_flags;
	uint8_t 		buttons_flags;
	uint8_t 		led_flags;
	uint8_t 		buttons_delay;
	uint8_t			power_state_machine;
	uint8_t			power_state_machine_delay;
	uint8_t			power_state_machine_string[USB_BUF_LEN];
	uint16_t		tick100ms_cntr;
	uint16_t		tick1Sec_cntr;
	uint16_t		tick10Sec_cntr;
	uint16_t		adc1[ADC1_INPUTS];
	uint8_t			adc1_buf[USB_BUF_LEN];
	uint8_t			usb_rx_buf[USB_BUF_LEN+8];
	uint8_t			usb_rx_buf_len;
	uint8_t			usb_rx_buf_index;
	uint8_t			usb_tx_buf[USB_BUF_LEN];
	uint8_t			usb_tx_buf_len;
	uint8_t			usb_buf[USB_BUF_LEN];
	uint8_t			usb_buf_index;
	uint8_t			usb_buf_len;
	uint16_t		usb_timeout;
	uint8_t			uart_tx_buf[UART_BUF_LEN];
	uint8_t			uart_rx_buf[UART_BUF_LEN];
	uint8_t			uart_rx_index;
	uint8_t			uart_rx_insertion_index;
	uint8_t			uart_rx_extraction_index;
	uint8_t			uart_rx_char;
	uint8_t			uart_flags;
	uint8_t			uart_errors;
	float			SENSE_3V3,SENSE_VIN,SENSE_5V,SENSE_1V8,SENSE_1V2;
}SystemTypeDef;

/* system_flags */
#define	ADC1_FLAG				0x01
#define	USB_FLAG				0x02
#define	CHECK_RESET_FLAG				0x04
// not used						0x08
// not used						0x10
// not used						0x20
// not used						0x40
#define	USB_ENABLE_FLAG		0x80

/* tick_flags */
#define	TICK10Sec_FLAG			0x01
#define	TICK1Sec_FLAG			0x02
#define	TICK100ms_FLAG			0x04
#define	TICK80ms_FLAG			0x08
#define	TICK50ms_FLAG			0x10
#define	TICK10ms_FLAG			0x20
// not used						0x20
// not used						0x40
// not used						0x80

/* usb_flags */
#define	USB_FLAGS_RTS_STATUS	0x02
#define	USB_FLAGS_DTR_STATUS	0x01
#define	USB_FLAGS_RTS_CHANGE	0x04
#define	USB_FLAGS_DTR_CHANGE	0x08
#define	USB_FLAGS_MENU_MODE		0x10
#define	USB_FLAGS_RX_BUF		0x20
#define	USB_FLAGS_HEADEROK		0x40
#define	USB_FLAGS_PKTCOMPLETE	0x80

/* buttons_flags */
// not used						0x01
// not used						0x02
// not used						0x04
// not used						0x08
// not used						0x10
#define	BUTTON_FLAGS_BOARD_REC	0x20
#define	BUTTON_FLAGS_BOARD_RST	0x40
#define	BUTTON_FLAGS_BOARD_WKE	0x80

/* led_flags */
// not used						0x01
// not used						0x02
// not used						0x04
// not used						0x08
// not used						0x10
// not used						0x20
// not used						0x40
#define	LED_FLAGS_BOARD_ACTIVE	0x80

/* uart_flags */
#define	UART_FLAGS_TOUTRX		0x01
// not used						0x02
// not used						0x04
// not used						0x08
// not used						0x10
#define	UART_FLAGS_ERROR		0x20
#define	UART_FLAGS_TX_END		0x40
#define	UART_FLAGS_RX_CHAR		0x80

#define	POWER_ON_DELAY		2
#define	POWER_OFF_DELAY		19
#define	EMERGENCY_POWER_OFF	9
#define	POWER_ON_WAIT		5

#define	POWER_GOOD_TIMEOUT	5	/* 500 mSec timeout on power good */

enum POWER_STATE
{
	IDLE,
	CHECK_FOR_PWRON_PRESSED,
	BOARD_PWRON,
	CHECK_FOR_PWRON_RELEASED,
	POWERON_WAIT,
	CHECK_FOR_SYS_RESET_HIGH,
	CHECK_FOR_BUTTONS,
	WAIT_FOR_PWRON_RELEASED,
};

extern	SystemParametersTypeDef		SystemParameters;
extern	SystemTypeDef				System;

extern	void App_Init(void);
extern	void App_Loop(void);
extern	void UsbPktReceived(uint8_t* Buf, uint32_t Len);
extern	void Debug_PrintState(void);
extern	uint8_t	USB_Tx(uint8_t *buf);


extern	uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);
extern	void MX_USB_Device_Init(void);

#include	"Power_StateMachine.h"
#include	"USB_Bridge.h"
#include	"Term_Menus.h"
#include	"Drivers/Devices/adc_dma.h"
#include	"Drivers/Devices/irqs.h"
#include	"Drivers/Devices/ticks.h"

/* devel */
//#define	UARTRX_IRQ	1


#endif /* APP_MAIN_H_ */
