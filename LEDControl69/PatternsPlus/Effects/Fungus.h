#ifndef FUNGUS_H
#define FUNGUS_H
#include "Effect.h"


class Fungus : public Effect {
public:
	using Effect::Effect;


	void run();
	void init();
	void init(LLnode* starting_node);
	void release();

	int dontdie = 0;
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
