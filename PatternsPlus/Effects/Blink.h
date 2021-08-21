#ifndef BLINK_H
#define BLINK_H
#include "Effect.h"


class Blink : public Effect {
public:
	using Effect::Effect;

	void run();
	void init();
	void release();
	LED* led;
	Strut* strut;
	void setStrut(Strut* strut);
	int strutSet = 0;
	int duration = 10000;
	int startTime = 0;
	hsv_f color;// = 0;
};


#endif
