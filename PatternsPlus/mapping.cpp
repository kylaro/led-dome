
#include "mapping.h"
#include <iostream>

float avg(float x, float y) {
	return (x + y) / 2;
}
float min(float x, float y) {
	if (x <= y) {
		return x;
	}
	else {
		return y;
	}
}

float Mapping::getEdgeY(int e) {
	return avg(dome->struts[e]->startNode->y, dome->struts[e]->endNode->y);//judge edge y based on lowest
}

float Mapping :: getEdgePhi(int e) {
	Strut* edge = dome->struts[e];
	//return atan2(edge->startNode->z, edge->startNode->x);
	return atan2( (edge->startNode->z+edge->endNode->z) , (edge->startNode->x+edge->endNode->x));;

}

float Mapping::getLEDPhi(LED* led) {
	return atan2(led->z, led->x);
}

float Mapping::getLEDPhi(int led) {
	//first need find the led's xyz
	LED* myled = getLEDObj(led);
	if (myled != NULL) {
		return getLEDPhi(myled);
	}
	
	return -420.69;
}

LED* Mapping::getLEDObj(int led) {
	for (LED* L : dome->leds) {
		if (L->index == led) {
			return L;
		}
	}
	return NULL;

}

bool Mapping::isClose(float x, float y) {
	float thresh = 33;
	if (x + y > 1500) {
		//thresh /= 2;
		//when looking at top of dome starting about y 750 the struts are closer together and we need do this.
	}
	bool closeness =  (x - y < thresh ) && ( x - y > -thresh);
	return closeness;
}

Mapping::Mapping(Dome* dome) {
	this->dome = dome;
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

			//35 billion dollars. thirty-phi
			size = phiLeds.size();
			didInsert = 0;
			float led_phi = 0;
			float philed_phi = 0;
			for (int i = 0; i < size; i++) {
				led_phi = getLEDPhi(led);//atan2(led->z, led->x);
				philed_phi = getLEDPhi(phiLeds[i]);//atan2(phiLeds[i]->z, phiLeds[i]->x);
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
	//Now let's do edges

	orderedEdges.push_back(0);
	for (int e = 1; e < dome->struts.size(); e++) {
		//We are essentially searching for this edges correct place in ordered edges
		//so let's go through orderedEdges
		float e_y = getEdgeY(e);
		float e_phi = getEdgePhi(e);
		//printf("%f phi", e_phi);
		bool didInsert = false;
		for (int oE = 0; oE < orderedEdges.size(); oE++) {
			float oE_y = getEdgeY(orderedEdges[oE]);
			float oE_phi = getEdgePhi(orderedEdges[oE]);//i know this is not needed most of thyme and could be later...

			//well the lowest one should be the first one, so let's say compare by y first
			if (isClose(e_y, oE_y)) {
				//they're like the same height so let's compare with phi
				if (e_phi < oE_phi) {
					orderedEdges.insert(orderedEdges.begin() + oE, e);
					break;
				}
			}else if (e_y < oE_y) {
				//well tht was easy and we are lower, so we need put it inf ront of this current edge.
				orderedEdges.insert(orderedEdges.begin() + oE, e);
				break;
			}
		}
		if (!didInsert) {
			orderedEdges.push_back(e);//it was meant to be here
		}

	}
	std::cout << "Finished Initializing :)" << std::endl;

}