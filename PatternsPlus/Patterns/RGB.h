#ifndef RGB_H
#define RGB_H
#include "../pattern.h"


class RGB : public Pattern {
public:
	using Pattern::Pattern;

	void run();
};


#endif
