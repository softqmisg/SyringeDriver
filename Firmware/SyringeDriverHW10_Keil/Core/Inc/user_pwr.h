#ifndef __USER_PWR_H__
#define __USER_PWR_H__
#include "stm32f1xx_hal.h"

extern __IO uint8_t awu_flag;

__STATIC_INLINE void SYSCLKConfig_FromSTOP(void);
void gotoStopMode(void);
void gotoStandbyMode(uint8_t mute);

#endif