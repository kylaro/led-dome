#ifndef SNAKE_H
#define SNAKE_H
#include "../pattern.h"
#include "../Interface/CXBOXController.h"

class Snake : public Pattern {
public:
	using Pattern::Pattern;
	void init();
	void run(bool real);
	int initted = 0;
	double rumble = 0;
	
	//for snake
	LLnode* curNode;
	LLnode* prevNode;
	int dir = 1;
	LLnode* lookaheadNode;
	LLnode* nextNode;
	int lookaheadSet = 0;
	int trail_k = 0;
	std::vector<ihsv_f> trail;
	
};


#endif
