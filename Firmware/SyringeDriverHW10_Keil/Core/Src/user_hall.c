#include "user_hall.h"
#include "user_motor.h"
#include "user_eeprom.h"
#include "user_adc.h"
#include <stdio.h>
void hallON()
{
		HAL_TIM_PWM_Start(&motorTIMER,motorCHANNEL1);
}
/*-------------------------------------------------------------*/
void hallOFF()
{
		HAL_TIM_PWM_Stop(&motorTIMER,motorCHANNEL1);
}
/*-------------------------------------------------------------*/
uint8_t hallIsEnd()
{
	uint16_t threshold=EEValue_VHALLF+(uint16_t)(EEValue_VHALLE-EEValue_VHALLF)*HALLEND_PERCENT/100;
	uint16_t hallvolt=adcGetRaw(adcHALVOLT);
	hallvolt=adcGetRaw(adcHALVOLT);
	printf("threshold:%d\n\r",threshold);
	printf("hallvolt:%d\n\r",hallvolt);	
	

	if(hallvolt>threshold)
		return 0;
	return 1;
}