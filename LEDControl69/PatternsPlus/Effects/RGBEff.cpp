#include "RGBEff.h"

void RGBEff::init() {
	startTime = nowMillis();

	initted = 1;
}
void RGBEff::cleanup() {
	int numLeds = mapping->phiLeds.size();

	rgb_f off = { 0,0,0 };
	for (int i = 0; i < numLeds; i++) {
		int index = mapping->phiLeds[i]->index;

		//hsv_f hsv = { t * 2 + 2 * i / (double)numLeds, 1 , 1 };
		if ((mapping->phiLeds[i]->confirmed)) {
			LEDs->setRGB(index, off);
		}
	}
	didfull = 0;
}
void RGBEff::run() {
	if (initted == 0) {
		init();
	}
	if (enabled == 0) {
		if (didfull == 1) {
			cleanup();
			didfull = 0;
		}
		return;
	} 
	didfull = 1;
	double t = time(10000);
	for (LED* led : mapping->phiLeds) {
		//uint32_t color = wheel(t + (led->x + led->y + led->z)/1000.0);
		
		hsv_f hsv = { t*2, 1 , pow(triangleD(t*15 + (led->x + led->y + led->z) / 200.0),2) };
		//hue saturation and value
		LEDs->forceHSV(led->index, hsv);
		

	}
}

void RGBEff::release() {
	done = 1;
	rgb_f off = { 0,0,0 };
	//turn off leds used...
}