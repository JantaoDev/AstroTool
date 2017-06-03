/*
 * class.drive.cpp
 * Step drive class source file
 *
 * Project: AstroTool
 * Created on: 08.08.2016
 * Author: Sergey Hayevoy (jantao.dev@gmail.com)
 */

#include "class.drive.h"

//define	DRIVE_1X_SPEED	(int16_t)((86400.0 / DRIVE_REDUCTION) * (F_CPU / 64))
#define	DRIVE_1X_SPEED	(int32_t)((86400.0 * F_CPU) / (64 * DRIVE_REDUCTION))
#define DRIVE_MAX_SPEED	(int16_t)(1.0 * F_CPU / (64 * DRIVE_MAXSPEED))

Drive * Drive::instance;

const uint8_t Drive::stepValues[4] = {0x01, 0x02, 0x04, 0x08};

void Drive::InterruptHandler(void) {
	TCNT1H = (timerValue >> 8) & 0xFF;
	TCNT1L = timerValue & 0xFF;
	if (mode == DRIVE_MODE_STOP) {
		return;
	}
	if (direction) {
		step++;
	} else {
		step--;
	}
	step &= 0x03;
	PORTD = (PORTD & ~0x0F) | stepValues[step];
}

Drive::Drive(void) {
	instance = this;
	step = 0;
	SetSpeedFactor(10);
	DDRD |= 0x0F;
	PORTD &= ~0x0F;
	TCCR1A = 0x00;
	TCCR1B = 0x03;
	TCNT1H = (timerValue >> 8) & 0xFF;
	TCNT1L = timerValue & 0xFF;
	TIMSK |= 1 << 2;
	sei();
}

void Drive::SetSpeedFactor(int8_t factor) {
	if (factor == 0) {
		Stop();
		return;
	}
	int32_t spd = DRIVE_1X_SPEED * 10 / factor;
	if (spd > 0x7FFFL) {
		spd = 0x7FFFL;
	}
	if (spd < -0x8000L) {
		spd = -0x8000L;
	}
	SetSpeed(spd);
}

void Drive::SetSpeed(int16_t speed) {
	currentSpeed = speed;
	if (speed < 0) {
		direction = !DRIVE_DIRECTION;
		speed = 0 - speed;
	} else {
		direction = DRIVE_DIRECTION;
	}
	if (speed < DRIVE_MAX_SPEED) {
		speed = DRIVE_MAX_SPEED;
	}
	timerValue = (0xFFFF - speed) + 1;
	mode = DRIVE_MODE_NORMAL;
}

void Drive::SetMode(uint8_t md) {
	if (md == DRIVE_MODE_STOP) {
		mode = DRIVE_MODE_STOP;
	} else if (md == DRIVE_MODE_NORMAL) {
		SetSpeed(currentSpeed);
	} else if (md == DRIVE_MODE_FORWARD) {
		direction = DRIVE_DIRECTION;
		timerValue = (0xFFFF - DRIVE_MAX_SPEED) + 1;
		mode = DRIVE_MODE_FORWARD;
	} else if (md == DRIVE_MODE_BACKWARD) {
		direction = !DRIVE_DIRECTION;
		timerValue = (0xFFFF - DRIVE_MAX_SPEED) + 1;
		mode = DRIVE_MODE_BACKWARD;
	}
}

int8_t Drive::GetSpeedFactor(void) {
	int32_t spd = GetSpeed();
	spd = DRIVE_1X_SPEED * 10 / spd;
	if (spd > 127) {
		spd = 127;
	}
	if (spd < -128) {
		spd = -128;
	}
	return spd;
}

int16_t Drive::GetSpeed(void) {
	if (mode == DRIVE_MODE_NORMAL) {
		return currentSpeed;
	}
	if (mode == DRIVE_MODE_FORWARD) {
		return DRIVE_MAX_SPEED;
	}
	if (mode == DRIVE_MODE_BACKWARD) {
		return (0 - DRIVE_MAX_SPEED);
	}
	return 0;
}

ISR(TIMER1_OVF_vect) {
	Drive::instance->InterruptHandler();
}
