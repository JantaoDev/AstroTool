/*
 * class.interval.h
 * Interval class header file
 *
 * Project: AstroTool
 * Created on: 28.07.2016
 * Author: Sergey Hayevoy (jantao.dev@gmail.com)
 */

#ifndef CLASS_INTERVAL_H_
#define CLASS_INTERVAL_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "configuration.h"

extern "C" void TIMER2_OVF_vect(void) __attribute__ ((signal));

class IntervalListener {
	public:
		virtual void IntervalHandler(void);
};

class Interval {

	private:
		static Interval * instance;
		IntervalListener * listeners[INTERVAL_LISTENERS_COUNT];
		uint16_t listenerCounter[INTERVAL_LISTENERS_COUNT];
		uint16_t listenerInterval[INTERVAL_LISTENERS_COUNT];
		uint16_t tickCounter;

		void InterruptHandler(void);

	public:

		/*
		 * Constructor
		 */
		Interval(void);

		/*
		 * Add interval listener to timer
		 * IntervalListener*	listener	Interval listener
		 * uint16_t	frequency	Interval frequency (Hz)
		 */
		void addListener(IntervalListener * listener, uint16_t frequency);

		/*
		 * Get milliseconds counter value
		 */
		uint16_t getMsCounter(void);

		friend void TIMER2_OVF_vect(void);

};

#endif /* CLASS_INTERVAL_H_ */
