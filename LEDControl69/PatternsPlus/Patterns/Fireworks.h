#ifndef FIREWORKS_H
#define FIREWORKS_H
#include "../pattern.h"
#include "../Interface/CXBOXController.h"

class Fireworks : public Pattern {
public:
	using Pattern::Pattern;
	void init();
	void run(bool real);
	int initted = 0;
	double rumble = 0;
	char name[40] = "Fireworks";
};


#endif
