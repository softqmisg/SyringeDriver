#ifndef __USER_BUZZER_H__
#define __USER_BUZZER_H__

#include "stm32f1xx_hal.h"
#include "tim.h"


#define BUZZERPERIOD_TIMER		htim3
#define BUZZERPERIOD_INSTANCE	TIM3
#define BUZZERPERIOD_CHANNEL			TIM_CHANNEL_1
#define BUZEERPERIOD_CLK			10000 		//min period= 1/10000=0.1 ms ,max period= 65535/10000=6.5s

#define BUZZERFREQ_TIMER 				htim2
#define BUZZERFREQ_INSTANCE 		TIM2
#define BUZZERFREQ_CHANNEL			TIM_CHANNEL_1
#define BUZZERFREQ_CLK					1000000 //min frq=1000000/65535~15Hz, max freq=1MHz


#define TONES_END 		65535
#define TONES_REPEAT 	65534

void playTone(uint16_t *tones);
void playToneReverse(uint16_t *tones);
void muteTone(void);
uint8_t isplayingTone(void);

#endif