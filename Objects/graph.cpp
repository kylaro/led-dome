#include "graph.h"
#include "strut.h"
#include "node.h"


Node* Graph::createNode(float x, float y, float z) {
	
	Node* newNode = new Node(x, y, z);
	nodes.push_back(newNode);
	
	return newNode;
}


Strut* Graph::createStrut(Node* a, Node* b, int letter, int index, int startLED) {
	Strut* newStrut = new Strut(a,b,letter, index);
	
	struts.push_back(newStrut);
	int numLEDs = 0;
	switch (letter) {
	case 0: //A
		numLEDs = 35;
		break;
	case 1: //B
		numLEDs = 42;
		break;
	case 2: //C
		numLEDs = 47;
		break;
	case 3: //D
		numLEDs = 49;
		break;
	}
	newStrut->generateLEDs(startLED, numLEDs);
	a->addStrut(newStrut);
	b->addStrut(newStrut);

	return newStrut;
}