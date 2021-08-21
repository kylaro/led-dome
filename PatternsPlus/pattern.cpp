
#include "pattern.h"
#include "../Networking/ledcontrol.h"
#include <csignal>

Pattern::Pattern( Shared * sharedObject ) {
	this->dome = sharedObject->dome;
	this->shared = sharedObject;
	this->mapping = sharedObject->mapping;
}

std::thread Pattern::start() {
	std::thread pat(&Pattern::run, this);
	return pat;
	
}


void Pattern::run() {

	while (1) {
		beforeRender();
		for (LED* led : this->dome->leds) {
			render(led->index, led->x, led->y, led->z);
		}
	}
}

//Could add delta, could add more time, but that's later
void Pattern::beforeRender() {
	while (1) {

	}
}


void Pattern::render(int i, float x, float y, float z) {
	
	setLED(i, wheel(i) );
}

void Pattern::signalHandler(int sigNum) {
	exit(69);
}