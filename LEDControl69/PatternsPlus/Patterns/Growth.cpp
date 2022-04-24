#include "Growth.h"
#include "../helpers.h""
#include "../Effects/Fungus.h"

void Growth::init() {
	//Called when we switch to this pattern
	
}
void Growth::run(bool real) {
	if (runOnce == 0) {
		Fungus* fungus = new Fungus(ledInterface, shared->mapping);
		fungus->giveEngine(effectEngine);
		fungus->dontdie = 1;
		effectEngine->apply(fungus);
		runOnce = 1;
	}

}

void Growth::release() {
	//Called when we switch away from this pattern
	runOnce = 0;
}