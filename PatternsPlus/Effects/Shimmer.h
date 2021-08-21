#ifndef SHIMMER_H
#define SHIMMER_H
#include "Effect.h"


class Shimmer : public Effect {
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
};


#endif
