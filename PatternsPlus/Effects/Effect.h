#ifndef EFFECT_H
#define EFFECT_H

#include "../Interface/LEDInterface.h"
#include "../mapping.h"
#include "../helpers.h"
class Effect {

public:
	Effect(LEDInterface * myInterface, Mapping * mapping);

	virtual void run();
	virtual void init();
	virtual void release();

	LEDInterface * LEDs;
	Mapping* mapping;

	int done = 0;
	int initted = 0;

};




#endif