/*
 * class.battery.h
 * Interval class source file
 *
 * Project: AstroTool
 * Created on: 02.08.2016
 * Author: Sergey Hayevoy (jantao.dev@gmail.com)
 */

#ifndef CLASS_BATTERY_H_
#define CLASS_BATTERY_H_

#include <stdint.h>
#include <avr/io.h>
#include "configuration.h"

class Battery {

	private:
		uint8_t value;

	public:

		Battery(void);
		uint8_t getVoltage(void);

};

#endif /* CLASS_BATTERY_H_ */
