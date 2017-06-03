/*
 * class.keyboard.h
 * Keyboard class source file
 *
 * Project: AstroTool
 * Created on: 28.07.2016
 * Author: Sergey Hayevoy (jantao.dev@gmail.com)
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
		uint8_t lastEvent;

		uint8_t GetDebouncedButton(void);

	public:

        /*
         * Constructor
         *
         * Interval*	interval	Interval object
         */
		Keyboard(Interval * interval);

		/*
		 * Update event
		 *
		 * uint8_t	return	Current event
		 */
		uint8_t UpdateEvent(void);

		/*
		 * Get current event
		 *
		 * uint8_t	return	Current event
		 */
		uint8_t GetEvent(void) {return lastEvent;}

		/*
		 * Check current condition on flag and key
		 *
		 * uint8_t	flag	Checking flag
		 * uint8_t	key	Checking key
		 * uint8_t	return	Result
		 */
		uint8_t CheckCondition(uint8_t flag, uint8_t key) {return ((lastEvent & flag) && ((lastEvent & 0x0F) == key));}

		/*
		 * Check current condition is empty
		 *
		 * uint8_t	return	Result
		 */
		uint8_t CheckEmptyCondition(void) {return (lastEvent == KEYBOARD_EMPTY);}

		/*
		 * Check current condition on any flag
		 *
		 * uint8_t	return	Result
		 */
		uint8_t CheckAnyFlagCondition(void) {return (lastEvent & 0xF0);}
};


#endif /* CLASS_KEYBOARD_H_ */
