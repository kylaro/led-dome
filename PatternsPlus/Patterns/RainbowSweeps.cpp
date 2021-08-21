

#include "RainbowSweeps.h"
#include <iostream>
#include "../../Networking/ledcontrol.h"
#include <algorithm>
#include <thread>


int32_t i = 0;
uint32_t k = 0;
uint32_t xled = 1200;
uint32_t xled2 = 0;
uint32_t yled = 1200;
uint32_t yled2 = 0;
uint32_t zled = 1200;
uint32_t zled2 = 0;
int32_t mode = 0;
uint32_t philed = 800;
uint32_t philed2 = 0;
uint32_t tanled = 1200;
uint32_t tanled2 = 0;
void RainbowSweeps:: run(bool real) {
	


	//pats.push_back(rainsweep);

	//rainsweep.start();
	//std::thread tr = rainsweep->start();
	//tr.detach();
	//std::thread::id tr_id = tr.get_id();


	if (shared->spacePressedPipe != 0) {
		mode += 1;
		shared->spacePressedPipe = 0;


		mode = negMod(mode, 5);
	}

	i %= dome->totalLEDs;
	//k += i;
	k++;

	switch (mode) {
	case 0:
		philed++;
		philed2++;
		philed %= mapping->phiLeds.size();
		philed2 %= mapping->phiLeds.size();


		setLED(mapping->phiLeds[philed]->index, wheel(k / 10), real);
		setLED(mapping->phiLeds[philed2]->index, 0, real);
		break;
	case 1:
		xled++;
		xled2++;
		xled %= mapping->xLeds.size();
		xled2 %= mapping->xLeds.size();


		setLED(mapping->xLeds[xled]->index, wheel(k / 10), real);
		setLED(mapping->xLeds[xled2]->index, 0, real);
		break;
	case 2:
		yled++;
		yled2++;
		yled %= mapping->yLeds.size();
		yled2 %= mapping->yLeds.size();


		setLED(mapping->yLeds[yled]->index, wheel(k / 10), real);
		setLED(mapping->yLeds[yled2]->index, 0, real);
		break;
	case 3:
		zled++;
		zled2++;
		zled %= mapping->zLeds.size();
		zled2 %= mapping->zLeds.size();


		setLED(mapping->zLeds[zled]->index, wheel(k / 10), real);
		setLED(mapping->zLeds[zled2]->index, 0, real);
		break;
	case 4:
		tanled++;
		tanled2++;
		tanled %= mapping->tanLeds.size();
		tanled2 %= mapping->tanLeds.size();


		setLED(mapping->tanLeds[tanled]->index, wheel(k / 10), real);
		setLED(mapping->tanLeds[tanled2]->index, 0, real);
		break;


	}
	
	



	delay2(100000);
	//std::cout << time(10e3) << std::endl;
	//time(100);
	updateLEDs( real);

	//setLED(i, wheel(k));
	i++;
	
}