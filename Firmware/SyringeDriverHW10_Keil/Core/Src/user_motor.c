#include "user_motor.h"
#include "user_adc.h"
#include "user_eeprom.h"
__IO uint8_t motorIsStartlocal=0;
__IO uint8_t motorErrNum=0;
/*-----------------------------------------------------------------*/
void motorStop()
{
	HAL_TIM_PWM_Stop(&motorTIMER,motorCHANNEL2);
	HAL_TIM_PWM_Stop(&motorTIMER,motorCHANNEL1);
	motorIsStartlocal=0;
}
/*-----------------------------------------------------------------*/
double motorCalcDuty(void)
{
	double r=(double)EEValue_VOLBAT*EEValue_PWM/(double)adcGetRaw(adcBATVOLT);
	return r;
}
/*-----------------------------------------------------------------*/
void motorStart(double percent)
{
	uint16_t arr=__HAL_TIM_GET_AUTORELOAD(&motorTIMER);
	uint16_t compare=(uint16_t) ((double)arr*percent/100.0);
	if(compare>arr)
		compare=arr;
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
