#ifndef MAPPING_H
#define MAPPING_H
#include "../Objects/dome.h"

class Mapping {

public:
	Mapping(Dome* theDome);
	std::vector<LED*> xLeds;
	std::vector<LED*> yLeds;
	std::vector<LED*> zLeds;
	std::vector<LED*> phiLeds; // 1 side rotation
	std::vector<LED*> tanLeds; // 2 sided rotation
	
	
};

#endif