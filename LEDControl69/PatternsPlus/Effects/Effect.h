#ifndef EFFECT_H
#define EFFECT_H

#include "../Interface/LEDInterface.h"
#include "../mapping.h"
#include "../helpers.h"
#include "../EffectEngine.h"


class EffectEngine;

class Effect {

public:
	Effect(LEDInterface * myInterface, Mapping * mapping);

	
	EffectEngine* engine = NULL;
	virtual void run();
	virtual void init();
	virtual void release();

	LEDInterface * LEDs;
	Mapping* mapping;
	void giveEngine(EffectEngine* effE);

	int done = 0;
	int initted = 0;

};




#endif