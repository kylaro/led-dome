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
	//turn off leds used...
}