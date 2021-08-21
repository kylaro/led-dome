#include "strut.h"


Strut::Strut() {
	this->letter = 4;//Not a real letter...
	this->index = -1;
}

Strut::Strut(Node* a, Node* b, int letter, int index) {
	this->startNode = a;
	this->endNode = b;
	this->letter = letter;//Not a real letter...
	this->index = index;
}


void Strut::generateLEDs(int start, int num) {
	this->numLEDs = num;
	this->startLED = start;
	this->endLED = start + num - 1;
	float padding = 10.0f; // make it so they don't perfectly intersect on the nodes
	
	float x_slope = (endNode->x - startNode->x) / ((float)numLEDs+padding);// +padding * numLEDs);
	float y_slope = (endNode->y - startNode->y) / ((float)numLEDs + padding);// + padding * numLEDs);
	float z_slope = (endNode->z - startNode->z) / ((float)numLEDs + padding);// + padding * numLEDs);

	leds.clear();
	for (int i = 0; i < numLEDs; i++) {
		LED * newLED = new LED(startLED + i);
		float x, y, z;
		x = (startNode->x)+x_slope*padding/2.0f + x_slope * i;
		y = startNode->y + y_slope * padding / 2.0f + y_slope * i;
		z = startNode->z + z_slope * padding / 2.0f + z_slope * i;
		newLED->setXYZ(x, y, z);
		leds.push_back(newLED);
	}
}