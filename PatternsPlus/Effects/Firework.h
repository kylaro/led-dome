#ifndef FIREWORK_H
#define FIREWORK_H
#include "Effect.h"


class Firework : public Effect {
public:
	using Effect::Effect;

	void run();
	void init();
	void release();
	
	Node* startNode;
	double velocity = 0;
	double pos = 0;
	LLnode* curNode;
	hsv_f color;
	std::vector<ihsv_f> trail;
};


#endif
