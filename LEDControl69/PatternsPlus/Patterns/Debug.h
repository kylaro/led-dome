#ifndef DEBUG_H
#define DEBUG_H
#include "../pattern.h"


class Debug : public Pattern {
public:
	using Pattern::Pattern;

	void run(bool real);
};


#endif
