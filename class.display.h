/*
 * class.display.h
 * Display class header file
 *
 * Project: AstroTool
 * Created on: 24.07.2016
 * Author: SergSXM (sergsxm@embedded.by)
 */

#ifndef CLASS_DISPLAY_H_
#define CLASS_DISPLAY_H_

#define	DISPLAY_CHAR_DIGIT	0
#define	DISPLAY_CHAR_SPACE	16
#define	DISPLAY_CHAR_DOT	17
#define	DISPLAY_CHAR_EQUAL	18
#define	DISPLAY_CHAR_MUL	19
#define	DISPLAY_CHAR_VOLT	20
#define	DISPLAY_CHAR_SEC	21
#define	DISPLAY_CHAR_DIV	22
#define	DISPLAY_CHAR_PLUS	23
#define	DISPLAY_CHAR_PAUSE	24
#define	DISPLAY_CHAR_STOP	25
#define	DISPLAY_CHAR_PLAY	26
#define	DISPLAY_CHAR_MINUS	27

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "configuration.h"

extern "C" void TIMER2_OVF_vect(void) __attribute__ ((signal));

class Display {

	private:
		static Display * pDisplay;
		static const uint8_t chartersData[28][14];
		volatile uint16_t lightCounter;
        uint8_t cursorCol;
        uint8_t cursorPage;
		void Init(void);
		void InterruptHandler(void);
		void SendCommand(uint8_t cmd, uint8_t chip);
		void SendData(uint8_t data, uint8_t chip);
        void PutColumn(uint8_t x, uint8_t y, uint8_t column, uint8_t mode = 0);

	public:

        /*
         * Constructor
         */
		Display(void);

		/*
		 * Clear screen
		 */
		void ClearScreen(void);

		/*
		 * Put charter on screen
		 *
		 * uint8_t	x	X position (0..14)
		 * uint8_t	y	Y position (0..1)
		 * uint8_t	charter	Charter number (0..27)
		 * uint8_t	mode	0 - normal, 1 - inversed
		 */
		void PutChar(uint8_t x, uint8_t y, uint8_t charter, uint8_t mode = 0);

		/*
		 * Turn on display LED backlight (it`s will turn off automatic after time)
		 */
		void WakeUp(void);

		friend void TIMER2_OVF_vect(void);

};



#endif /* CLASS_DISPLAY_H_ */
