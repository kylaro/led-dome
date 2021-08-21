#ifndef SHOWLL_H
#define SHOWLL_H
#include "../pattern.h"


class ShowLL : public Pattern {
public:
	using Pattern::Pattern;

	void run(bool real);
};


#endif
