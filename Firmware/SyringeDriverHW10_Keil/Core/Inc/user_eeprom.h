#ifndef _USER_EEPROM_H
#define _USER_EEPROM_H
#include "stm32f1xx_hal.h"
#include "eeprom.h"
////////////////////////////////////////////////////////////////////////////////////////
#define BASEADDRESS	0x0000
/////////////////////////////////////////////////////////////////////////////
#define EE_ADD_PWM		0
#define	EE_ADD_VHALLF	2
#define	EE_ADD_VHALLE	4
#define EE_ADD_CURMOT	6
#define EE_ADD_VOLBAT	8
#define EE_ADD_CURBAT	10


#define DEFAULT_PWM			50   //%
#define	DEFAULT_VHALLF	340  //mv 
#define DEFAULT_VHALLE	370 //mv 
#define DEFAULT_CURMOT 	100   //ma
#define DEFAULT_VOLBAT	7000 //mv
#define DEFAULT_CURBT		50

#define MAX_PWM		100
#define MIN_PWM		0


extern uint16_t EEValue_PWM;
extern uint16_t EEValue_VHALLF;
extern uint16_t EEValue_VHALLE;
extern uint16_t EEValue_CURMOT;
extern uint16_t EEValue_VOLBAT;
extern uint16_t EEValue_CURBAT;

void eeprom_read_values(void);
void eeprom_write_defaults(void);

#endif
