#include "strut.h"


Strut::Strut() {
	this->letter = 4;//Not a real letter...
	this->index = -1;
}

Strut::Strut(Node* a, Node* b, int letter, int index) {
	this->startNode = a;//xyz position starts at startnode, so should startled
	this->endNode = b;
	this->letter = letter;//Not a real letter...
	this->index = index;
}
void Strut::reverseLEDs() {
	for (int i = 0; i < leds.size() / 2; i++) {
		int swapindex = leds[i]->index;
		leds[i]->index = leds[leds.size() - 1 - i]->index;
		leds[leds.size() - 1 - i]->index = swapindex;
	}
	//int swapi = startLED;
	//startLED = endLED;
	//endLED = swapi;
	//printf("rev");
	//if(reverseLED)
	dir = -1;
}
void Strut::regenLEDs() {
	this->endLED = startLED + numLEDs-1;
	
	for (int i = 0; i < leds.size(); i++) {
		leds[i]->index = startLED + i;
		leds[i]->confirmed = this->confirmed;
	}
	if (reversed) {
		reverseLEDs();
	}

}


void Strut::generateLEDs(int start, int num) {
	this->numLEDs = num;
	this->startLED = start;
	this->endLED = start + num - 1;
	float padding = 5.0f; // make it so they don't perfectly intersect on the nodes
	
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


void Strut::setStartLED(int start) {
	startLED = start;
	endLED = start + numLEDs;
	for (int i = 0; i < numLEDs; i++) {
		leds[i]->index = start + i;
	}


}