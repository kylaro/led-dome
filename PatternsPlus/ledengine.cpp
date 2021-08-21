#include "ledengine.h"
#include <iostream>
#include <chrono>
#include "../Networking/ledcontrol.h"
#include <algorithm>
Dome* dome;


std::vector<LED*> xLeds;
std::vector<LED*> yLeds;
std::vector<LED*> zLeds;
std::vector<LED*> phiLeds; // 1 side rotation
std::vector<LED*> tanLeds; // 2 sided rotation

void giveEngineDome(Dome* theDome) {
	dome = theDome;
}

void init() {
	initLEDController();

	//Let's create the x y z led arrays
	std::cout << "meowbefore" << std::endl;
	bool addedOne = false;
	for (LED* led : dome->leds) {
		if (addedOne) {
			int size = xLeds.size();
			int didInsert = 0;
			for (int i = 0; i < size; i++) {
				
				if (led->x < xLeds[i]->x) {
					//if our current LED is lower, that means it is now in the right place
					xLeds.insert(xLeds.begin() + i, led);
					didInsert = 1;
					break;
				}
				
			}
			if (didInsert == 0) {
				//We didn't even add it  bc it was so big
				xLeds.push_back(led);
			}

			size = yLeds.size();
			didInsert = 0;
			for (int i = 0; i < size; i++) {
				if (led->y < yLeds[i]->y) {
					//if our current LED is lower, that means it is now in the right place
					yLeds.insert(yLeds.begin() + i, led);
					didInsert = 1;
					break;
				}

			}
			if (didInsert == 0) {
				//We didn't even add it  bc it was so big
				yLeds.push_back(led);
			}

			size = zLeds.size();
			didInsert = 0;
			for (int i = 0; i < size; i++) {
				if (led->z < zLeds[i]->z) {
					//if our current LED is lower, that means it is now in the right place
					zLeds.insert(zLeds.begin() + i, led);
					didInsert = 1;
					break;
				}

			}
			if (didInsert == 0) {
				//We didn't even add it  bc it was so big
				zLeds.push_back(led);
			}

			//35 billion dollars
			size = phiLeds.size();
			didInsert = 0;
			float led_phi = 0;
			float philed_phi = 0;
			for (int i = 0; i < size; i++) {
				led_phi = atan2(led->z , led->x);
				philed_phi = atan2(phiLeds[i]->z , phiLeds[i]->x);
				if (led_phi < philed_phi) {
					//if our current LED is lower, that means it is now in the right place
					phiLeds.insert(phiLeds.begin() + i, led);
					didInsert = 1;
					break;
				}

			}
			if (didInsert == 0) {
				//We didn't even add it  bc it was so big
				phiLeds.push_back(led);
			}
			

			//35 billion dollars
			size = tanLeds.size();
			didInsert = 0;
			led_phi = 0;
			philed_phi = 0;
			for (int i = 0; i < size; i++) {
				led_phi = atan(led->z / led->x);
				philed_phi = atan(tanLeds[i]->z / tanLeds[i]->x);
				if (led_phi < philed_phi) {
					//if our current LED is lower, that means it is now in the right place
					tanLeds.insert(tanLeds.begin() + i, led);
					didInsert = 1;
					break;
				}

			}
			if (didInsert == 0) {
				//We didn't even add it  bc it was so big
				tanLeds.push_back(led);
			}

		} else {
			xLeds.push_back(led);
			yLeds.push_back(led);
			zLeds.push_back(led);
			phiLeds.push_back(led);
			tanLeds.push_back(led);
			addedOne = true;
			std::cout << "added one set" << std::endl;
		}		

		
	}
	//Now let's sort them
	std::cout << "meowAFTER" << std::endl;
	

}
void delay2(int idk) {
	for (int i = 0; i < idk; i += 2) {
		i--;
	}
}
using namespace std::chrono;
//returns 0 to 1 repeating, sawtooth wave
//period is in MILLISECONDS 
//1 second is 1e3 = 1000
double time(uint32_t period) {
	auto now = high_resolution_clock::now();
	uint32_t millis = duration_cast<milliseconds>(now.time_since_epoch()).count();
	//std::cout << (nanos / period) << std::endl;
	return ( double(millis % period) )/double(period);
}

using namespace std::chrono;
void run() {
	init();
	int32_t i = 0;
	uint32_t k = 0;
	uint32_t xled = 1200;
	uint32_t xled2 = 0;
	uint32_t yled = 1200;
	uint32_t yled2 = 0;
	uint32_t zled = 1200;
	uint32_t zled2 = 0;
	uint32_t mode = 0;
	uint32_t philed = 800;
	uint32_t philed2 = 0;
	uint32_t tanled = 1200;
	uint32_t tanled2 = 0;
	while (1) {
		
		if (dome->dataPipe) {
			dome->dataPipe = 0;
			mode += 1;
			mode %= 5;
		}
		
		i %= dome->totalLEDs;
		//k += i;
		k++;

		switch (mode) {
		case 0:
			philed++;
			philed2++;
			philed %= phiLeds.size();
			philed2 %= phiLeds.size();


			setLED(phiLeds[philed]->index, wheel(k / 10));
			setLED(phiLeds[philed2]->index, 0);
			break;
		case 1:
			xled++;
			xled2++;
			xled %= xLeds.size();
			xled2 %= xLeds.size();


			setLED(xLeds[xled]->index, wheel(k / 10));
			setLED(xLeds[xled2]->index, 0);
			break;
		case 2:
			yled++;
			yled2++;
			yled %= yLeds.size();
			yled2 %= yLeds.size();


			setLED(yLeds[yled]->index, wheel(k / 10));
			setLED(yLeds[yled2]->index, 0);
			break;
		case 3:
			zled++;
			zled2++;
			zled %= zLeds.size();
			zled2 %= zLeds.size();


			setLED(zLeds[zled]->index, wheel(k / 10));
			setLED(zLeds[zled2]->index, 0);
			break;
		case 4:
			tanled++;
			tanled2++;
			tanled %= tanLeds.size();
			tanled2 %= tanLeds.size();


			setLED(tanLeds[tanled]->index, wheel(k / 10));
			setLED(tanLeds[tanled2]->index, 0);
			break;

		
		}

		/*
		*/
		


		delay2(100000);
		//std::cout << time(10e3) << std::endl;
		//time(100);
		updateLEDs();
		
		//setLED(i, wheel(k));
		i++;
	}
}