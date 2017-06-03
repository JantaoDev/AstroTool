/*
 * class.battery.cpp
 * Interval class source file
 *
 * Project: AstroTool
 * Created on: 02.08.2016
 * Author: Sergey Hayevoy (jantao.dev@gmail.com)
 */

#include "class.battery.h"



Battery::Battery(void) {
	ADMUX = 0xC4;
	ADCSRA = 0x87;
	ADCSRA |= (1 << 6);
	value = 0;
}

uint8_t Battery::getVoltage(void) {
	if ((ADCSRA & (1 << 6)) == 0) {
		uint32_t result = ADCW;
		result = result * ((uint32_t)(25.6 * BATTERY_DEVIDER)) / 1024;
		value = (result & 0xFF);
		ADCSRA |= (1 << 6) | (1 << 7);
	}
	return value;
}
