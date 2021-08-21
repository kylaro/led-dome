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
void runEngine() {
	init();
	shared->clearBuffer();
	
	std::vector<Pattern*> patterns;
	//PUSH ALL THE PATTERNS WE WANT
	//todo in the future, map specific keys to specific patterns?

	patterns.push_back(new RainbowSweeps(shared));
	patterns.push_back(new RGB(shared));

	Pattern* realPattern = patterns[0];
	Pattern* simulatedPattern = patterns[0];
	int sim_pattern_i = 0;
	int real_pattern_i = 0;
	int patterns_len = patterns.size();
	while (1) {
		
		if (real_pattern_i == sim_pattern_i) {
			realPattern->run(true);
			shared->viewReal = true;
		}
		else {
			//run both
			
			simulatedPattern->run(false);/// i wish there was a way to thread this...
			realPattern->run(true);
			shared->viewReal = false;
			
		}
		

		//HANDLE SUBMITTED BUFFER
		if (shared->submitPipe) {
			shared->submitPipe = 0;
			//SIMULATED VS REAL:
			if (shared->bufferPipe[0] == 0) {
				//The buffer is empty, this is just enter
				printf("Real = simulation\n");
				if (real_pattern_i != sim_pattern_i) {
					clearLEDs();
				}
				real_pattern_i = sim_pattern_i;

				realPattern = patterns[sim_pattern_i];
				shared->viewReal = true;
			}
			//if shared-> buffer == "cal" - enters calibration Pattern
			//im really thinking about having another thread that handles input.... hmm
			//probably in here we do something like 


			shared->clearBuffer();
		}

		//HANDLE SWITCHING PATTERNS:
		// use plus minus keys? presss number key and it jumps to numbered pattern? patterns have names and can be searched for?
		if (shared->directionPipe != 0) {
			sim_pattern_i += shared->directionPipe;
			sim_pattern_i = negMod(sim_pattern_i, patterns_len);
			simulatedPattern = patterns[sim_pattern_i];
			shared->directionPipe = 0;
			clearLEDs(false);
		}
	}
	
}