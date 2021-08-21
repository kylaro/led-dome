#include "HEXPulse.h"
void HEXPulse::init() {

}
void HEXPulse::run() {
	static int init = 0;
	if (init == 0) {

	}
	int node = std::rand() % mapping->dome->nodes.size();
	static float h = 0;
	static float s = 0;
	static float v = 0;
	Node* myNode = mapping->dome->nodes[node];
	int time = nowMillis();
	printf("XDwow%d\n",node);
	for (Strut * strut : myNode->struts) {
		double count = 0;
		for (LED* led : strut->leds) {
			count++;
			if (count > 50) {
				printf("fuckme");
			}
			count = fmod(count, 100);
			LEDs->setRGB(led,count/50.0 , .4, .4);
		}
	}
	done = 1;

}