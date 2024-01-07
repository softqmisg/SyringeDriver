#include "user_motor.h"
#include "user_adc.h"
#include "user_eeprom.h"
#include <stdio.h>
__IO uint8_t motorIsStartlocal=0;
__IO uint8_t motorErrNum=0;
/*-----------------------------------------------------------------*/
void motorPositive(uint8_t onoff)
{
	if(onoff)
	{
		HAL_GPIO_WritePin(MOTORP_GPIO_Port,MOTORP_Pin,GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(MOTORP_GPIO_Port,MOTORP_Pin,GPIO_PIN_RESET);
	}
}
/*-----------------------------------------------------------------*/
void motorStop()
{
	HAL_TIM_PWM_Stop(&motorTIMER,motorCHANNEL2);
	motorPositive(0);
	motorIsStartlocal=0;
}
/*-----------------------------------------------------------------*/
double motorCalcDuty(void)
{
	double r;
	double batvolt=(double)adcGetRaw(adcBATVOLT);
	batvolt=(double)adcGetRaw(adcBATVOLT);
	printf("EE Volt:%d,cu Volt:%.1f\n\r",EEValue_VOLBAT,batvolt);	
	if(batvolt>0)
	{
		r=(double)EEValue_VOLBAT*((double)EEValue_PWM/10.0)/batvolt;
	}
	else
	{
		r=0;
	}
	return r;
}
/*-----------------------------------------------------------------*/
void motorStart(double percent)
{
	uint16_t arr=__HAL_TIM_GET_AUTORELOAD(&motorTIMER);
	uint16_t compare=(uint16_t) ((double)arr*percent/100.0);
	if(compare>arr)
		compare=arr;
	motorPositive(1);HAL_Delay(30);
	__HAL_TIM_SET_COMPARE(&motorTIMER,motorCHANNEL2,compare);      
	HAL_TIM_PWM_Start(&motorTIMER,motorCHANNEL2);	
	motorIsStartlocal=1;
}
/*-----------------------------------------------------------------*/
uint8_t motorIsStart()
{
	return motorIsStartlocal;
}
