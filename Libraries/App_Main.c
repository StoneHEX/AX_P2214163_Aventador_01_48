/*
 * App_Main.c
 *
 *  Created on: Nov 7, 2022
 *      Author: fil
 */
#include "main.h"

__attribute__ ((aligned (4)))	SystemParametersTypeDef		SystemParameters;
__attribute__ ((aligned (4)))	SystemTypeDef				System;

static void SetupDefaults(void)
{
	HAL_GPIO_WritePin(BRD_RST__GPIO_Port, BRD_RST__Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BRD_WAKE__GPIO_Port, BRD_WAKE__Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(POWER_EN__GPIO_Port, POWER_EN__Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(CARRIER_PWR_ENABLE_GPIO_Port, CARRIER_PWR_ENABLE_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(ON_5V_MODULE_GPIO_Port, ON_5V_MODULE_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SLEEP_WAKE_GPIO_Port, SLEEP_WAKE_Pin,GPIO_PIN_RESET);				//external mosfet
	HAL_GPIO_WritePin(SYS_RESET_OUT_GPIO_Port, SYS_RESET_OUT_Pin,GPIO_PIN_RESET);			//external mosfet
	HAL_GPIO_WritePin(SEQUENCER_ACTIVE_GPIO_Port, SEQUENCER_ACTIVE_Pin,GPIO_PIN_SET); 	// active low

	System.power_state_machine = IDLE;
	System.usb_timeout = USB_TIMEOUT;
}

uint8_t	USB_Tx(uint8_t *buf)
{
	CDC_Transmit_FS(buf,strlen((char *)buf));
	return 0;
}

void App_Timers(void)
{
	if (( System.tick_flags &TICK10ms_FLAG ) == TICK10ms_FLAG)
	{
		System.tick_flags &= ~TICK10ms_FLAG;
		System.tick100ms_cntr++;
		if ( System.tick100ms_cntr == 8 )
			System.tick_flags |= TICK80ms_FLAG;
		if ( System.tick100ms_cntr >= 9 )
		{
			System.tick_flags |= TICK100ms_FLAG;
			System.tick100ms_cntr = 0;
			System.tick1Sec_cntr++;
			if (( System.led_flags & LED_FLAGS_BOARD_ACTIVE) == LED_FLAGS_BOARD_ACTIVE)
			{
				if (( System.tick1Sec_cntr == 7 ) || ( System.tick1Sec_cntr == 9 ))
					HAL_GPIO_WritePin(SEQUENCER_ACTIVE_GPIO_Port, SEQUENCER_ACTIVE_Pin,GPIO_PIN_RESET);
				else
					HAL_GPIO_WritePin(SEQUENCER_ACTIVE_GPIO_Port, SEQUENCER_ACTIVE_Pin,GPIO_PIN_SET);
			}
			else
			{
				if ( System.tick1Sec_cntr == 9 )
					HAL_GPIO_WritePin(SEQUENCER_ACTIVE_GPIO_Port, SEQUENCER_ACTIVE_Pin,GPIO_PIN_RESET);
				else
					HAL_GPIO_WritePin(SEQUENCER_ACTIVE_GPIO_Port, SEQUENCER_ACTIVE_Pin,GPIO_PIN_SET);
			}
			if ( System.tick1Sec_cntr > 9 )
			{
				System.tick_flags |= TICK1Sec_FLAG;
				System.tick1Sec_cntr = 0;
				System.tick10Sec_cntr++;
				if ( System.tick10Sec_cntr > 9 )
				{
					System.tick_flags |= TICK10Sec_FLAG;
					System.tick10Sec_cntr = 0;
				}
			}
		}
	}
}

static void hiz_mco(void)
{
	uint32_t	moder;
	moder = GPIOA->MODER;
	moder &= ~MCOMASK;  	// pin PA8(bits 17:16) as Input 	(00)
	GPIOA->MODER = moder;
}

static void enable_mco(void)
{
	uint32_t	moder;
	moder = GPIOA->MODER;
	moder &= ~MCOMASK;  	// pin PA8(bits 17:16) as Input 	(00)
	moder |= ALTMODE;
	GPIOA->MODER = moder;
}

void App_Init(void)
{
	hiz_mco();
	SetupDefaults();
	MX_USB_Device_Init();
	Tick_Start();
	ADC_Start();
}

//uint8_t count_voltages = 0;
//uint8_t	vprint = 0;

void App_Loop(void)
{
	App_Timers();
	if (( System.tick_flags & TICK100ms_FLAG) == TICK100ms_FLAG)
	{
		System.tick_flags &= ~TICK100ms_FLAG;
		if (( System.system_flags & ADC1_FLAG) == ADC1_FLAG)
		{
			System.system_flags &= ~ADC1_FLAG;
			ADC_GetValues();
		}
		PowerStateMachine();
	}
	if (( System.system_flags & CHECK_RESET_FLAG ) == CHECK_RESET_FLAG)
	{
		if ( HAL_GPIO_ReadPin(SYS_RESET__GPIO_Port, SYS_RESET__Pin) == GPIO_PIN_SET)
		{
			CarrierPowerOn();
			enable_mco();
		}
		else
		{
			CarrierPowerOff();
			hiz_mco();
		}
	}
	else
	{
		CarrierPowerOff();
		hiz_mco();
	}
	USB_Bridge();
}
