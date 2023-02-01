/*
 * adc_dma.c
 *
 *  Created on: Sep 12, 2022
 *      Author: fil
 */

#include "main.h"


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if ( hadc == &hadc1 )
		System.system_flags |= ADC1_FLAG;
}

void ADC_Start(void)
{
	/* ST HAL bug fix */
	HAL_PWREx_EnableVddA() ;
	__HAL_RCC_PWR_CLK_ENABLE();
	/* ST HAL bug fix end*/
	HAL_ADCEx_Calibration_Start(&hadc1,ADC_CALIB_OFFSET_LINEARITY,ADC_SINGLE_ENDED);
	HAL_Delay(10);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&System.adc1[0], ADC1_INPUTS);
}

void ADC_GetValues(void)
{
	System.SENSE_3V3  = (float )System.adc1[SENSE_3V3_IDX]  * SENSE_3V3_VAL;
	System.SENSE_VIN  = (float )System.adc1[SENSE_VIN_IDX] * SENSE_VIN_VAL;
	System.SENSE_5V   = (float )System.adc1[SENSE_5V_IDX]  * SENSE_5V_VAL;
	System.SENSE_1V8  = (float )System.adc1[SENSE_1V8_IDX]  * SENSE_1V8_VAL;
	System.SENSE_1V2  = (float )System.adc1[SENSE_1V2_IDX]  * SENSE_1V2_VAL;

	sprintf((char *)System.adc1_buf,"Board : %s\n\rVoltage Monitor\r\n1V2: %2.2f\r\n1V8: %2.2f\r\n3V3: %2.2f\r\n5V : %2.2f\r\nVIN: %2.2f\r\nHw %s\n\rSW %s\r\n\r\n",
			BOARD_NAME,
			System.SENSE_1V2,System.SENSE_1V8,System.SENSE_3V3,System.SENSE_5V,System.SENSE_VIN,
			HW_VERSION,
			SW_VERSION);
}
