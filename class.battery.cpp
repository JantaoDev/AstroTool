/*
 * class.battery.cpp
 * Interval class source file
 *
 * Project: AstroTool
 * Created on: 02.08.2016
 * Author: SergSXM (sergsxm@embedded.by)
 */

#include "class.battery.h"



Battery::Battery(void) {
	ADMUX = 0xC4;
	ADCSRA = 0xA7;
}

uint8_t Battery::getVoltage(void) {
	uint32_t result = (ADCH << 8) | ADCL;
	result = result * ((uint32_t)(25.6 * BATTERY_DEVIDER)) / 1024;
	return (result & 0xFF);
}
