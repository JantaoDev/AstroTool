/*
 * class.application.h
 * AstroTool application header file
 *
 * Project: AstroTool
 * Created on: 09.08.2016
 * Author: SergSXM (sergsxm@embedded.by)
 */

#ifndef CLASS_APPLICATION_H_
#define CLASS_APPLICATION_H_

#include "class.interval.h"
#include "class.battery.h"
#include "class.display.h"
#include "class.drive.h"
#include "class.keyboard.h"
#include "class.shutter.h"
#include "configuration.h"

class Application {

	private:
		Interval interval;
		Display display;
		Keyboard keyboard;
		Battery battery;
		Shutter shutter;
		Drive drive;

		void DrawDriveLine(uint8_t selection);
		void DrawShutterLine(uint8_t selection);
		void WaitForEvent(void);

		void MainMenu(void);
	#ifdef APPLICATION_DEBUG
		void Test(void);
	#endif

	public:
		/*
		 * Constructor
		 */
		Application(void);

		/*
		 * Run application
		 */
		void Run(void);

};

#endif /* CLASS_APPLICATION_H_ */
