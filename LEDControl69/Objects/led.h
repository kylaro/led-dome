#ifndef LED_HFILE
#define LED_HFILE

#include "../PatternsPlus/positioning.h"
class LED {
public:
	LED(int i);
	void setXYZ(float x, float y, float z);
	int index;
	int confirmed = 0;
	float x, y, z;
	xyz_f xyz;

};

#endif
