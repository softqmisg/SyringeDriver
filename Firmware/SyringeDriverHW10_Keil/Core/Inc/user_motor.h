#ifndef __USER_MOTOR_H__
#define __USER_MOTOR_H__
#include "stm32f1xx_hal.h"
#include "tim.h"
#define motorTIMER		htim1
#define motorCHANNEL1	TIM_CHANNEL_1
#define motorCHANNEL2	TIM_CHANNEL_2
#define motorFreqPWM	5000 //Hz
#define MAX_MotorErrNum		2

extern __IO uint8_t motorErrNum;
void motorStop(void);
void motorStart(double percent);
uint8_t motorIsStart(void);
double motorCalcDuty(void);

#endif