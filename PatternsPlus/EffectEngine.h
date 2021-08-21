#ifndef EFFECTENGINE_H
#define EFFECTENGINE_H
#include "Effects/Effect.h"

class EffectEngine {
public:
	EffectEngine();
	void clear();
	std::vector<Effect*> effects;
	void apply(Effect * effect);
	void run();
};





#endif