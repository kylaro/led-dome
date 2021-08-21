#include "ledengine.h"
#include <iostream>
#include <chrono>
#include "../Networking/ledcontrol.h"
#include <algorithm>
#include <thread>
#include "pattern.h"
#include "Patterns/RainbowSweeps.h"
#include "Patterns/RGB.h"
#include "Patterns/Calibration.h"
#include <signal.h>
#include <string>
#include "Patterns/Debug.h"
#include "EffectEngine.h"
#include "Interface/LEDInterface.h"
#include "Patterns/UsingEffects.h"
#include "Patterns/ShowLL.h"

Dome* dome;
Shared* shared;

#define FRAME_RATE 50 //duh. suggestd max is 350 to ensure controller can handle all the packets
uint32_t framerate_nanos = (1 / ((float)FRAME_RATE)) * 1e9;
uint32_t framerate_micros = (1 / ((float)FRAME_RATE)) * 1e6;
uint32_t framerate_millis = (1 / ((float)FRAME_RATE)) * 1e3;
double freetime_avg = -1;
double effectiveFPS = FRAME_RATE;
void giveEngineShared(Shared* sharedObject) {
	shared = sharedObject;
	dome = shared->dome;
}

void init() {
	initLEDController();
	loadCalibration(dome);
	shared->mapping = new Mapping(dome);
}


using namespace std;
void handleBuffer(char * buffer) {
	string buf = string(buffer);
	if (buf == "fps") {
		double maxfps = (1e6)/(1 - freetime_avg)*(framerate_micros);
		printf("FreetimeAVG = %f\n", freetime_avg);
		printf("real FPS = %f\n", effectiveFPS);
	}
	else if (buf == "calibrate" || buf == "calibration" || buf == "mapping") {
		printf("Beginning Calibration...\n");

		Pattern* cal = new Calibration(shared);
		shared->viewReal = false;
		clearLEDs();
		shared->clearBuffer();
		shared->calibratingPipe = 1;
		cal->run(true);
		shared->calibratingPipe = 0;
	}
}

void runEngine() {
	init();
	shared->clearBuffer();
	uint32_t count = 0;
	std::vector<Pattern*> patterns;
	EffectEngine* effectEngineReal = new EffectEngine();
	EffectEngine* effectEngineSim = new EffectEngine();
	LEDInterface* ledInterfaceReal = new LEDInterface(true);
	LEDInterface* ledInterfaceSim = new LEDInterface(false);
	//shared->effectEngine = effectEngine;
	
	
	//PUSH ALL THE PATTERNS WE WANT
	//todo in the future, map specific keys to specific patterns?
	patterns.push_back(new ShowLL(shared));
	patterns.push_back(new UsingEffects(shared));
	patterns.push_back(new RainbowSweeps(shared));
	
	patterns.push_back(new RGB(shared));

	Pattern* realPattern = patterns[0];
	Pattern* simulatedPattern = patterns[0];
	int sim_pattern_i = 0;
	int real_pattern_i = 0;
	int patterns_len = patterns.size();
	
	uint32_t beginMicros = nowMicros();
	uint32_t lastbeginMicros = nowMicros();
	
	uint32_t elapsed = 0;
	double freetime = 0;

	uint32_t timer = 0;
	clearLEDs();
	
	while (1) {
		//PREPARE STATISTICS
		count++;
		beginMicros = nowMicros();
		elapsed = beginMicros - lastbeginMicros;
		effectiveFPS = 1e6 / (double)elapsed;//(effectiveFPS * 19 + (1e6 / elapsed)) / 20.0;... 1 second / time for 1 frame
		lastbeginMicros = beginMicros;

		timer = nowMicros();
		//RUN THE PATTERNs
		if (real_pattern_i == sim_pattern_i) {
			realPattern->ledInterface = ledInterfaceReal;
			realPattern->effectEngine = effectEngineReal;
			timer = nowMicros();
			realPattern->run(true);
			printf("\tpatrun=\t%d\n", nowMicros() - timer);

			timer = nowMicros();
			effectEngineReal->run();
			printf("\teffect=\t%d\n", nowMicros() - timer);
			shared->viewReal = true;

			timer = nowMicros();
			ledInterfaceReal->apply();
			printf("\tledint=\t%d\n", nowMicros() - timer);
		}
		else {
			//run both if they are different
			realPattern->ledInterface = ledInterfaceReal;
			realPattern->effectEngine = effectEngineReal;
			simulatedPattern->ledInterface = ledInterfaceSim;
			simulatedPattern->effectEngine = effectEngineSim;
			simulatedPattern->run(false);/// i wish there was a way to thread this...
			realPattern->run(true);
			effectEngineReal->run();
			effectEngineSim->run();
			shared->viewReal = false;
			ledInterfaceReal->apply();
			ledInterfaceSim->apply();
		}
		//RUN THE EFFECTS THAT THE PATTERNS HAVE CREATED
		
		//printf("RUN=%d\n", nowMicros() - timer);
		//Then update leds
		timer = nowMicros();
		updateLEDs();
		//printf("UPD=%d\n", nowMicros() - timer);
		//WARN IF FREETIME IS LOW
		freetime = ((double)(framerate_micros - (nowMicros() - beginMicros))) / framerate_micros;

		if (freetime_avg == -1) {
			freetime_avg = freetime;
		}
		if (freetime_avg < 0.2) {
			printf("Warning, free time between patterns is very low at: %f out of 1\n", freetime);
			printf("FreetimeAVG = %f\n", freetime_avg);
		} 
		freetime_avg = (freetime_avg * 9 + freetime) / 10.0; // keep track of average freetime
		

		//PROCESS USER INPUT DURING FREE TIME
		//note: nowNanos wraps to 0 
		do {

			//printf("test%d\n", shared->directionPipe);
			//We will be handling input until it is time to do the next frame
			//printf("%f\n", time(10000));
			//HANDLE SUBMITTED BUFFER
			if (shared->submitPipe) {
				shared->submitPipe = 0;
				//SIMULATED VS REAL:
				if (shared->bufferPipe[0] == 0) {
					//The buffer is empty, this is just enter
					printf("Real = simulation\n");
					if (real_pattern_i != sim_pattern_i) {
						effectEngineReal->clear();
						clearLEDs();

					}
					real_pattern_i = sim_pattern_i;

					realPattern = patterns[sim_pattern_i];
					//TODO MAYBE ADD A SWAP BETWEEN REAL AND SIM EFFECT ENGINES
					shared->viewReal = true;
				}
				else {
					//The buffer has contents...
					handleBuffer(shared->bufferPipe);
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
				effectEngineSim->clear();
				shared->directionPipe = 0;
				clearLEDs(false);
			}

		} while ((elapsed = nowMicros() - (beginMicros)) < framerate_micros);
	}
	
}


