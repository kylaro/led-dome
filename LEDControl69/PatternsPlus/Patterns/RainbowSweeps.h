#ifndef RAINBOWSWEEPS_H
#define RAINBOWSWEEPS_H
#include "../pattern.h"


class RainbowSweeps : public Pattern {
public:
	using Pattern::Pattern;

	void run(bool real);
	char name[40] = "RainbowSweeps";
};


#endif
