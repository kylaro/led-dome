#ifndef USINGEFFECTS_H
#define USINGEFFECTS_H
#include "../pattern.h"


class UsingEffects : public Pattern {
public:
	using Pattern::Pattern;

	void run(bool real);
};


#endif
