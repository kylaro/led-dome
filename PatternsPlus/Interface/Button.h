#ifndef BUTTON_H
#define BUTTON_H

#include "CXBOXController.h"
class CXBOXController;
class Button {
public:
	Button(CXBOXController * controller, int button);
	int button = 0;
	int isHeld();
	int isPressed();
	CXBOXController* controller;
private:
	int released = 1;
	int pressed = 0;
};




#endif