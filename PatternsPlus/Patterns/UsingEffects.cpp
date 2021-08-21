#include "UsingEffects.h"
#include "../helpers.h""
#include "../Effects/HEXPulse.h"
#include "../Effects/WhiteOut.h"

void UsingEffects::run(bool real) {
	if (shared->spacePressedPipe) {
		shared->spacePressedPipe = 0;
		effectEngine->apply(new HEXPulse(ledInterface, shared->mapping));
		//effectEngine->apply(new WhiteOut(ledInterface, shared->mapping));
	}

}