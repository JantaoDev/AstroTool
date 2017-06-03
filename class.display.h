/*
 * class.display.h
 * Display class header file
 *
 * Project: AstroTool
 * Created on: 24.07.2016
 * Author: Sergey Hayevoy (jantao.dev@gmail.com)
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
#include "class.interval.h"
#include "configuration.h"

class Display: public IntervalListener {

	private:
		static const uint8_t chartersData[28][14];
		volatile uint16_t lightCounter;
        uint8_t cursorCol;
        uint8_t cursorPage;
		void InitHardware(void);
		void IntervalHandler(void);
		void SendCommand(uint8_t cmd, uint8_t chip);
		void SendData(uint8_t data, uint8_t chip);
        void PutColumn(uint8_t x, uint8_t y, uint8_t column, uint8_t mode = 0);

	public:

        /*
         * Constructor
         *
         * Interval*	interval	Interval object
         */
		Display(Interval * interval);

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
		 * Put number
		 *
		 * uint8_t	x	X position (0..14)
		 * uint8_t	y	Y position (0..1)
		 * uint8_t	digits	Count of digits (charters)
		 * int16_t	value	Number value
		 * uint8_t	mode	0 - normal, 1 - inversed
		 */
		void PutNumber(uint8_t x, uint8_t y, uint8_t digits, int16_t value, uint8_t mode = 0);

		/*
		 * Put number with fixed point (1 digit after point)
		 *
		 * uint8_t	x	X position (0..14)
		 * uint8_t	y	Y position (0..1)
		 * uint8_t	digits	Count of digits (charters)
		 * int16_t	value	Number value
		 * uint8_t	mode	0 - normal, 1 - inversed
		 */
		void PutPointNumber(uint8_t x, uint8_t y, uint8_t digits, int16_t value, uint8_t mode = 0);

		/*
		 * Put hex number
		 *
		 * uint8_t	x	X position (0..14)
		 * uint8_t	y	Y position (0..1)
		 * uint8_t	digits	Count of digits (charters)
		 * int16_t	value	Number value
		 * uint8_t	mode	0 - normal, 1 - inversed
		 */
		void PutHexNumber(uint8_t x, uint8_t y, uint8_t digits, uint16_t value, uint8_t mode = 0);

		/*
		 * Turn on display LED backlight (it`s will turn off automatic after time)
		 */
		void WakeUp(void);

};



#endif /* CLASS_DISPLAY_H_ */
