#ifndef PERSHING_H
#define PERSHING_H
#include "../pattern.h"


class Pershing : public Pattern {
public:
	using Pattern::Pattern;

	void run(bool real);
	char name[40] = "empty";
};


#endif
