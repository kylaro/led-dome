#include "Shimmer.h"
void Shimmer::setStrut(Strut* strut) {
	strutSet = 1;
	this->strut = strut;
}
void Shimmer::init() {
	if (strutSet) {
		led = strut->leds[rand() % strut->leds.size()];
	}
	else {
		if (led == NULL) {
			led = mapping->dome->leds[rand() % mapping->dome->leds.size()];
		}
		
	}
	
	startTime = nowMillis();
	initted = 1;
}

void Shimmer::run() {
	if (initted == 0) {
		init();
	}
	double val = nowMillis() - startTime;
	val = val/(double)duration;
	hsv_f color = { (rand() % 100) / 100.0, (rand() % 40) / 100.0,(rand() % 60) / 100.0 + 0.4 - val / 4.0 };
	if (nowMillis() - startTime > duration) {
		release();
	}
	LEDs->setHSV(led->index,color);
	
}

void Shimmer::release() {
	done = 1;
	//turn off leds used...
	rgb_f off = { 0,0,0 };
	if(led != (LED*)0xcdcdcdcdcdcdcdcd) // not sure why i have to do this to make it not crash when switching between sim/real
		LEDs->setRGB(led->index, off);
}