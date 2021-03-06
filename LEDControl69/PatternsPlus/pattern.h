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
	bool ledConfirmed(LED* led);
	bool ledConfirmed(int i);
	//std::thread start(); // attempted threading...
	virtual void run(bool real);
	virtual void init();
	virtual void release();
	Dome* dome;
	Shared* shared;
	Mapping* mapping;
	EffectEngine* effectEngine;
	LEDInterface* ledInterface;
	char name[40] = "noname";
private:
	virtual void beforeRender();
	virtual void render(int i, float x, float y, float z);
};

#endif