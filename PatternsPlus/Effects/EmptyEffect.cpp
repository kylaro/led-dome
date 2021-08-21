#include "EmptyEffect.h"

void EmptyEffect::init() {


	initted = 1;
}

void EmptyEffect::run() {
	if (initted == 0) {
		init();
	}
}

void EmptyEffect::release() {
	done = 1;
	rgb_f off = { 0,0,0 };
	//turn off leds used...
}