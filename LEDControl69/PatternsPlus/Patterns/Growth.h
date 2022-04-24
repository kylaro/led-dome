#ifndef GROWTH_H
#define GROWTH_H
#include "../pattern.h"


class Growth : public Pattern {
public:
	using Pattern::Pattern;

	void run(bool real);
	void init();
	void release();
	char name[40] = "GROWTH";

	int runOnce = 0;
};


#endif
