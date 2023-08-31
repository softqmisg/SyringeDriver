#ifndef __USER_ADC_H__
#define __USER_ADC_H__
#include "stm32f1xx_hal.h"
#define adcBATCUR		0
#define adcMOTCUR		1
#define adcHALVOLT		2
#define adcBATVOLT		3

extern 	uint16_t adcRawValue[4];

uint16_t adcGetRaw(uint8_t channel);
double adcGetValue(uint8_t channel);
#endif