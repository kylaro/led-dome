#ifndef FIREFLIES_H
#define FIREFLIES_H
#include "../pattern.h"


class Fireflies : public Pattern {
public:
	using Pattern::Pattern;

	void run(bool real);
	char name[40] = "Fireflies";
};


#endif
