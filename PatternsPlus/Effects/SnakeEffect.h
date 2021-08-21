#ifndef SNAKEEFF_H
#define SNAKEEFF_H
#include "Effect.h"


class SnakeEffect : public Effect {
public:
	using Effect::Effect;

	void run();
	void init();
	void release();
	void feed(double val);// idk the units..

	hsv_f color;
	int player;
	LLnode* curNode;
	LLnode* prevNode;
	int dir = 1;
	LLnode* lookaheadNode;
	LLnode* nextNode;
	int lookaheadSet = 0;
	int trail_k = 0;
	double velocity = 0.5;
	double position = 0;
	std::vector<ihsv_f> trail;
	double length = 0.5;
	double food = 0;
};


#endif
