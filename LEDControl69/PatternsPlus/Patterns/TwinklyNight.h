#ifndef TWINKLY_H
#define TWINKLY_H
#include "../pattern.h"


class TwinklyNight : public Pattern {
public:
	using Pattern::Pattern;

	void run(bool real);
	char name[40] = "TwinklyNight";
};


#endif
