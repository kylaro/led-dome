#ifndef THUMBSTICK_H
#define THUMBSTICK_H

#include "CXBOXController.h"
class CXBOXController;
class Thumbstick {
public:
	Thumbstick(CXBOXController* controller);

	int getActive();

	double x = 0;
	double y = 0;
	CXBOXController* controller;
	double getX();
	double getY();
	double getAngle();//returns angle in radians, 0 to 2pi;
private:
	int released = 1;
	int pressed = 0;
};




#endif