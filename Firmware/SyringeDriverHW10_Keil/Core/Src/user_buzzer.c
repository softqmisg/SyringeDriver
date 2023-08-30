#include "user_buzzer.h"

uint16_t *local_tone;
static __IO uint16_t local_index=0,local_length;
static __IO int8_t local_forward=1;

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
uint16_t period_cmp_value;
uint32_t frq_pwm_value;
	if(htim->Instance==BUZZERPERIOD_INSTANCE)
	{
		if(local_forward==0)
		{
				if(local_index==0)
				{
					local_index=local_length;
				}
				else
				{					
					local_index-=2;			
				}
			if(local_tone[local_index]==TONES_REPEAT)
					local_index=local_length-2;
			if(local_tone[local_index]==TONES_END)
			{
				HAL_TIM_PWM_Stop(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL);
				HAL_TIM_OC_Stop_IT(&BUZZERPERIOD_TIMER,BUZZERPERIOD_CHANNEL);
			}
			else
			{
				if(local_tone[local_index]==0)
				{
					frq_pwm_value=0;
				__HAL_TIM_SET_AUTORELOAD(&BUZZERFREQ_TIMER,(uint16_t)65535);
				__HAL_TIM_SET_COMPARE(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL,0);				
				}
				else
				{
					frq_pwm_value=(uint32_t)BUZZERFREQ_CLK/local_tone[local_index]-1;
					__HAL_TIM_SET_AUTORELOAD(&BUZZERFREQ_TIMER,(uint16_t)frq_pwm_value);
					__HAL_TIM_SET_COMPARE(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL,frq_pwm_value/2);
				}
					__HAL_TIM_SET_COUNTER(&BUZZERFREQ_TIMER, 0);//init timer counter

					period_cmp_value=(uint16_t)BUZEERPERIOD_CLK/1000*local_tone[local_index+1]-1;
					__HAL_TIM_SET_COMPARE(&BUZZERPERIOD_TIMER,BUZZERPERIOD_CHANNEL,period_cmp_value);
					__HAL_TIM_SET_COUNTER(&BUZZERPERIOD_TIMER, 0);//init timer counter
			}
		}
		else if(local_forward)
		{
			if(local_tone[local_index]==TONES_REPEAT)
					local_index=0;
			if(local_tone[local_index]==TONES_END)
			{
				HAL_TIM_PWM_Stop(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL);
				HAL_TIM_OC_Stop_IT(&BUZZERPERIOD_TIMER,BUZZERPERIOD_CHANNEL);
			}
			else
			{
				if(local_tone[local_index]==0)
				{
					frq_pwm_value=0;
				__HAL_TIM_SET_AUTORELOAD(&BUZZERFREQ_TIMER,(uint16_t)65535);
				__HAL_TIM_SET_COMPARE(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL,0);				
				}
				else
				{
					frq_pwm_value=(uint32_t)BUZZERFREQ_CLK/local_tone[local_index]-1;
					__HAL_TIM_SET_AUTORELOAD(&BUZZERFREQ_TIMER,(uint16_t)frq_pwm_value);
					__HAL_TIM_SET_COMPARE(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL,frq_pwm_value/2);
				}
					__HAL_TIM_SET_COUNTER(&BUZZERFREQ_TIMER, 0);//init timer counter

					period_cmp_value=(uint16_t)BUZEERPERIOD_CLK/1000*local_tone[local_index+1]-1;
					__HAL_TIM_SET_COMPARE(&BUZZERPERIOD_TIMER,BUZZERPERIOD_CHANNEL,period_cmp_value);
					__HAL_TIM_SET_COUNTER(&BUZZERPERIOD_TIMER, 0);//init timer counter

				local_index+=2;
			}
		}
			
	}
}
/**
*/
void mute_tone(void)
{
	HAL_TIM_PWM_Stop(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL);
	HAL_TIM_OC_Stop_IT(&BUZZERPERIOD_TIMER,BUZZERPERIOD_CHANNEL);
}
/**
	freq=in HZ
	dur= in ms
	length
*/
void play_tone(uint16_t *tones)
{
	local_tone=tones;
	local_index=0;
	local_forward=1;
	
	__HAL_TIM_SET_AUTORELOAD(&BUZZERFREQ_TIMER,(uint16_t)0);
	__HAL_TIM_SET_COMPARE(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL,0);
	__HAL_TIM_SET_COUNTER(&BUZZERFREQ_TIMER, 0);//init timer counter
	
	HAL_TIM_PWM_Start(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL); //start pwm waiting for trigger of timer2
	HAL_TIM_OC_Start_IT(&BUZZERPERIOD_TIMER,BUZZERPERIOD_CHANNEL); 	//start timerperiod for first period	
	
	HAL_TIM_GenerateEvent(&BUZZERPERIOD_TIMER,TIM_EVENTSOURCE_CC1);
}
void play_tone_reverse(uint16_t *tones)
{
	local_forward=0;
	local_index=0;
	while(tones[local_index]!=TONES_END && tones[local_index]!=TONES_REPEAT)
	{
		local_index+=2;
	}
	local_tone=tones;
	local_length=local_index;
	
	__HAL_TIM_SET_AUTORELOAD(&BUZZERFREQ_TIMER,(uint16_t)0);
	__HAL_TIM_SET_COMPARE(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL,0);
	__HAL_TIM_SET_COUNTER(&BUZZERFREQ_TIMER, 0);//init timer counter
	
	HAL_TIM_PWM_Start(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL); //start pwm waiting for trigger of timer2
	HAL_TIM_OC_Start_IT(&BUZZERPERIOD_TIMER,BUZZERPERIOD_CHANNEL); 	//start timerperiod for first period	
	
	HAL_TIM_GenerateEvent(&BUZZERPERIOD_TIMER,TIM_EVENTSOURCE_CC1);
}