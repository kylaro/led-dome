#ifndef PATTERN_H
#define PATTERN

#include "../Objects/dome.h"

class Pattern {

public:
	void giveDome(Dome* dome);
	void run();
	Dome* dome;
};

#endif