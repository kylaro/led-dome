#ifndef MAPPING_H
#define MAPPING_H
#include "../Objects/dome.h"

class Mapping {

public:
	Mapping(Dome* theDome);
	Dome* dome;
	std::vector<LED*> xLeds;
	std::vector<LED*> yLeds;
	std::vector<LED*> zLeds;
	std::vector<LED*> phiLeds; // 1 side rotation
	std::vector<LED*> tanLeds; // 2 sided rotation
	std::vector<int> orderedEdges;
	float getEdgeY(int e);
	float getEdgePhi(int e);
	float getLEDPhi(int led);
	float getLEDPhi(LED* led);
	LED* getLEDObj(int led);
private:
	
	bool isClose(float x, float y);
};

#endif