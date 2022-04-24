#include "Firefly.h"

void Firefly::init() {
	//curNode = mapping->llnodes_map[mapping->nodesByY[0]->index][rand()%(mapping->llnodes_map[mapping->nodesByY[0]->index].size())];
	curNode = mapping->llnodes[rand() % mapping->llnodes.size()];
	prevNode = curNode;
	dir = 1;
	//curNode = mapping->llnodes[3000];
	//printf("%d\n", curNode->led->index);
	initted = 1;
	startTime = nowMillis();
	on = { 1,.26 + (rand() % 10) / 40.0,0 };
	//printf("%f\n", on.g);
	speed = rand() % 6 / 12.0 + 0.7;
}
void Firefly::release() {
	done = 1;
	rgb_f off = { 0,0,0 };
	for (int k = startIndex; k < lights.size(); k++) {
		LEDs->setRGB(lights[k].i, off);
	}
	lights.~vector();

}
void Firefly::run() {
	 
	if (initted == 0) {
		init();
	}

	//light up next one
	
	rgb_f off = { 0,0,0 };
	//LEDs->setRGB(curNode->led, off);
	//this should make it so they always travel in the direction of the struts, 
	gonext += speed;
	if (gonext > 1) {
		curNode = curNode->getNextDir(dir);
		if (curNode == NULL) {
			//this means we hit the end in this direction :)
			curNode = prevNode->getNeighbor();
			dir = curNode->getStrutDir();
		}
		//curNode = curNode->getNextDir(dir);

		if (speed < 0.07 ){//|| curNode == NULL || nowMillis() - startTime > 20000) {
			release();
			return;
		}
		prevNode = curNode;
		//LEDs->setRGB(curNode->led, on);
		irgb_f led = { curNode->led->index, on };
		lights.push_back(led);
		gonext = 0;
		speed *= 0.96;
	}
	
	for (int k = startIndex; k < lights.size(); k++) {
		irgb_f light = lights[k];
		if (lights[k].rgb.r < 0.01) {
			startIndex = k;
			LEDs->setRGB(light.i, off);
			continue;
		}
		LEDs->setRGB(light.i, light.rgb);
		lights[k].rgb.r *= 0.9;
		lights[k].rgb.g *= 0.86;//
		lights[k].rgb.b *= 0.8;
		
	}

}