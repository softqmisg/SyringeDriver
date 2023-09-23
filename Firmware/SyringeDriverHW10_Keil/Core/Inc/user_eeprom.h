#ifndef _USER_EEPROM_H
#define _USER_EEPROM_H
#include "main.h"
#include "eeprom.h"
////////////////////////////////////////////////////////////////////////////////////////
#define BASEADDRESS	0x0000
/////////////////////////////////////////////////////////////////////////////
#define EE_ADD_FIRSTTIME	0
#define EE_ADD_PWM				2
#define	EE_ADD_VHALLF			4
#define	EE_ADD_VHALLE			6
#define EE_ADD_CURMOT			8
#define EE_ADD_VOLBAT			10
#define EE_ADD_CURBAT			12
#define EE_ADD_MSTATE			14
#define EE_ADD_TIMEINDEX	16
#define EE_ADD_TYPEINDEX	18


#define DEFAULT_PWM				25   //%
#define	DEFAULT_VHALLF		340  //mv 
#define DEFAULT_VHALLE		370 //mv 
#define DEFAULT_CURMOT		100   //ma
#define DEFAULT_VOLBAT		1942 //9V to digital=(9v*1M/5.75M)*(4096/3.3V)
#define DEFAULT_CURBT			50
#define DEFAULT_MSTATE		UpState
#define DEFAULT_TIMEINDEX	0
#define DEFAULT_TYPEINDEX	0

#define MAX_PWM		99
#define MIN_PWM		0

extern uint16_t EEValue_PWM;
extern uint16_t EEValue_VHALLF;
extern uint16_t EEValue_VHALLE;
extern uint16_t EEValue_CURMOT;
extern uint16_t EEValue_VOLBAT;
extern uint16_t EEValue_CURBAT;
extern mState_t EEValue_MSTATE;
extern uint16_t	EEValue_TIMEINDEX;
extern uint16_t	EEValue_TYPEINDEX;

void eepromReadValues(void);
void eepromWriteDefaults(void);

#endif
