#ifndef __USER_TIME_H__
#define __USER_TIME_H__
#include "stm32f1xx_hal.h"

typedef uint32_t tTime;															///< Keeps time.
typedef struct{
    tTime due;																	///< Timestamp of the next timeout.
    tTime period;																///< The period for reloading the timeout.
}tTimeout;

void PunctualTimeoutSet(tTimeout *to, tTime ms);
uint8_t PunctualTimeoutCheck(tTimeout *to);
#endif