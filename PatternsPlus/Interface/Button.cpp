#include "Button.h"


Button::Button(CXBOXController* controller, int button) {
	this->button = button;
	this->controller = controller;
}

int Button :: isHeld() {
	if (controller->GetState().Gamepad.wButtons & this->button)
	{
		//Player1->Vibrate(0, 65535);
		if (released == 1) {
			pressed = 1;
		}
		released = 0;
		return 1;
	}
	else {
		pressed = 0;
		released = 1;
	}
	return 0;
}

int Button::isPressed() {
	isHeld();
	if (pressed == 1) {
		pressed = 0;
		return 1;
	}
	return 0;
}

