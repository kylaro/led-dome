
#include "mapping.h"
#include <iostream>

Mapping::Mapping(Dome* dome) {
	//Let's create the x y z led arrays
	std::cout << "Initializing Dome mappings..." << std::endl;
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
				led_phi = atan2(led->z, led->x);
				philed_phi = atan2(phiLeds[i]->z, phiLeds[i]->x);
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

		}
		else {
			xLeds.push_back(led);
			yLeds.push_back(led);
			zLeds.push_back(led);
			phiLeds.push_back(led);
			tanLeds.push_back(led);
			addedOne = true;

		}


	}
	//Now let's sort them
	std::cout << "Finished Initializing :)" << std::endl;

}