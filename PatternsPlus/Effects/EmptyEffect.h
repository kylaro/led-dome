#ifndef EMPTYEFF_H
#define EMPTYEFF_H
#include "Effect.h"


class EmptyEffect : public Effect {
public:
	using Effect::Effect;

	void run();
	void init();
	void release();
};


#endif
