#include "Raindrop.h"

void Raindrop::init() {
	//curNode = mapping->llnodes_map[mapping->nodesByY[0]->index][rand()%(mapping->llnodes_map[mapping->nodesByY[0]->index].size())];
	curNode = mapping->llnodes_map[mapping->nodesByY[0]->index][rand()% mapping->llnodes_map[mapping->nodesByY[0]->index].size()];
	prevNode = curNode;
	dir = 1;
	//curNode = mapping->llnodes[3000];
	//printf("%d\n", curNode->led->index);
	initted = 1;
	startTime = nowMillis();
	//on = { 0,0,1 };
	//printf("%f\n", on.g);
	speed = rand() % 12 / 12.0 + 1;
}
void Raindrop::release() {
	done = 1;
	rgb_f off = { 0,0,0 };
	for (int k = startIndex; k < lights.size(); k++) {
		LEDs->setRGB(lights[k].i, off);
	}
	lights.~vector();

}
void Raindrop::run() {

	if (initted == 0) {
		init();
	}

	//light up next one

	rgb_f off = { 0,0,0 };
	//LEDs->setRGB(curNode->led, off);
	//this should make it so they always travel in the direction of the struts, 
	gonext += speed;
	if (gonext > 1) {
		curNode = curNode->getNextLowest();
		if (curNode == NULL) {
			done = 1;
			return;
			//this means we hit the end in this direction :)
			curNode = prevNode->getNextLowest();
			//dir = curNode->getStrutDir();
		}
		
		//curNode = curNode->getNextDir(dir);

		if (speed < 0.07) {//|| curNode == NULL || nowMillis() - startTime > 20000) {
			release();
			return;
		}
		prevNode = curNode;
		//LEDs->setRGB(curNode->led, on);
		irgb_f led = { curNode->led->index, on };
		lights.push_back(led);
		gonext = 0;
		speed *= 1.05;
	}

	for (int k = startIndex; k < lights.size(); k++) {
		irgb_f light = lights[k];
		if (lights[k].rgb.b+ lights[k].rgb.g+ lights[k].rgb.r < 0.03) {
			startIndex = k;
			LEDs->setRGB(light.i, off);
			continue;
		}
		LEDs->setRGB(light.i, light.rgb);
		lights[k].rgb.r *= 0.5;
		lights[k].rgb.g *= 0.5;//
		lights[k].rgb.b *= 0.5;

	}

}