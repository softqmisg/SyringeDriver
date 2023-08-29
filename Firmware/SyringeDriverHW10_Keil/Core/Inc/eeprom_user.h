#ifndef _USER_EEPROM_H
#define _USER_EEPROM_H
#include "main.h"

#define MAX_RENT	10
////////////////////////////////////////////////////////////////////////////////////////
#define BASEADDRESS	0x0000
/////////////////////////////////////////////////////////////////////////////
#define ON_HR_TM_ADD			0//BASEADDRESS+0   // 0:9 //1byte
#define	ON_MIN_TM_ADD			1//ON_HR_TM_ADD+1   //0-59 1byte
#define ON_SEC_TM_ADD			2//ON_MIN_TM_ADD+1  //0-59 1byte
#define BACKLIGHT_PWM_ADD 3//ON_SEC_TM_ADD+1  //0:99 1byte  
#define TEMPH_ADD		4//BACKLIGHT_PWM_ADD+1			
#define TEMPL_ADD		6//TEMPH_ADD+2
#define HUMH_ADD		8//TEMPL_ADD+2
#define HUML_ADD		10//HUMH_ADD+2
#define SENSORTYPE_ADD	12//HUML_ADD+2
#define RENT_TIMESTRUCT_BASE_ADD	13//SENSORTYPE_ADD+1  //0:99 1byte  

#define ON_HR_TM_DEFAULT			1   // 0:9 //1byte
#define	ON_MIN_TM_DEFAULT		50   //0-59 1byte
#define ON_SEC_TM_DEFAULT		40  //0-59 1byte
#define BACKLIGHT_PWM_DEFAULT 80  //0:99 1byte  
#define TEMPH_DEFAULT		600		
#define TEMPL_DEFAULT		580
#define HUMH_DEFAULT		300
#define HUML_DEFAULT		250
#define SENSORTYPE_DEFAULT	0

#define TEMP_MAX	800
#define TEMP_MIN	0

#define HUM_MAX		950
#define HUM_MIN		0

extern struct tm tm_Targetperiod_Value;
extern uint8_t	BACKLIGHT_PWM_Value;
extern int16_t TEMPH_Value;
extern int16_t TEMPL_Value;
extern int16_t HUMH_Value;
extern int16_t HUML_Value;
extern uint8_t SENSORTYPE_Value;
extern struct tm tm_RentTimes[MAX_RENT];
extern uint8_t RentTimes_valid[MAX_RENT];

void eeprom_read_values(void);
void eeprom_write_defaults(void);
void eeprom_write_structtm(uint16_t add,struct tm r,uint8_t v,uint8_t number);

#endif
