#include "user_buzzer.h"

__IO uint8_t playState=0;
uint16_t *local_freq,*local_dur,local_lenght;
__IO uint16_t local_index=0;

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
uint16_t period_cmp_value;
uint32_t frq_pwm_value;
	if(htim->Instance==BUZZERPERIOD_INSTANCE)
	{
		if(local_freq[local_index]==TONES_REPEAT)
				local_index=0;
		if(local_freq[local_index]==TONES_END)
		{
			HAL_TIM_PWM_Stop(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL);
			HAL_TIM_OC_Stop_IT(&BUZZERPERIOD_TIMER,BUZZERPERIOD_CHANNEL);
		}
		else
		{
			if(local_freq[local_index]==0)
			{
				frq_pwm_value=0;
			__HAL_TIM_SET_AUTORELOAD(&BUZZERFREQ_TIMER,(uint16_t)65535);
			__HAL_TIM_SET_COMPARE(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL,0);				
			}
			else
			{
				frq_pwm_value=(uint32_t)BUZZERFREQ_CLK/local_freq[local_index]-1;
			__HAL_TIM_SET_AUTORELOAD(&BUZZERFREQ_TIMER,(uint16_t)frq_pwm_value);
			__HAL_TIM_SET_COMPARE(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL,frq_pwm_value/2);
			}
			__HAL_TIM_SET_COUNTER(&BUZZERFREQ_TIMER, 0);//init timer counter

			period_cmp_value=(uint16_t)BUZEERPERIOD_CLK/1000*local_dur[local_index]-1;
		__HAL_TIM_SET_COMPARE(&BUZZERPERIOD_TIMER,BUZZERPERIOD_CHANNEL,period_cmp_value);
		__HAL_TIM_SET_COUNTER(&BUZZERPERIOD_TIMER, 0);//init timer counter

			local_index++;
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
void play_tone(uint16_t *freq,uint16_t *dur,uint16_t length)
{
	local_freq=freq;
	local_dur=dur;
	local_lenght=length;
	local_index=0;
	

	__HAL_TIM_SET_AUTORELOAD(&BUZZERFREQ_TIMER,(uint16_t)0);
	__HAL_TIM_SET_COMPARE(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL,0);
	__HAL_TIM_SET_COUNTER(&BUZZERFREQ_TIMER, 0);//init timer counter
	
	HAL_TIM_PWM_Start(&BUZZERFREQ_TIMER,BUZZERFREQ_CHANNEL); //start pwm waiting for trigger of timer2
	HAL_TIM_OC_Start_IT(&BUZZERPERIOD_TIMER,BUZZERPERIOD_CHANNEL); 	//start timerperiod for first period	
	
	HAL_TIM_GenerateEvent(&BUZZERPERIOD_TIMER,TIM_EVENTSOURCE_CC1);
}
