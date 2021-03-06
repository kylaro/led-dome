#ifndef HEXPULSE_H
#define HEXPULSE_H
#include "Effect.h"


class HEXPulse : public Effect {
public:
	using Effect::Effect;

	void init();
	void run();
	void release();
	void setNode(int n);

	std::vector<ihsv_f> leds;
	int startTime = 0;
	int initted = 0;
	int node;
	int nodeSet = 0;
};


#endif
