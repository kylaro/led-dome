
#include "pattern.h"
#include "../Networking/ledcontrol.h"
#include <csignal>

Pattern::Pattern( Shared * sharedObject ) {
	this->dome = sharedObject->dome;
	this->shared = sharedObject;
	this->mapping = sharedObject->mapping;
}

/*
std::thread Pattern::start() {
	//std::thread pat(&Pattern::run, this);
	//return pat;
	
}*/

bool Pattern::ledConfirmed(LED * led) {
	if (led == NULL) {
		return false;
	}
	return led->confirmed;
}
bool Pattern::ledConfirmed(int i) {
	LED* ledobj = shared->mapping->getLEDObj(i);
	if (ledobj == NULL) {
		return false;
	}
	return ledobj->confirmed;
	
}

void Pattern::run(bool real) {


	beforeRender();
	for (LED* led : this->dome->leds) {
		render(led->index, led->x, led->y, led->z);
	}
	
}

//Could add delta, could add more time, but that's later
void Pattern::beforeRender() {

}


void Pattern::render(int i, float x, float y, float z) {
	
	setLED(i, wheel(i) );
}
