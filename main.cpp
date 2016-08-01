/*
 * main.cpp
 * Main source file
 *
 * Project: AstroTool
 * Created on: 24.07.2016
 * Author: SergSXM (sergsxm@embedded.by)
 */

#include "class.interval.h"
#include "class.display.h"
#include "class.keyboard.h"




int main(void) {
	Interval interval;
    Display display(&interval);
    Keyboard keyboard(&interval);
	uint8_t event, pos = 0;
    while (1) {
    	event = keyboard.GetEvent();
    	if (event & 0xf0) {
    		display.PutChar(pos % 15, pos / 15, (event >> 4) & 0x0F);
    		pos++;
    		if (pos >= 30) {
    			pos = 0;
    		}
    		display.PutChar(pos % 15, pos / 15, event & 0x0F);
    		pos++;
    		if (pos >= 30) {
    			pos = 0;
    		}
    	}
    }









    display.PutChar(0, 0, 0);
    display.PutChar(1, 0, 1);
    display.PutChar(2, 0, 2);
    display.PutChar(3, 0, 3);
    display.PutChar(4, 0, 4);
    display.PutChar(5, 0, 5);
    display.PutChar(6, 0, 6, 1);
    display.PutChar(7, 0, 7);
    display.PutChar(8, 0, 8);
    display.PutChar(9, 0, 9);
    display.PutChar(10, 0, 10);
    display.PutChar(11, 0, 11, 1);
    display.PutChar(12, 0, 12);
    display.PutChar(13, 0, 13);
    display.PutChar(14, 0, 14);

    display.PutChar(0, 1, 16, 1);
    display.PutChar(1, 1, 17, 1);
    display.PutChar(2, 1, 18, 1);
    display.PutChar(3, 1, 19, 1);
    display.PutChar(4, 1, 20, 1);
    display.PutChar(5, 1, 21, 1);
    display.PutChar(6, 1, 22, 1);
    display.PutChar(7, 1, 23);
    display.PutChar(8, 1, 24);
    display.PutChar(9, 1, 25);
    display.PutChar(10, 1, 26);
    display.PutChar(11, 1, 27);
    display.PutChar(12, 1, 0);
    display.PutChar(13, 1, 1);
    display.PutChar(14, 1, 15, 1);

    while (1) {
    }
}
