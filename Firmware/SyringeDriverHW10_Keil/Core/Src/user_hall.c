#include "user_hall.h"
#include "user_motor.h"
#include "user_eeprom.h"
#include "user_adc.h"
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
	if(adcGetRaw(adcHALVOLT)>threshold)
		return 0;
	return 1;
}