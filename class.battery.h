/*
 * class.battery.h
 * Interval class source file
 *
 * Project: AstroTool
 * Created on: 02.08.2016
 * Author: SergSXM (sergsxm@embedded.by)
 */

#ifndef CLASS_BATTERY_H_
#define CLASS_BATTERY_H_

#include <stdint.h>
#include <avr/io.h>
#include "configuration.h"

class Battery {

	public:

		Battery(void);
		uint8_t getVoltage(void);

};

#endif /* CLASS_BATTERY_H_ */
