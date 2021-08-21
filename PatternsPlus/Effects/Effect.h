#ifndef EFFECT_H
#define EFFECT_H

#include "../Interface/LEDInterface.h"
#include "../mapping.h"
#include "../helpers.h"
class Effect {

public:
	Effect(LEDInterface * myInterface, Mapping * mapping);

	virtual void run();

	LEDInterface * LEDs;
	Mapping* mapping;

	int done = 0;

};




#endif