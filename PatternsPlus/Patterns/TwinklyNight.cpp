#include "TwinklyNight.h"
#include "../helpers.h""
#include "../Effects/Shimmer.h"

void TwinklyNight::run(bool real) {
	
	effectEngine->apply(new Shimmer(ledInterface, mapping));
	effectEngine->apply(new Shimmer(ledInterface, mapping));

}