#ifndef PATTERN_H
#define PATTERN_H

#include "../Objects/dome.h"
#include "shared.h"
#include <thread>
#include "mapping.h"
#include "../Networking/ledcontrol.h"
#include "helpers.h"
class Pattern {

public:
	Pattern(Shared * sharedObject);
	std::thread start();
	virtual void run();
	Dome* dome;
	Shared* shared;
	Mapping* mapping;
private:
	virtual void beforeRender();
	virtual void render(int i, float x, float y, float z);
	void signalHandler(int sigNum);
};

#endif