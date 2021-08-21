#ifndef LEDCHANGE_H
#define LEDCHANGE_H

#include "../color_structs.h"
class LEDChange {
public:
	LEDChange(int i, rgb_f rgb);
	int getWattsEXP(rgb_t rgb);
	double getWatts(rgb_f rgb);
	int index;
	rgb_f rgb;
	double watts;
	
};




#endif