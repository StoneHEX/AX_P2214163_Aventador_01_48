/*
 * Power_StateMachine.c
 *
 *  Created on: Nov 7, 2022
 *      Author: fil
 */

#include "main.h"

char val[32];

void Debug_PrintVoltages(uint8_t state)
{
		sprintf((char *)System.usb_tx_buf,"Board : %s\n\rVoltage Monitor\r\n1V2: %2.2f\r\n1V8: %2.2f\r\n3V3: %2.2f\r\n5V : %2.2f\r\nVIN: %2.2f\r\nHw %s\n\rSW %s\r\n\r\n",
				BOARD_NAME,
				System.SENSE_1V2,System.SENSE_1V8,System.SENSE_3V3,System.SENSE_5V,System.SENSE_VIN,
				HW_VERSION,
				SW_VERSION);
	USB_Tx(System.usb_tx_buf);
}

void BoardPowerOn(void)
{
	HAL_GPIO_WritePin(ON_5V_MODULE_GPIO_Port, ON_5V_MODULE_Pin,GPIO_PIN_SET);
}

void BoardPowerOff(void)
{
	HAL_GPIO_WritePin(ON_5V_MODULE_GPIO_Port, ON_5V_MODULE_Pin,GPIO_PIN_RESET);
}

void CarrierPowerOn(void)
{
	HAL_GPIO_WritePin(CARRIER_PWR_ENABLE_GPIO_Port, CARRIER_PWR_ENABLE_Pin,GPIO_PIN_SET);
	HAL_TIM_PWM_Start(&OSC32K_TIMER, OSC32K_CHANNEL);
	System.led_flags |= LED_FLAGS_BOARD_ACTIVE;
}

void CarrierPowerOff(void)
{
	HAL_TIM_PWM_Stop(&OSC32K_TIMER, OSC32K_CHANNEL);
	HAL_GPIO_WritePin(CARRIER_PWR_ENABLE_GPIO_Port, CARRIER_PWR_ENABLE_Pin,GPIO_PIN_RESET);
	System.led_flags &= ~LED_FLAGS_BOARD_ACTIVE;
}

void force_poweron(void)
{
	System.power_state_machine_delay = POWER_ON_WAIT;
	System.power_state_machine = POWERON_WAIT;
	BoardPowerOn();
}

void PowerStateMachine(void)
{
	switch(System.power_state_machine)
	{
	case	IDLE:
		System.power_state_machine = CHECK_FOR_PWRON_PRESSED;
		HAL_GPIO_WritePin(POWER_EN__GPIO_Port, POWER_EN__Pin,GPIO_PIN_SET);
		System.power_state_machine_delay = POWER_ON_WAIT;
		System.buttons_delay = POWER_ON_DELAY;
		break;
	case	CHECK_FOR_PWRON_PRESSED:
		if ( HAL_GPIO_ReadPin(BRD_WAKE__GPIO_Port, BRD_WAKE__Pin) == GPIO_PIN_RESET)
		{
			if ( System.buttons_delay != 0 )
			{
				System.buttons_delay --;
				if ( System.buttons_delay == 0 )
				{
					System.power_state_machine_delay = POWER_ON_WAIT;
					System.power_state_machine = POWERON_WAIT;
					BoardPowerOn();
				}
			}
		}
		else
		{
			System.power_state_machine_delay = POWER_ON_WAIT;
			System.buttons_delay = POWER_ON_DELAY;
		}
		break;
	case	POWERON_WAIT:
		if ( System.power_state_machine_delay != 0 )
		{
			System.power_state_machine_delay --;
		}
		else
		{
			HAL_GPIO_WritePin(POWER_EN__GPIO_Port, POWER_EN__Pin,GPIO_PIN_RESET);
			System.system_flags |= CHECK_RESET_FLAG;
			System.power_state_machine = CHECK_FOR_SYS_RESET_HIGH;
			System.power_state_machine_delay = EMERGENCY_POWER_OFF;
		}
		break;
	case	CHECK_FOR_SYS_RESET_HIGH:
		if ( HAL_GPIO_ReadPin(SYS_RESET__GPIO_Port, SYS_RESET__Pin) == GPIO_PIN_RESET)
		{
			if ( System.power_state_machine_delay != 0 )
			{
				System.power_state_machine_delay --;
			}
			else
			{
				// No reset arrived within EMERGENCY_POWER_OFF time, shutdown
				HAL_GPIO_WritePin(POWER_EN__GPIO_Port, POWER_EN__Pin,GPIO_PIN_SET);
				BoardPowerOff();
				System.power_state_machine = WAIT_FOR_PWRON_RELEASED;
			}
		}
		else
			System.power_state_machine = CHECK_FOR_PWRON_RELEASED;
		break;
	case	CHECK_FOR_PWRON_RELEASED:
		if ( HAL_GPIO_ReadPin(BRD_WAKE__GPIO_Port, BRD_WAKE__Pin) == GPIO_PIN_SET)
		{
			System.buttons_delay = POWER_OFF_DELAY;
			System.power_state_machine = CHECK_FOR_BUTTONS;
		}
		break;
	case	CHECK_FOR_BUTTONS:
		if ( HAL_GPIO_ReadPin(BRD_WAKE__GPIO_Port, BRD_WAKE__Pin) == GPIO_PIN_RESET)
		{
			System.buttons_delay --;
			if ( System.buttons_delay == 0 )
			{
				/* User requested shutdown */
				System.system_flags  &= ~CHECK_RESET_FLAG;
				HAL_GPIO_WritePin(POWER_EN__GPIO_Port, POWER_EN__Pin,GPIO_PIN_SET);
				CarrierPowerOff();
				BoardPowerOff();
				System.power_state_machine = WAIT_FOR_PWRON_RELEASED;
			}
		}
		else
		{
			System.buttons_delay = POWER_OFF_DELAY;
		}
		/* Reset low from board */
		if ( HAL_GPIO_ReadPin(SYS_RESET__GPIO_Port, SYS_RESET__Pin) == GPIO_PIN_RESET)
		{
			System.system_flags  &= ~CHECK_RESET_FLAG;
			CarrierPowerOff();
			BoardPowerOff();
			System.power_state_machine = IDLE;
		}
		break;
	case	WAIT_FOR_PWRON_RELEASED:
		if ( HAL_GPIO_ReadPin(BRD_WAKE__GPIO_Port, BRD_WAKE__Pin) == GPIO_PIN_SET)
			System.power_state_machine = IDLE;
		break;
	default:
		System.power_state_machine = IDLE;
		break;
	}
}
