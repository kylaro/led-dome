#ifndef DOME_H
#define DOME_H

#include "graph.h"

class Dome : public Graph {
public:
	Dome();
	int totalLEDs = -1;
	std::vector<LED*> leds;
	int dataPipe = 0;
};


#endif