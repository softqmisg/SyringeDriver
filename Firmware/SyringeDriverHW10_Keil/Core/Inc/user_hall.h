#ifndef __USER_HALL_H__
#define __USER_HALL_H__
#include "stm32f1xx_hal.h"

#define HALLEND_PERCENT	20 //% percent to Front of HALL sensor

void hallON(void);
void hallOFF(void);
uint8_t hallIsEnd(void);

#endif