#ifndef EMPTY_H
#define EMPTY_H
#include "../pattern.h"


class BodyTracking : public Pattern {
public:
	using Pattern::Pattern;

	void run(bool real);
	void init();
	void release();
	char name[40] = "empty";
};


#endif
