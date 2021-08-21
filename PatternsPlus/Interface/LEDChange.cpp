#include "LEDChange.h"

LEDChange::LEDChange(int i, rgb_t rgb) {
	index = i;
	this->rgb = rgb;
	rgborhsv = 0;
	this->hsv = { 0,0,0 };
}

LEDChange::LEDChange(int i, hsv_t hsv) {
	index = i;
	this->hsv = hsv;
	rgborhsv = 1;
	this->rgb = { 0,0,0 };
}