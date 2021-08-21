#ifndef EMPTYEFF_H
#define EMPTYEFF_H
#include "Effect.h"


class EmptyEffect : public Effect {
public:
	using Effect::Effect;

	int startTime = 0;
	void run();
	void init();
	void release();
};


#endif
