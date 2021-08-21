#ifndef EMPTYEFF_H
#define EMPTYEFF_H
#include "Effect.h"


class EmptyEffect : public Effect {
public:
	using Effect::Effect;

	void apply();
};


#endif
