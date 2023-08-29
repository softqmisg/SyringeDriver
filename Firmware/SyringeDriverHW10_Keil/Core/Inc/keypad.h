/**
 * @file      keypad.h
 * @author    Atakan S.
 * @date      01/01/2018
 * @version   1.0
 * @brief     "PushME" Event based keypad reader module with debouncing.
 *
 * @copyright Copyright (c) 2018 Atakan SARIOGLU ~ www.atakansarioglu.com
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 */

#ifndef _H_KEYPAD_H
#define _H_KEYPAD_H

#include "main.h"
//-- Settings.
#define KEY_DEBOUNCE_TIME								5UL
#define KEY_LONGPRESS_TIME							1000UL
#define KEY_LONGPRESS_REPEAT_TIME				0 //1000UL
#define KEY_LONGPRESS_BOOST_TIME				KEY_LONGPRESS_TIME//50UL
#define KEY_LONGPRESS_BOOST_THRESHOLD		8

//-- Definitions (DONT TOUCH)
#define KEY00							0x0001
#define KEY01							0x0002
#define KEY02							0x0004
#define KEY03							0x0008
#define KEY04							0x0010
#define KEY05							0x0020
#define KEY06							0x0040
#define KEY07							0x0080
#define KEY08							0x0100
#define KEY09							0x0200
#define KEY10							0x0400
#define KEY11							0x0800
#define KEY12							0x1000
#define KEY13							0x2000
#define KEY14							0x4000
#define KEYLONG						0x8000

//----enum key state

typedef enum {KEYPRESS,KEYDOWN,KEYRELEASE} tKeyState;

//----user Key Definition

#define KeySS						KEY00
#define KEY00_port			KeySS_GPIO_Port
#define KEY00_pin				KeySS_Pin
#define KEY00_active		GPIO_PIN_RESET

#define KeyPower				KEY01
#define KEY01_port			KeyPower_GPIO_Port
#define KEY01_pin				KeyPower_Pin
#define KEY01_active		GPIO_PIN_RESET

#define KeyTime					KEY02
#define KEY02_port			KeyTime_GPIO_Port
#define KEY02_pin				KeyTime_Pin
#define KEY02_active		GPIO_PIN_RESET

#define KeyType					KEY03
#define KEY03_port			KeyType_GPIO_Port
#define KEY03_pin				KeyType_Pin
#define KEY03_active		GPIO_PIN_RESET

//#define KeyFB						KEY04
//#define KEY04_port			SwitchFB_GPIO_Port
//#define KEY04_pin				SwitchFB_Pin
//#define KEY04_active		GPIO_PIN_SET
//-- Prototypes.
void keypadInit(void);
void keypadRead(void);
uint8_t isKeyDown(uint16_t m); // Key(s) is just down.
uint8_t isKeyPress(uint16_t m); // Key(s) is pressed.
uint8_t isKeyHold(uint16_t m); // Key(s) is held down.
tKeyState KeyState(uint16_t m);
#endif
