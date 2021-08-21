#ifndef XBOX_H2
#define XBOX_H2
#include "CXBOXController.h"
const int P1 = 1;
const int P2 = 2;
namespace xbox {
	//const int P1 = 1;
	//const int P2 = 2;

	void vibrate(int p, double val);
	int getAPress(int p);
	int anyPressed(int p);
	int anyHeld(int p);

	void rumble(int p);
	double getLeftThumbX(int p);
	double getLeftThumbAngle(int p);
	int getLeftThumbActive(int p);

	int getDpadUpPress(int p);
	int getDpadUpHeld(int p);

	int getDpadDownPress(int p);
	int getDpadDownHeld(int p);
	int getDpadLeftPress(int p);
	int getDpadLeftHeld(int p);

	int getDpadRightPress(int p);
	int getDpadRightHeld(int p);

	int getStartPress(int p);
	int getStartHeld(int p);

	int getBackPress(int p);
	int getBackHeld(int p);

	int getLeftThumbPress(int p);
	int getLeftThumbHeld(int p);

	int getRightThumbPress(int p);
	int getRightThumbHeld(int p);

	int getLeftShoulderPress(int p);
	int getLeftShoulderHeld(int p);

	int getRightShoulderPress(int p);
	int getRightShoulderHeld(int p);

	int getAPress(int p);
	int getAHeld(int p);

	int getBPress(int p);
	int getBHeld(int p);

	int getXPress(int p);
	int getXHeld(int p);

	int getYPress(int p);
	int getYHeld(int p);

}



#endif