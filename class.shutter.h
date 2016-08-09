/*
 * class.shutter.h
 * Camera shutter class header file
 *
 * Project: AstroTool
 * Created on: 07.08.2016
 * Author: SergSXM (sergsxm@embedded.by)
 */

#ifndef CLASS_SHUTTER_H_
#define CLASS_SHUTTER_H_

#define	SHUTTER_STATUS_RUN	2
#define	SHUTTER_STATUS_PAUSE	1
#define	SHUTTER_STATUS_STOP	0

#include <stdint.h>
#include <avr/io.h>
#include "class.interval.h"
#include "configuration.h"

class Shutter: public IntervalListener {

	private:
		uint8_t currentTime, focusTime, shutterTime, cycleTime;
		uint8_t currentFrame, framesCount;
		uint8_t status;
		void IntervalHandler(void);

	public:

		/*
		 * Constructor
		 *
         * Interval*	interval	Interval object
		 */
		Shutter(Interval * interval);

		/*
		 * Set shutter time (time when focus is pressed)
		 *
		 * uint8_t	time	Time in sec (2..99)
		 */
		void SetShutterTime(uint8_t time);

		/*
		 * Set pause time (time when focus is released)
		 *
		 * uint8_t	time	Time in sec (2..99)
		 */
		void SetPauseTime(uint8_t time);

		/*
		 * Set frames count
		 *
		 * uint8_t	frames	Frames count (1..99)
		 */
		void SetFramesCount(uint8_t frames);

		/*
		 * Set status
		 *
		 * uint8_t	stat	Status (see SHUTTER_STATUS_ constants)
		 */
		void SetStatus(uint8_t stat);

		/*
		 * Set status RUN
		 */
		void Run(void) {SetStatus(SHUTTER_STATUS_RUN);}

		/*
		 * Set status PAUSE
		 */
		void Pause(void) {SetStatus(SHUTTER_STATUS_PAUSE);}

		/*
		 * Set status STOP
		 */
		void Stop(void) {SetStatus(SHUTTER_STATUS_STOP);}

		/*
		 * Get shutter time
		 *
		 * uint8_t	return	Time in sec
		 */
		uint8_t GetShutterTime(void) {return cycleTime - shutterTime;}

		/*
		 * Get pause time
		 *
		 * uint8_t	return	Time in sec
		 */
		uint8_t GetPauseTime(void) {return shutterTime;}

		/*
		 * Get frames count
		 *
		 * uint8_t	return	Frames count
		 */
		uint8_t GetFramesCount(void) {return framesCount;}

		/*
		 * Get current status
		 *
		 * uint8_t	return	Current status (see SHUTTER_STATUS_ constants)
		 */
		uint8_t GetStatus(void) {return status;}

		/*
		 * Get time counter value of current frame
		 *
		 * uint8_t	return	Time in sec
		 */
		uint8_t GetCurrentTime(void) {return currentTime;}

		/*
		 * Get current frame
		 *
		 * uint8_t	return	Current frame
		 */
		uint8_t GetCurrentFrame(void) {return currentFrame;}

};



#endif /* CLASS_SHUTTER_H_ */
