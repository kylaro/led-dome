#ifndef EFFECTENGINE_H
#define EFFECTENGINE_H
#include "Effects/Effect.h"
class Effect;
class EffectEngine {
public:
	EffectEngine();
	void clear();
	std::vector<Effect*> effects;
	std::vector<Effect*> effectsQueue;
	void apply(Effect * effect);
	void queueApply(Effect* effect);
	void run();
};





#endif