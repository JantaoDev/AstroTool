/*
 * class.drive.h
 * Step drive class source file
 *
 * Project: AstroTool
 * Created on: 08.08.2016
 * Author: Sergey Hayevoy (jantao.dev@gmail.com)
 */

#ifndef CLASS_DRIVE_H_
#define CLASS_DRIVE_H_

#define	DRIVE_MODE_STOP	0
#define DRIVE_MODE_NORMAL	1
#define	DRIVE_MODE_FORWARD	2
#define DRIVE_MODE_BACKWARD	3

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "configuration.h"

extern "C" void TIMER1_OVF_vect(void) __attribute__ ((signal));

class Drive {

	private:
		static const uint8_t stepValues[4];
		static Drive * instance;
		uint8_t direction, step, mode;
		uint16_t timerValue;
		int16_t currentSpeed;
		void InterruptHandler(void);

	public:

		/*
		 * Constructor
		 */
		Drive(void);

		/*
		 * Set speed by factor value
		 *
		 * int8_t	factor	Factor value (* 10)
		 */
		void SetSpeedFactor(int8_t factor);

		/*
		 * Set speed directly
		 *
		 * int16_t	speed	Speed
		 */
		void SetSpeed(int16_t speed);

		/*
		 * Set drive mode
		 *
		 * uint8_t	md	Mode (see DRIVE_MODE_ constants)
		 */
		void SetMode(uint8_t md);

		/*
		 * Stop drive
		 */
		void Stop(void) {SetMode(DRIVE_MODE_STOP);}

		/*
		 * Set normal mode with saved speed
		 */
		void Normal(void) {SetMode(DRIVE_MODE_NORMAL);}

		/*
		 * Set forward mode with maximum speed
		 */
		void Forward(void) {SetMode(DRIVE_MODE_FORWARD);}

		/*
		 * Set backward mode with maximum speed
		 */
		void Backward(void) {SetMode(DRIVE_MODE_BACKWARD);}

		/*
		 * Get current speed factor
		 *
		 * int8_t	return	Speed factor
		 */
		int8_t GetSpeedFactor(void);

		/*
		 * Get current speed
		 *
		 * int16_t	return	Current speed
		 */
		int16_t GetSpeed(void);

		/*
		 * Get current mode
		 *
		 * uint8_t	return	Current mode
		 */
		uint8_t GetMode(void) {return mode;}

		friend void TIMER1_OVF_vect(void);

};




#endif /* CLASS_DRIVE_H_ */
