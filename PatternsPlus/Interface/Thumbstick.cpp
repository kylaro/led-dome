#include "Thumbstick.h"


Thumbstick::Thumbstick(CXBOXController* controller) {
	this->controller = controller;
}
int Thumbstick::getActive() {
	return (getX() != 0 || getY() != 0);
}
double Thumbstick::getAngle() {//-pi to pi
	double angle = atan2(getY(), getX());
	printf("%f\n",angle);
	return angle;
}

double Thumbstick::getX() {
	XINPUT_STATE state = controller->GetState();
	XINPUT_GAMEPAD gamepad = state.Gamepad;
	int rawX = gamepad.sThumbLX + 32768;
	double niceX = rawX / 65535.0;// now is 0 to 1;
	niceX -= 0.5;
	niceX *= 2;// i wonder how much precision we are losing doing all this..
	if (fabs(niceX) < 0.001) {
		niceX = 0;
	}
	return niceX;
}

double Thumbstick::getY() {
	XINPUT_STATE state = controller->GetState();
	XINPUT_GAMEPAD gamepad = state.Gamepad;
	int rawY = gamepad.sThumbLY + 32768;
	double niceY = rawY / 65535.0;// now is 0 to 1;
	niceY -= 0.5;
	niceY *= 2;// i wonder how much precision we are losing doing all this..
	if (fabs(niceY) < 0.001) {
		niceY = 0;
	}
	return niceY;
}