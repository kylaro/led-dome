#include "node.h"
#include "../PatternsPlus/helpers.h"
Node::Node(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}


//void Node::addNeighbor(Node* neighbor) {
//	neighborNodes.push_back(neighbor);

//}

void Node::addStrut(Strut* stert)
{
	struts.push_back(stert);
	LED* startLED = stert->leds[0];
	LED* endLED = stert->leds[stert->leds.size() - 1];
	if (distance3d(startLED->x, startLED->y, startLED->z, x, y, z) < distance3d(endLED->x, endLED->y, endLED->z, x, y, z)) {
		closestLEDs.push_back(startLED);
	}
	else {
		closestLEDs.push_back(endLED);
	}
}
