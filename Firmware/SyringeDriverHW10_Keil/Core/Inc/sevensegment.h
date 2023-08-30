#ifndef __SEVENSEGMENT_H__
#define __SEVENSEGMENT_H__
#define CA_SEG

#include "stm32f1xx_hal.h"
#include "tim.h"

#define SEGMENT_TIMER				htim4
#define SEGMENT_INSTANCE		TIM4
#define SEGMENT_CLK					1000 //hz

#define BLINKON_DELAY				1000	//ms
#define BLINKOFF_DELAY				500	//ms
void init_segs(void);
void print_segs(char *str,uint8_t blink);
void blink_segs(uint8_t blink);
void clear_segs();

#endif