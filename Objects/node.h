#ifndef NODE_H
#define NODE_H

#include "strut.h"
#include "led.h"
#include <vector>
#include "../PatternsPlus/positioning.h"
//class Node; // this was here but not sturt
class Strut;


class Node {
public:
	Node(float x, float y, float z);
	//void addNeighbor(Node* neighbor);
	void addStrut(Strut* stert);
	//std::vector<Strut*> awayStruts;
	//std::vector<Strut*> towardStruts;
	//std::vector<Node*> neighborNodes;
	std::vector<Strut*> struts;
	std::vector<LED*> closestLEDs;
	float x;
	float y;
	float z;
	xyz_f xyz;
	int index;
};



#endif