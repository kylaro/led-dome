#include "Pinwheel.h"

void Pinwheel::init() {
	do{
		nodeI = rand() % mapping->dome->nodes.size();
		node = mapping->dome->nodes[nodeI];
		selectedStrut = node->struts[0];
	} while (node->struts.size() == 0);
	
	initted = 1;
}

void Pinwheel::run() {
	angle = time(1000) * 6;// (node->struts.size());
	if (initted == 0) {
		init();
	}
	hsv_f hsv = { (rand()%10)/10.0,1,1 };
	rgb_f off = { 0,0,0 };
	//pick the strut
	angle = fmod(angle, node->struts.size());
	int strutI = angle;
	//turn on leds on the strut
	for (LED* led : selectedStrut->leds) {
		LEDs->setRGB(led->index, off);
	}
	
	selectedStrut = node->struts[strutI];
	double count = 0;
	for (LED* led : selectedStrut->leds) {

		count += 0.01;
		
		LEDs->setHSV(led->index,hsv);
	}

}

void Pinwheel::release() {
	done = 1;
	//turn off leds used...
}