/*
 * class.keyboard.h
 * Keyboard class source file
 *
 * Project: AstroTool
 * Created on: 28.07.2016
 * Author: SergSXM (sergsxm@embedded.by)
 */

#ifndef CLASS_KEYBOARD_H_
#define CLASS_KEYBOARD_H_

#define	KEYBOARD_EMPTY	0
#define	KEYBOARD_DOWN_FLAG	0x10
#define	KEYBOARD_UP_FLAG	0x20
#define	KEYBOARD_SHORT_FLAG	0x40
#define	KEYBOARD_LONG_FLAG	0x80


#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "class.interval.h"
#include "configuration.h"

class Keyboard {

	private:
		Interval * interval;
		uint8_t bounceCounter;
		uint8_t bounceOldButton;
		uint8_t currentButton;
		uint16_t pressStartMs;
		uint8_t longPressFlag;

		uint8_t GetDebouncedButton(void);

	public:

		Keyboard(Interval * interval);
		uint8_t GetEvent(void);

};


#endif /* CLASS_KEYBOARD_H_ */
