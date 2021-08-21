

#include "RGB.h"
#include "../helpers.h""
double t = 0;
void RGB::run(bool real) {
	t = time(10000);
	for (LED* led : mapping->phiLeds) {
		uint32_t color = wheel(t*4000 + led->x + led->y + led->z);
		if (t > 0.66) {
			color = rDiv(color, 100);
			color = bDiv(color, 100);
			setLED(led->index, color, real);
		}
		else if (t > 0.33) {
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
	//delay2(1000000);
	updateLEDs(real);
	
}