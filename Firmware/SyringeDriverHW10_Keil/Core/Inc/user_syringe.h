#ifndef __USER_SYRINGE_H__
#define __USER_SYRINGE_H__
#include "stm32f1xx_hal.h"
//#define RUNOFFLED_TICK	1 //s
//#define STOPWAKEUP_TICK	2 //s

#define ERR_NONE	0
#define ERR_NE		1
#define ERR_E5		2
#define ERR_DU		3

#define ULTRALOWVOLT_TH		6850 //mv noload of bat=6850+150=7000
#define LOWBATVOLT_TH			7150 //ms noload of bat=7150+150=7300

#define MAX_TIMEINDEX	10
#define MAX_TYPEINDEX	2

extern uint16_t syringeTypes[];
extern uint16_t syringeTimes[];
extern uint8_t syringWakeups[][2];
extern uint8_t systemError;
extern char *systemErrorMsg[];
extern uint8_t delayAlarwakups[];
#endif