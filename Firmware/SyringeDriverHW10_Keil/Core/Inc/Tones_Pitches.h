/**
 * @file ArduboyTonesPitches.h
 * \brief Frequency definitions for standard note pitches.
 */

// Definitions ending with "H" indicate high volume

#ifndef __TONES_PITCHES_H__
#define __TONES_PITCHES_H__
#include "stm32f1xx.h"

#define NOTE_REST 0
#define NOTE_C0  16
#define NOTE_CS0 17
#define NOTE_D0  18
#define NOTE_DS0 19
#define NOTE_E0  21
#define NOTE_F0  22
#define NOTE_FS0 23
#define NOTE_G0  25
#define NOTE_GS0 26
#define NOTE_A0  28
#define NOTE_AS0 29
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2218
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define NOTE_E8  5274
#define NOTE_F8  5588
#define NOTE_FS8 5920
#define NOTE_G8  6272
#define NOTE_GS8 6645
#define NOTE_A8  7040
#define NOTE_AS8 7459
#define NOTE_B8  7902
#define NOTE_C9  8372
#define NOTE_CS9 8870
#define NOTE_D9  9397
#define NOTE_DS9 9956
#define NOTE_E9  10548
#define NOTE_F9  11175
#define NOTE_FS9 11840
#define NOTE_G9  12544
#define NOTE_GS9 13290
#define NOTE_A9  14080
#define NOTE_AS9 14917
#define NOTE_B9  15804

#define NOTE_C0H  (NOTE_C0 + TONE_HIGH_VOLUME)
#define NOTE_CS0H (NOTE_CS0 + TONE_HIGH_VOLUME)
#define NOTE_D0H  (NOTE_D08 + TONE_HIGH_VOLUME)
#define NOTE_DS0H (NOTE_DS0 + TONE_HIGH_VOLUME)
#define NOTE_E0H  (NOTE_E0 + TONE_HIGH_VOLUME)
#define NOTE_F0H  (NOTE_F0 + TONE_HIGH_VOLUME)
#define NOTE_FS0H (NOTE_FS0 + TONE_HIGH_VOLUME)
#define NOTE_G0H  (NOTE_G0 + TONE_HIGH_VOLUME)
#define NOTE_GS0H (NOTE_GS0 + TONE_HIGH_VOLUME)
#define NOTE_A0H  (NOTE_A0 + TONE_HIGH_VOLUME)
#define NOTE_AS0H (NOTE_AS0 + TONE_HIGH_VOLUME)
#define NOTE_B0H  (NOTE_B0 + TONE_HIGH_VOLUME)
#define NOTE_C1H  (NOTE_C1 + TONE_HIGH_VOLUME)
#define NOTE_CS1H (NOTE_CS1 + TONE_HIGH_VOLUME)
#define NOTE_D1H  (NOTE_D1 + TONE_HIGH_VOLUME)
#define NOTE_DS1H (NOTE_DS1 + TONE_HIGH_VOLUME)
#define NOTE_E1H  (NOTE_E1 + TONE_HIGH_VOLUME)
#define NOTE_F1H  (NOTE_F1 + TONE_HIGH_VOLUME)
#define NOTE_FS1H (NOTE_FS1 + TONE_HIGH_VOLUME)
#define NOTE_G1H  (NOTE_G1 + TONE_HIGH_VOLUME)
#define NOTE_GS1H (NOTE_GS1 + TONE_HIGH_VOLUME)
#define NOTE_A1H  (NOTE_A1 + TONE_HIGH_VOLUME)
#define NOTE_AS1H (NOTE_AS1 + TONE_HIGH_VOLUME)
#define NOTE_B1H  (NOTE_B1 + TONE_HIGH_VOLUME)
#define NOTE_C2H  (NOTE_C2 + TONE_HIGH_VOLUME)
#define NOTE_CS2H (NOTE_CS2 + TONE_HIGH_VOLUME)
#define NOTE_D2H  (NOTE_D2 + TONE_HIGH_VOLUME)
#define NOTE_DS2H (NOTE_DS2 + TONE_HIGH_VOLUME)
#define NOTE_E2H  (NOTE_E2 + TONE_HIGH_VOLUME)
#define NOTE_F2H  (NOTE_F2 + TONE_HIGH_VOLUME)
#define NOTE_FS2H (NOTE_FS2 + TONE_HIGH_VOLUME)
#define NOTE_G2H  (NOTE_G2 + TONE_HIGH_VOLUME)
#define NOTE_GS2H (NOTE_GS2 + TONE_HIGH_VOLUME)
#define NOTE_A2H  (NOTE_A2 + TONE_HIGH_VOLUME)
#define NOTE_AS2H (NOTE_AS2 + TONE_HIGH_VOLUME)
#define NOTE_B2H  (NOTE_B2 + TONE_HIGH_VOLUME)
#define NOTE_C3H  (NOTE_C3 + TONE_HIGH_VOLUME)
#define NOTE_CS3H (NOTE_CS3 + TONE_HIGH_VOLUME)
#define NOTE_D3H  (NOTE_D3 + TONE_HIGH_VOLUME)
#define NOTE_DS3H (NOTE_DS3 + TONE_HIGH_VOLUME)
#define NOTE_E3H  (NOTE_E3 + TONE_HIGH_VOLUME)
#define NOTE_F3H  (NOTE_F3 + TONE_HIGH_VOLUME)
#define NOTE_FS3H (NOTE_F3 + TONE_HIGH_VOLUME)
#define NOTE_G3H  (NOTE_G3 + TONE_HIGH_VOLUME)
#define NOTE_GS3H (NOTE_GS3 + TONE_HIGH_VOLUME)
#define NOTE_A3H  (NOTE_A3 + TONE_HIGH_VOLUME)
#define NOTE_AS3H (NOTE_AS3 + TONE_HIGH_VOLUME)
#define NOTE_B3H  (NOTE_B3 + TONE_HIGH_VOLUME)
#define NOTE_C4H  (NOTE_C4 + TONE_HIGH_VOLUME)
#define NOTE_CS4H (NOTE_CS4 + TONE_HIGH_VOLUME)
#define NOTE_D4H  (NOTE_D4 + TONE_HIGH_VOLUME)
#define NOTE_DS4H (NOTE_DS4 + TONE_HIGH_VOLUME)
#define NOTE_E4H  (NOTE_E4 + TONE_HIGH_VOLUME)
#define NOTE_F4H  (NOTE_F4 + TONE_HIGH_VOLUME)
#define NOTE_FS4H (NOTE_FS4 + TONE_HIGH_VOLUME)
#define NOTE_G4H  (NOTE_G4 + TONE_HIGH_VOLUME)
#define NOTE_GS4H (NOTE_GS4 + TONE_HIGH_VOLUME)
#define NOTE_A4H  (NOTE_A4 + TONE_HIGH_VOLUME)
#define NOTE_AS4H (NOTE_AS4 + TONE_HIGH_VOLUME)
#define NOTE_B4H  (NOTE_B4 + TONE_HIGH_VOLUME)
#define NOTE_C5H  (NOTE_C5 + TONE_HIGH_VOLUME)
#define NOTE_CS5H (NOTE_CS5 + TONE_HIGH_VOLUME)
#define NOTE_D5H  (NOTE_D5 + TONE_HIGH_VOLUME)
#define NOTE_DS5H (NOTE_DS5 + TONE_HIGH_VOLUME)
#define NOTE_E5H  (NOTE_E5 + TONE_HIGH_VOLUME)
#define NOTE_F5H  (NOTE_F5 + TONE_HIGH_VOLUME)
#define NOTE_FS5H (NOTE_FS5 + TONE_HIGH_VOLUME)
#define NOTE_G5H  (NOTE_G5 + TONE_HIGH_VOLUME)
#define NOTE_GS5H (NOTE_GS5 + TONE_HIGH_VOLUME)
#define NOTE_A5H  (NOTE_A5 + TONE_HIGH_VOLUME)
#define NOTE_AS5H (NOTE_AS5 + TONE_HIGH_VOLUME)
#define NOTE_B5H  (NOTE_B5 + TONE_HIGH_VOLUME)
#define NOTE_C6H  (NOTE_C6 + TONE_HIGH_VOLUME)
#define NOTE_CS6H (NOTE_CS6 + TONE_HIGH_VOLUME)
#define NOTE_D6H  (NOTE_D6 + TONE_HIGH_VOLUME)
#define NOTE_DS6H (NOTE_DS6 + TONE_HIGH_VOLUME)
#define NOTE_E6H  (NOTE_E6 + TONE_HIGH_VOLUME)
#define NOTE_F6H  (NOTE_F6 + TONE_HIGH_VOLUME)
#define NOTE_FS6H (NOTE_FS6 + TONE_HIGH_VOLUME)
#define NOTE_G6H  (NOTE_G6 + TONE_HIGH_VOLUME)
#define NOTE_GS6H (NOTE_GS6 + TONE_HIGH_VOLUME)
#define NOTE_A6H  (NOTE_A6 + TONE_HIGH_VOLUME)
#define NOTE_AS6H (NOTE_AS6 + TONE_HIGH_VOLUME)
#define NOTE_B6H  (NOTE_B6 + TONE_HIGH_VOLUME)
#define NOTE_C7H  (NOTE_C7 + TONE_HIGH_VOLUME)
#define NOTE_CS7H (NOTE_CS7 + TONE_HIGH_VOLUME)
#define NOTE_D7H  (NOTE_D7 + TONE_HIGH_VOLUME)
#define NOTE_DS7H (NOTE_DS7 + TONE_HIGH_VOLUME)
#define NOTE_E7H  (NOTE_E7 + TONE_HIGH_VOLUME)
#define NOTE_F7H  (NOTE_F7 + TONE_HIGH_VOLUME)
#define NOTE_FS7H (NOTE_FS7 + TONE_HIGH_VOLUME)
#define NOTE_G7H  (NOTE_G7 + TONE_HIGH_VOLUME)
#define NOTE_GS7H (NOTE_GS7 + TONE_HIGH_VOLUME)
#define NOTE_A7H  (NOTE_A7 + TONE_HIGH_VOLUME)
#define NOTE_AS7H (NOTE_AS7 + TONE_HIGH_VOLUME)
#define NOTE_B7H  (NOTE_B7 + TONE_HIGH_VOLUME)
#define NOTE_C8H  (NOTE_C8 + TONE_HIGH_VOLUME)
#define NOTE_CS8H (NOTE_CS8 + TONE_HIGH_VOLUME)
#define NOTE_D8H  (NOTE_D8 + TONE_HIGH_VOLUME)
#define NOTE_DS8H (NOTE_DS8 + TONE_HIGH_VOLUME)
#define NOTE_E8H  (NOTE_E8 + TONE_HIGH_VOLUME)
#define NOTE_F8H  (NOTE_F8 + TONE_HIGH_VOLUME)
#define NOTE_FS8H (NOTE_FS8 + TONE_HIGH_VOLUME)
#define NOTE_G8H  (NOTE_G8 + TONE_HIGH_VOLUME)
#define NOTE_GS8H (NOTE_GS8 + TONE_HIGH_VOLUME)
#define NOTE_A8H  (NOTE_A8 + TONE_HIGH_VOLUME)
#define NOTE_AS8H (NOTE_AS8 + TONE_HIGH_VOLUME)
#define NOTE_B8H  (NOTE_B8 + TONE_HIGH_VOLUME)
#define NOTE_C9H  (NOTE_C9 + TONE_HIGH_VOLUME)
#define NOTE_CS9H (NOTE_CS9 + TONE_HIGH_VOLUME)
#define NOTE_D9H  (NOTE_D9 + TONE_HIGH_VOLUME)
#define NOTE_DS9H (NOTE_DS9 + TONE_HIGH_VOLUME)
#define NOTE_E9H  (NOTE_E9 + TONE_HIGH_VOLUME)
#define NOTE_F9H  (NOTE_F9 + TONE_HIGH_VOLUME)
#define NOTE_FS9H (NOTE_FS9 + TONE_HIGH_VOLUME)
#define NOTE_G9H  (NOTE_G9 + TONE_HIGH_VOLUME)
#define NOTE_GS9H (NOTE_GS9 + TONE_HIGH_VOLUME)
#define NOTE_A9H  (NOTE_A9 + TONE_HIGH_VOLUME)
#define NOTE_AS9H (NOTE_AS9 + TONE_HIGH_VOLUME)
#define NOTE_B9H  (NOTE_B9 + TONE_HIGH_VOLUME)


extern uint16_t tonePowerWake[];
extern uint16_t toneKeyPress[];
extern uint16_t toneAlarm[];
extern uint16_t toneAlarmNE[];
extern uint16_t toneBeep[];
extern uint16_t toneSave[];
extern uint16_t toneEnterSetup[];
extern uint16_t toneStartRun[];
#endif