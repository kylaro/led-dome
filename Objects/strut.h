#ifndef STRUT_H
#define STRUT_H

#include "node.h"
#include "led.h"
#include <vector>
class Node;



class Strut {

public:
	Strut();
	Strut(Node * a, Node * b, int letter, int index);
	void reverseLEDs();
	void generateLEDs(int start, int num);
	void setStartLED(int start);
	//For now, let's have the paradigm be starting LED, and NUMBER of LED
	//this way we just adjust start, and NUM should be constant based on strut A B C or D
	int startLED;
	int endLED;
	int numLEDs;
	int reversed = 1;
	int dir = 1;
	std::vector<LED*> leds;

	Node* startNode;
	Node* endNode;
	int letter;
	int index;
	void regenLEDs();
	int confirmed = 0; //calibrated?
};

#endif