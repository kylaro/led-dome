#include "WhiteOut.h"

void WhiteOut::init() {
	for (LED* led : mapping->dome->leds) {
		rgb_f white = { 0,0,1 };
		LEDs->setRGB(led->index, white);
	}
	initted = 1;
}

void WhiteOut::run() {
	if (initted == 0) {
		init();
	}
	release();
}

void WhiteOut::release() {
	done = 1;
}