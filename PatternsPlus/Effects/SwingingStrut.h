#ifndef SWINGINGSTRUT_H
#define SWINGINGSTRUT_H
#include "Effect.h"


class SwingingStrut : public Effect {
public:
	using Effect::Effect;

	void run();
	void init();
	void release();
	double color = 0;
	Node* node;
	Strut* curStrut;
	std::vector<ihsv_f> leds;
	double gonext = 0;
	double speed = 0.05;
};


#endif
