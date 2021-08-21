#ifndef SNAKEFIREWORK_H
#define SNAKEFIREWORK_H
#include "Effect.h"
#include "SnakeEffect.h"
class SnakeFirework : public Effect {
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
	int player = 0;
	SnakeEffect* snake;
	int initted = 0;
	
};


#endif
