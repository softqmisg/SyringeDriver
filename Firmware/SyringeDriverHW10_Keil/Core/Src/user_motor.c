#include "user_motor.h"
#include "user_adc.h"
#include "user_eeprom.h"
__IO uint8_t motorIsStartlocal=0;
/*-----------------------------------------------------------------*/
void motorStop()
{
	HAL_TIM_PWM_Stop(&motorTIMER,motorCHANNEL2);
	HAL_TIM_PWM_Stop(&motorTIMER,motorCHANNEL1);
	motorIsStartlocal=0;
}
/*-----------------------------------------------------------------*/
double motorDuty()
{
	double r=(double)EEValue_VOLBAT*100.0/(double)adcGetRaw(adcBATVOLT);
	return r;
}
/*-----------------------------------------------------------------*/
uint8_t motorStart(double percent)
{
	uint16_t compare=(uint16_t) (__HAL_TIM_GET_AUTORELOAD(&motorTIMER)*percent/100.0);
	HAL_TIM_PWM_Start(&motorTIMER,motorCHANNEL1);
	__HAL_TIM_SET_COMPARE(&motorTIMER,motorCHANNEL2,compare);      
	HAL_TIM_PWM_Start(&motorTIMER,motorCHANNEL2);	
	motorIsStartlocal=1;
}
/*-----------------------------------------------------------------*/
uint8_t motorIsStart()
{
	return motorIsStartlocal;
}
void hallON()
{
		HAL_TIM_PWM_Start(&motorTIMER,motorCHANNEL1);
}
void hallOFF()
{
		HAL_TIM_PWM_Stop(&motorTIMER,motorCHANNEL1);
}