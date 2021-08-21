#include "WhiteOut.h"

void WhiteOut::init() {
	
	startTime = nowMillis();
	initted = 1;
}

void WhiteOut::run() {
	if (initted == 0) {
		init();
	}
	double elapsed = (nowMillis() - startTime)/100.0;
	for (LED* led : mapping->dome->leds) {
		hsv_f white = { 0,0,1-elapsed };
		LEDs->setHSV(led->index, white);
	}
	if (elapsed > 1) {
		done = 1;
	}
	
}

void WhiteOut::release() {
	for (LED* led : mapping->dome->leds) {
		rgb_f white = { 0,0,0 };
		LEDs->setRGB(led->index, white);
	}
}