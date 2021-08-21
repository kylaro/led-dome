

#include "RGB.h"


void RGB::run() {
	for (LED* led : dome->leds) {
		setLED (led->index, led->x, led->y, led->z);
	}
	updateLEDs();
	while (1) {
		if (shared->spacePressedPipe == 1) {
			shared->spacePressedPipe = 0;
			return;
		}
		shared->bufferPipe[0] = 1;
	}
}