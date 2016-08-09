/*
 * class.shutter.cpp
 * Camera shutter class source file
 *
 * Project: AstroTool
 * Created on: 07.08.2016
 * Author: SergSXM (sergsxm@embedded.by)
 */

#include "class.shutter.h"

void Shutter::IntervalHandler(void) {
	if ((status == SHUTTER_STATUS_STOP) || ((status == SHUTTER_STATUS_PAUSE) && (currentTime == 0))) {
		PORTD &= ~(1 << 5);
		PORTD &= ~(1 << 6);
		return;
	}
	currentTime++;
	if (currentTime >= cycleTime) {
		currentTime = 0;
		currentFrame++;
		if (currentFrame >= framesCount) {
			status = SHUTTER_STATUS_STOP;
		}
	}
	if (currentTime < focusTime) {
		PORTD &= ~(1 << 6);
	} else {
		PORTD |= (1 << 6);
	}
	if (currentTime < shutterTime) {
		PORTD &= ~(1 << 5);
	} else {
		PORTD |= (1 << 5);
	}
}

Shutter::Shutter(Interval * interval) {
	PORTD &= ~(1 << 5);
	PORTD &= ~(1 << 6);
	DDRD |= (1 << 5);
	DDRD |= (1 << 6);
	currentTime = 0;
	focusTime = 1;
	shutterTime = 2;
	cycleTime = 12;
	currentFrame = 0;
	framesCount = 20;
	status = SHUTTER_STATUS_STOP;
	interval->addListener(this, 1);
}

void Shutter::SetShutterTime(uint8_t time) {
	if (time < 1) {
		time = 1;
	}
	if (time > 99) {
		time = 99;
	}
	SetStatus(SHUTTER_STATUS_STOP);
	cycleTime = shutterTime + time;
}

void Shutter::SetPauseTime(uint8_t time) {
	if (time < 2) {
		time = 2;
	}
	if (time > 99) {
		time = 99;
	}
	SetStatus(SHUTTER_STATUS_STOP);
	cycleTime = cycleTime - shutterTime + time;
	shutterTime = time;
	focusTime = time - 1;
}

void Shutter::SetFramesCount(uint8_t frames) {
	if (frames < 1) {
		frames = 1;
	}
	if (frames > 99) {
		frames = 99;
	}
	SetStatus(SHUTTER_STATUS_STOP);
	framesCount = frames;
}

void Shutter::SetStatus(uint8_t stat) {
	status = stat;
	if (stat == SHUTTER_STATUS_STOP) {
		currentFrame = 0;
		currentTime = 0;
	}
}
