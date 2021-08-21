#ifndef STRUT_H
#define STRUT_H

#include "node.h"
#include "led.h"
class Node;



class Strut {

public:
	Strut();
	Strut(Node * a, Node * b, int letter, int index);
	void generateLEDs(int start, int num);
	//For now, let's have the paradigm be starting LED, and NUMBER of LED
	//this way we just adjust start, and NUM should be constant based on strut A B C or D
	int startLED;
	int endLED;
	int numLEDs;
	int dir;
	std::vector<LED*> leds;

	Node* startNode;
	Node* endNode;
	int letter;
	int index;
};

#endif