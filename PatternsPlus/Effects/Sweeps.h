#ifndef SWEEPS_H
#define SWEEPS_H
#include "Effect.h"


class Sweeps : public Effect {
public:
	using Effect::Effect;

	void run();
	void init();
	void release();
	void cleanup();

	int enabled = 1;
	int startTime = 0;
	int mode = 0;
	const int rainbow = 0;
	const int left_sweep = 1;
	const int right_sweep = 2;
	const int up_sweep = 4;
	const int down_sweep = 3;
	int didfull = 0;
};


#endif
