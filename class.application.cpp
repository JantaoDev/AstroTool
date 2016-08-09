/*
 * class.application.cpp
 * AstroTool application source file
 *
 * Project: AstroTool
 * Created on: 09.08.2016
 * Author: SergSXM (sergsxm@embedded.by)
 */

#include "class.application.h"

#define APP_SELECTION_DRIVE	0
#define	APP_SELECTION_SHUTTER	1
#define APP_SELECTION_DRIVE_FACTOR	2
#define APP_SELECTION_DRIVE_SPEED	3
#define	APP_SELECTION_SHUTTER_FRAMES	4
#define	APP_SELECTION_SHUTTER_TIME	5
#define	APP_SELECTION_SHUTTER_PAUSE	6


Application::Application(void): interval(), display(&interval), keyboard(&interval), battery(), shutter(&interval), drive() {
}

void Application::DrawDriveLine(uint8_t selection) {
	display.PutPointNumber(0, 0, 4, drive.GetSpeedFactor(), (selection == APP_SELECTION_DRIVE) || (selection == APP_SELECTION_DRIVE_FACTOR));
	display.PutChar(4, 0, DISPLAY_CHAR_MUL, selection == APP_SELECTION_DRIVE);
	display.PutChar(5, 0, DISPLAY_CHAR_EQUAL, selection == APP_SELECTION_DRIVE);
	display.PutHexNumber(6, 0, 4, (drive.GetSpeed() >= 0 ? drive.GetSpeed() : 0 - drive.GetSpeed()), (selection == APP_SELECTION_DRIVE) || (selection == APP_SELECTION_DRIVE_SPEED));
	display.PutPointNumber(11, 0, 3, battery.getVoltage(), 0);
	display.PutChar(14, 0, DISPLAY_CHAR_VOLT, 0);
}

void Application::DrawShutterLine(uint8_t selection) {
	switch (shutter.GetStatus()) {
		case SHUTTER_STATUS_RUN:
			display.PutChar(0, 1, DISPLAY_CHAR_PLAY, selection == APP_SELECTION_SHUTTER);
			break;
		case SHUTTER_STATUS_PAUSE:
			display.PutChar(0, 1, DISPLAY_CHAR_PAUSE, selection == APP_SELECTION_SHUTTER);
			break;
		case SHUTTER_STATUS_STOP:
			display.PutChar(0, 1, DISPLAY_CHAR_STOP, selection == APP_SELECTION_SHUTTER);
			break;
	}
	display.PutChar(1, 1, DISPLAY_CHAR_SPACE, selection == APP_SELECTION_SHUTTER);
	display.PutNumber(2, 1, 2, shutter.GetCurrentFrame(), selection == APP_SELECTION_SHUTTER);
	display.PutChar(4, 1, DISPLAY_CHAR_DIV, selection == APP_SELECTION_SHUTTER);
	display.PutNumber(5, 1, 2, shutter.GetFramesCount(), (selection == APP_SELECTION_SHUTTER) || (selection == APP_SELECTION_SHUTTER_FRAMES));
	display.PutChar(7, 1, DISPLAY_CHAR_MUL, selection == APP_SELECTION_SHUTTER);
	display.PutNumber(8, 1, 2, shutter.GetShutterTime(), (selection == APP_SELECTION_SHUTTER) || (selection == APP_SELECTION_SHUTTER_TIME));
	display.PutChar(10, 1, DISPLAY_CHAR_SEC, selection == APP_SELECTION_SHUTTER);
	display.PutChar(11, 1, DISPLAY_CHAR_PLUS, selection == APP_SELECTION_SHUTTER);
	display.PutNumber(12, 1, 2, shutter.GetPauseTime(), (selection == APP_SELECTION_SHUTTER) || (selection == APP_SELECTION_SHUTTER_PAUSE));
	display.PutChar(14, 1, DISPLAY_CHAR_SEC, selection == APP_SELECTION_SHUTTER);
}

void Application::WaitForEvent(void) {
	uint16_t time = interval.getMsCounter();
	do {
		keyboard.UpdateEvent();
	} while (!keyboard.CheckAnyFlagCondition() && (interval.getMsCounter() - time < 300));
}

void Application::Run(void) {
#ifdef APPLICATION_DEBUG
	Test();
#endif
	MainMenu();
}

#ifdef APPLICATION_DEBUG
void Application::Test(void) {
	uint8_t i;
	for (i = 0; i < 30; i++) {
		display.PutChar(i % 15, i / 15, i % 28, i / 10);
	}
	uint8_t pos = 0, j = 0;
	while (1) {
	  	i = keyboard.UpdateEvent();
	   	if (i & 0xf0) {
	   		display.PutChar(pos % 15, pos / 15, (i >> 4) & 0x0F);
	   		pos++;
	   		if (pos >= 30) {
	   			pos = 0;
	   		}
	   		display.PutChar(pos % 15, pos / 15, i & 0x0F);
	   		pos++;
	   		if (pos >= 30) {
	   			pos = 0;
	   		}
	   		display.WakeUp();
	   	}
	   	if (keyboard.CheckCondition(KEYBOARD_LONG_FLAG, 3)) {
	   		j++;
	   		if (j > 3) {
	   			break;
	   		}
	   	}
	}
	display.ClearScreen();
}
#endif

void Application::MainMenu(void) {
	uint8_t selection = APP_SELECTION_DRIVE;
	while (1) {
		DrawDriveLine(selection);
		DrawShutterLine(selection);

		WaitForEvent();

		if (!keyboard.CheckEmptyCondition()) {
			display.WakeUp();
		}
		if (keyboard.CheckCondition(KEYBOARD_SHORT_FLAG, 3)) {
			switch (selection) {
				case APP_SELECTION_DRIVE:
					selection = APP_SELECTION_SHUTTER;
					break;
				case APP_SELECTION_SHUTTER:
					selection = APP_SELECTION_DRIVE;
					break;

				case APP_SELECTION_DRIVE_FACTOR:
					selection = APP_SELECTION_DRIVE_SPEED;
					break;
				case APP_SELECTION_DRIVE_SPEED:
					selection = APP_SELECTION_DRIVE_FACTOR;
					break;

				case APP_SELECTION_SHUTTER_FRAMES:
					selection = APP_SELECTION_SHUTTER_TIME;
					break;
				case APP_SELECTION_SHUTTER_TIME:
					selection = APP_SELECTION_SHUTTER_PAUSE;
					break;
				case APP_SELECTION_SHUTTER_PAUSE:
					selection = APP_SELECTION_SHUTTER_FRAMES;
					break;
			}
		} else if (selection == APP_SELECTION_DRIVE) {
			if (keyboard.CheckCondition(KEYBOARD_DOWN_FLAG, 1)) {
				drive.Backward();
			}
			if (keyboard.CheckCondition(KEYBOARD_DOWN_FLAG, 2)) {
				drive.Forward();
			}
			if (keyboard.CheckCondition(KEYBOARD_UP_FLAG, 1) || keyboard.CheckCondition(KEYBOARD_UP_FLAG, 2)) {
				drive.Normal();
			}
			if (keyboard.CheckCondition(KEYBOARD_LONG_FLAG, 3)) {
				selection = APP_SELECTION_DRIVE_FACTOR;
			}
		} else if (selection == APP_SELECTION_SHUTTER) {
			if (keyboard.CheckCondition(KEYBOARD_SHORT_FLAG, 1)) {
				switch (shutter.GetStatus()) {
					case SHUTTER_STATUS_RUN:
						shutter.Pause();
						break;
					case SHUTTER_STATUS_PAUSE:
						shutter.Stop();
						break;
				}
			}
			if (keyboard.CheckCondition(KEYBOARD_SHORT_FLAG, 2)) {
				switch (shutter.GetStatus()) {
					case SHUTTER_STATUS_STOP:
						shutter.Pause();
						break;
					case SHUTTER_STATUS_PAUSE:
						shutter.Run();
						break;
				}
			}
			if (keyboard.CheckCondition(KEYBOARD_LONG_FLAG, 3)) {
				shutter.Stop();
				selection = APP_SELECTION_SHUTTER_FRAMES;
			}
		} else if (selection == APP_SELECTION_DRIVE_FACTOR) {
			if (keyboard.CheckCondition(KEYBOARD_SHORT_FLAG, 1)) {
				drive.SetSpeedFactor(drive.GetSpeedFactor() - 1);
			}
			if (keyboard.CheckCondition(KEYBOARD_SHORT_FLAG, 2)) {
				drive.SetSpeedFactor(drive.GetSpeedFactor() + 1);
			}
			if (keyboard.CheckCondition(KEYBOARD_LONG_FLAG, 3)) {
				selection = APP_SELECTION_DRIVE;
			}
		} else if (selection == APP_SELECTION_DRIVE_SPEED) {
			if (keyboard.CheckCondition(KEYBOARD_SHORT_FLAG, 1)) {
				drive.SetSpeed(drive.GetSpeed() - 1);
			}
			if (keyboard.CheckCondition(KEYBOARD_SHORT_FLAG, 2)) {
				drive.SetSpeed(drive.GetSpeed() + 1);
			}
			if (keyboard.CheckCondition(KEYBOARD_LONG_FLAG, 3)) {
				selection = APP_SELECTION_DRIVE;
			}
		} else if (selection == APP_SELECTION_SHUTTER_FRAMES) {
			if (keyboard.CheckCondition(KEYBOARD_SHORT_FLAG, 1)) {
				shutter.SetFramesCount(shutter.GetFramesCount() - 1);
			}
			if (keyboard.CheckCondition(KEYBOARD_SHORT_FLAG, 2)) {
				shutter.SetFramesCount(shutter.GetFramesCount() + 1);
			}
			if (keyboard.CheckCondition(KEYBOARD_LONG_FLAG, 3)) {
				selection = APP_SELECTION_SHUTTER;
			}
		} else if (selection == APP_SELECTION_SHUTTER_TIME) {
			if (keyboard.CheckCondition(KEYBOARD_SHORT_FLAG, 1)) {
				shutter.SetShutterTime(shutter.GetShutterTime() - 1);
			}
			if (keyboard.CheckCondition(KEYBOARD_SHORT_FLAG, 2)) {
				shutter.SetShutterTime(shutter.GetShutterTime() + 1);
			}
			if (keyboard.CheckCondition(KEYBOARD_LONG_FLAG, 3)) {
				selection = APP_SELECTION_SHUTTER;
			}
		} else if (selection == APP_SELECTION_SHUTTER_PAUSE) {
			if (keyboard.CheckCondition(KEYBOARD_SHORT_FLAG, 1)) {
				shutter.SetPauseTime(shutter.GetPauseTime() - 1);
			}
			if (keyboard.CheckCondition(KEYBOARD_SHORT_FLAG, 2)) {
				shutter.SetPauseTime(shutter.GetPauseTime() + 1);
			}
			if (keyboard.CheckCondition(KEYBOARD_LONG_FLAG, 3)) {
				selection = APP_SELECTION_SHUTTER;
			}
		}
	}
}

