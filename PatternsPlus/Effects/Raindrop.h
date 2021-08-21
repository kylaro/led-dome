#ifndef RAINDROP_H
#define RAINDROP_H
#include "Effect.h"


class Raindrop : public Effect {
public:
	using Effect::Effect;

	void run();
	void init();
	void release();

	LLnode* curNode;
	LLnode* prevNode;
	std::vector<irgb_f> lights;
	rgb_f on;
	int startIndex = 0;
	int dir = 0;
	int startTime = 0;
	int crossed = 0;
	double speed = 1;
	double gonext = 0;

};


#endif
