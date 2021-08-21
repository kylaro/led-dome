#ifndef WHITEOUT_H
#define WHITEOUT_H
#include "Effect.h"


class WhiteOut : public Effect {
public:
	using Effect::Effect;

	void run();
	void init();
	void release();
};


#endif
