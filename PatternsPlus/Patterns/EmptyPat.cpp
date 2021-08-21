#include "EmptyPat.h"
#include "../helpers.h""


void EmptyPat::run(bool real) {
	setLED(0, 0, real);//Be sure to include real at the end to differentiate between simulated calls and real calls
	updateLEDs(real);

}