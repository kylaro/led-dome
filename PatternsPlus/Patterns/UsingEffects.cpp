#include "UsingEffects.h"
#include "../helpers.h""
#include "../Effects/HEXPulse.h"

void UsingEffects::run(bool real) {
	if (shared->spacePressedPipe) {
		shared->spacePressedPipe = 0;
		effectEngine->apply(new HEXPulse(ledInterface, shared->mapping));
	}

}