/*
 * configuration.h
 * Configuration constants
 *
 * Project: AstroTool
 * Created on: 24.07.2016
 * Author: Sergey Hayevoy (jantao.dev@gmail.com)
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

// Max count of interval listeners
#define INTERVAL_LISTENERS_COUNT	3
// Interval timer frequency (Hz)
#define	INTERVAL_FREQ	4000UL

// Keyboard bounce filter value
#define	KEYBOARD_BOUNCE_FILTER	32
// Keyboard long pressed time (ms)
#define	KEYBOARD_LONG_TIME	3000

// Display oscilator frequency (Hz)
#define	DISPLAY_OSC_FREQ	2000UL
// Display backlight time (ms)
#define DISPLAY_LIGHT_TIME	10000UL

// Battery voltage devider value
#define BATTERY_DEVIDER	5.7

// Drive default direction
#define	DRIVE_DIRECTION	1
// Drive mechanic reduction (steps per full cycle)
#define DRIVE_REDUCTION	(12.5 * 2048 * 100)
// Drive max speed (steps per second)
#define DRIVE_MAXSPEED	200

// Enabled application debug tests
//#define	APPLICATION_DEBUG


#endif /* CONFIGURATION_H_ */
