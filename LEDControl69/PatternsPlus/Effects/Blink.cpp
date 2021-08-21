#include "Blink.h"
void Blink::setStrut(Strut* strut) {
	strutSet = 1;
	this->strut = strut;
}
void Blink::init() {
	if (strutSet) {
		led = strut->leds[rand() % strut->leds.size()];
	}
	else {
		led = mapping->dome->leds[rand() % mapping->dome->leds.size()];
	}
	startTime = nowMillis();
	initted = 1;
	color = { (rand() % 10) / 100.0 +0.2*atan2(led->x, led->z)+(startTime%10000)/10000.0,1,1 };
	//color = { (startTime % 10000) / 10000.0,1,1 };
	//color = { 0.2 * atan2(led->x,led->z),1,1 };
	//color = { (rand() % 10) / 100.0,1,1 };
}

void Blink::run() {
	if (initted == 0) {
		init();
	}
	double val = nowMillis() - startTime;
	val = val / (double)duration;
	//hsv_f color = { (rand() % 100) / 100.0, (rand() % 40) / 100.0,(rand() % 60) / 100.0 + 0.4 - val / 4.0 };
	if (nowMillis() - startTime > duration) {
		release();
	}
	color.v = 1-val*val;
	LEDs->setHSV(led->index, color);

}

void Blink::release() {
	done = 1;
	//turn off leds used...
	rgb_f off = { 0,0,0 };
	if (led != (LED*)0xcdcdcdcdcdcdcdcd) // not sure why i have to do this to make it not crash when switching between sim/real
		LEDs->setRGB(led->index, off);
}