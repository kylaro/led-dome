#include "Pershing.h"
#include "../helpers.h""
#include "../Effects/Firefly.h"

void Pershing::run(bool real) {
	

	effectEngine->apply(new Firefly(ledInterface, shared->mapping));
}