#ifndef LEDCHANGE_H
#define LEDCHANGE_H

#include "../color_structs.h"
class LEDChange {
public:
	LEDChange(int i, rgb_t rgb);
	LEDChange(int i, hsv_t rgb);
	int index;
	rgb_t rgb;
	hsv_t hsv;
	int rgborhsv = 0; // 0 is rgb, 1 is hsv
};




#endif