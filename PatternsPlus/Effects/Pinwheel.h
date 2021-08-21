#ifndef PINWHEEL_H
#define PINWHEEL_H
#include "Effect.h"


class Pinwheel : public Effect {
public:
	using Effect::Effect;

	void run();
	void init();
	void release();
	double angle = 0;
	int nodeI = 0;
	Node* node;
	Strut* selectedStrut;

};


#endif
