

#include "RGB.h"

uint32_t count = 0;
void RGB::run(bool real) {
	count++;
	for (LED* led : mapping->phiLeds) {
		uint32_t color = wheel(count + led->x + led->y + led->z);
		if (count % 10000 > 6660) {
			color = rDiv(color, 100);
			color = bDiv(color, 100);
			setLED(led->index, color, real);
		}
		else if (count % 10000 > 3330) {
			color = gDiv(color, 100);
			color = rDiv(color, 100);
			setLED(led->index, color, real);
		}
		else {
			color = gDiv(color, 100);
			color = bDiv(color, 100);
			setLED(led->index, color, real);
		}
		
	}
	delay2(1000000);
	updateLEDs(real);
	
}