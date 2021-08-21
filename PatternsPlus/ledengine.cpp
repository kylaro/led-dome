#include "ledengine.h"
#include <iostream>
#include <chrono>
#include "../Networking/ledcontrol.h"
#include <algorithm>
#include <thread>
#include "pattern.h"
#include "Patterns/RainbowSweeps.h"
#include "Patterns/RGB.h"
#include <signal.h>

Dome* dome;
Shared* shared;





void giveEngineShared(Shared* sharedObject) {
	shared = sharedObject;
	dome = shared->dome;
}

void init() {
	initLEDController();

	shared->mapping = new Mapping(dome);
	

}


using namespace std::chrono;
void run() {
	init();

	Pattern* rainsweep = new RainbowSweeps(shared);
	std::vector<Pattern*> patterns;
	//PUSH ALL THE PATTERNS WE WANT
	//todo in the future, map specific keys to specific patterns?

	patterns.push_back(new RainbowSweeps(shared));
	patterns.push_back(new RGB(shared));

	Pattern* currentPattern = patterns[0];
	int pattern_i = 0;
	int patterns_len = patterns.size();
	while (1) {
		
		currentPattern->run();/// i wish there was a way to thread this...

		//HANDLE SUBMITTED BUFFER
		if (shared->submitPipe) {
			shared->submitPipe = 0;
			//if shared-> buffer == "cal" - enters calibration Pattern
			//im really thinking about having another thread that handles input.... hmm
			//probably in here we do something like 
		}

		//HANDLE SWITCHING PATTERNS:
		// use plus minus keys? presss number key and it jumps to numbered pattern? patterns have names and can be searched for?
		if (shared->directionPipe != 0) {
			pattern_i += shared->directionPipe;
			pattern_i = negMod(pattern_i, patterns_len);
			currentPattern = patterns[pattern_i];
			shared->directionPipe = 0;
			clearLEDs();
		}
	}
	
}