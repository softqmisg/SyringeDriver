#ifndef __USER_PWR_H__
#define __USER_PWR_H__
#include "main.h"
#include "user_keypad.h"
__STATIC_INLINE void SYSCLKConfig_FromSTOP(void);
void gotoStopMode(void);
void gotoStandbyMode(uint8_t mute);

#endif