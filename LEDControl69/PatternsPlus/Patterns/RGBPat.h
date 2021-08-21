#ifndef RGB_H
#define RGB_H
#include "../pattern.h"


class RGBPat : public Pattern {
public:
	using Pattern::Pattern;

	void run(bool real);
	char name[40] = "RGB";
};


#endif
