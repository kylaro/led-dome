#include "LEDChange.h"

int LEDChange::getWattsEXP(rgb_t rgb) {
	return rgb.r + rgb.g + rgb.b;
}

double LEDChange::getWatts(rgb_f rgb) {
	return 12.0 * (rgb.r*0.02 + rgb.g* 0.02 + rgb.b* 0.02);//12v * 20mA max/LED
}

void LEDChange::force(rgb_f newrgb) {
	if (locked == 0) {
		rgb = newrgb;
		locked++;
		count++;
	} else {
		rgb.r = (rgb.r * locked + newrgb.r) / (double)(locked + 1);
		rgb.g = (rgb.g * locked + newrgb.g) / (double)(locked + 1);
		rgb.b = (rgb.b * locked + newrgb.b) / (double)(locked + 1);
		locked++;
		count++;
	}
	
}
void LEDChange::assimilate(rgb_f newrgb) {
	if (locked > 0) {
		return;
	}
	if (count == 0) {
		rgb = newrgb;
		count++;
		return;
	}
	else {
		rgb.r = (rgb.r * count + newrgb.r) / (double)(count + 1);
		rgb.g = (rgb.g * count + newrgb.g) / (double)(count + 1);
		rgb.b = (rgb.b * count + newrgb.b) / (double)(count + 1);
		count++;
	}
	
}
LEDChange::LEDChange(int i, rgb_f rgb) {
	index = i;
	this->rgb = rgb;
	//watts = getWatts(rgb);
}
