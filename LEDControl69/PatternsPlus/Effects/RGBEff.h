#ifndef RGBEFF_H
#define RGBEFF_H
#include "Effect.h"


class RGBEff : public Effect {
public:
	using Effect::Effect;

	int startTime = 0;
	void run();
	void init();
	void release();
	void cleanup();
	int enabled = 1;
	int didfull = 0;
};


#endif
