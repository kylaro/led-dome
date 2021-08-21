#include "led.h"


LED::LED(int i) {
	this->index = i;
	this->x = 0;
	this->y = 0;
	this->z = 0;
	xyz = { x,y,z };
}

void LED::setXYZ(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	xyz = { x,y,z };
}