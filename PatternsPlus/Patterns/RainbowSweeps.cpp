

#include "RainbowSweeps.h"
#include <iostream>
#include "../../Networking/ledcontrol.h"
#include <algorithm>
#include <thread>


int32_t i = 0;
uint32_t k = 0;

int32_t mode = 0;

uint32_t numLeds = 0;

void RainbowSweeps:: run(bool real) {
	
	double t = time(4000);

	//pats.push_back(rainsweep);

	//rainsweep.start();
	//std::thread tr = rainsweep->start();
	//tr.detach();
	//std::thread::id tr_id = tr.get_id();


	if (shared->spacePressedPipe != 0) {
		mode += 1;
		shared->spacePressedPipe = 0;


		mode = negMod(mode, 6);
	}

	
	//k += i;
	k++;

	switch (mode) {
	case 0:
		
		numLeds = mapping->phiLeds.size();
		for (int i = 0; i < numLeds; i++) {
			int index = mapping->phiLeds[i]->index;
			uint32_t color = wheel(t * 256 + 256.0 * (i / (double)numLeds));
			//color = getB(color);// we now have an intensity 0-255
			//color = sharpenRGB(color, 200);
			//color = color > 0;
			//color = wheel(-t * 256 + i / 8) * color;
			if (ledConfirmed(mapping->phiLeds[i]))
				setLED(index, (color), real);
				
		}

		break;
	case 1:
		numLeds = mapping->phiLeds.size();
		for (int i = 0; i < numLeds; i++) {
			int index = mapping->phiLeds[i]->index;
			uint32_t color = wheel(t * 256 + 256.0 * (i / (double)numLeds));
			color = getB(color);// we now have an intensity 0-255
			color = sharpenRGB(color, 200);
			color = color > 0;
			color = wheel(-t * 256 + i / 8) * color;
			if (ledConfirmed(mapping->phiLeds[i]))
				setLED(index, (color), real);

		}
		break;
	case 2:
		numLeds = mapping->xLeds.size();
		for (int i = 0; i < numLeds; i++) {
			int index = mapping->xLeds[i]->index;
			uint32_t color = wheel(t*256+256.0*(i / (double)numLeds));
			color = getB(color);// we now have an intensity 0-255
			color = sharpenRGB(color, 200);
			color = color > 0;
			color = wheel(-t * 256 + i / 8) * color;
			if (ledConfirmed(mapping->xLeds[i]))
				setLED(index, (color), real);
		}

		break;
	case 3:
		numLeds = mapping->yLeds.size();
		for (int i = 0; i < numLeds; i++) {
			int index = mapping->yLeds[i]->index;
			uint32_t color = wheel(t * 256 + 256.0 * (i / (double)numLeds));
			color = getB(color);// we now have an intensity 0-255
			color = sharpenRGB(color, 200);
			color = color > 0;
			color = wheel(-t * 256 + i / 8) * color;
			if (ledConfirmed(mapping->yLeds[i]))
				setLED(index, (color), real);
		}

		break;
	case 4:
		numLeds = mapping->zLeds.size();
		for (int i = 0; i < numLeds; i++) {
			int index = mapping->zLeds[i]->index;
			uint32_t color = wheel(t * 256 + 256.0 * (i / (double)numLeds));
			color = getB(color);// we now have an intensity 0-255
			color = sharpenRGB(color, 200);
			color = color > 0;
			color = wheel(-t * 256 + i / 8) * color;
			if (ledConfirmed(index))
				setLED(index, (color), real);
		}
		
		break;
	case 5:
		numLeds = mapping->tanLeds.size();
		for (int i = 0; i < numLeds; i++) {
			int index = mapping->tanLeds[i]->index;
			uint32_t color = wheel(t * 256 + 256.0 * (i / (double)numLeds));
			color = getB(color);// we now have an intensity 0-255
			color = sharpenRGB(color, 200);
			color = color > 0;
			color = wheel(-t * 256 + i / 8) * color;
			if (ledConfirmed(index))
				setLED(index, (color), real);
		}
		break;


	}
	
	



	//delay2(100000);
	//std::cout << time(10e3) << std::endl;
	//time(100);
	updateLEDs( real);

	//setLED(i, wheel(k));
	i++;
	
}

