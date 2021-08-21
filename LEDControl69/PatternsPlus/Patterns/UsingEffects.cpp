#include "UsingEffects.h"
#include "../helpers.h""
#include "../Effects/HEXPulse.h"
#include "../Effects/WhiteOut.h"
#include "../Effects/Pinwheel.h"
#include "../Effects/SwingingStrut.h"
#include "../Effects/Firework.h"

void UsingEffects::run(bool real) {
	if (shared->spacePressedPipe) {
		shared->spacePressedPipe = 0;
		//effectEngine->apply(new Pinwheel(ledInterface, shared->mapping));
		//effectEngine->apply(new HEXPulse(ledInterface, shared->mapping));
		//effectEngine->apply(new SwingingStrut(ledInterface, shared->mapping));
		//effectEngine->apply(new WhiteOut(ledInterface, shared->mapping));
		Firework* fire = new Firework(ledInterface, shared->mapping);
		fire->giveEngine(effectEngine);
		effectEngine->apply(fire);

	}

}