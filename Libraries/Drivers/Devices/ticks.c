/*
 * ticks.c
 *
 *  Created on: Sep 12, 2022
 *      Author: fil
 */

#include "main.h"



void Tick_Start(void)
{
	HAL_TIM_Base_Start_IT(&TICK_TIMER);
	HAL_TIM_Base_Start_IT(&CDC_TIMER);
}
