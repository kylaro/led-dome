#include "Firework.h"
#include "HEXPulse.h"
#include "Shimmer.h"
void Firework::init() {

	startNode = mapping->bottomNodes[rand()%mapping->bottomNodes.size()];//one of the last 15
	curNode = mapping->llnodes_map[startNode->index][rand()% mapping->llnodes_map[startNode->index].size()];
	initted = 1;
	velocity = rand()%2+5;
	color = { (rand()%100)/100.0,0,1 };
}

void Firework::run() {
	if (initted == 0) {
		init();
	}
	rgb_f off = { 0,0,0 };
	if (done == 1) {
		return;
	}
	//dim trail
	for (int k = 0; k < trail.size(); k++) {
		trail[k].hsv.h += 0.005;
		trail[k].hsv.s += 0.15;
		trail[k].hsv.v *= 0.92;
		//ihsv_f ihsv = trail[k];
		LEDs->setHSV(trail[k].i, trail[k].hsv);
	}
	//light up curnode
	pos += velocity;
	velocity *= 0.97;
	if (velocity < 0.5) {
		velocity = 0.5;
	}
	
	while (pos > 1) {

		curNode = curNode->getNextHighest();
		
		LEDs->setHSV(curNode->led->index, color);
		ihsv_f add = { curNode->led->index, color };
		trail.push_back(add);
		pos -= 1;
		//int node;
		if ( velocity < 1.2 && curNode->nodeImpact()) {
			int node = curNode->whatNode();
			for (int i = 0; i < 160; i++) {
				Shimmer* shim = new Shimmer(LEDs, mapping);
				shim->duration = rand() % 600 + 50;
				Strut* stert = mapping->dome->nodes[node]->struts[rand() % mapping->dome->nodes[node]->struts.size()];
				shim->setStrut(stert);
				engine->queueApply(shim);
			}
			HEXPulse * pulse = new HEXPulse(LEDs, mapping);
			pulse->setNode(node);
			engine->queueApply(pulse);
			done = 1;
			
			release();
			return;
		}
	}
	

}

void Firework::release() {
	done = 1;
	rgb_f off = { 0,0,0 };
	//turn off leds used...
	for (ihsv_f h : trail) {
		LEDs->setRGB(h.i, off);
		
	}
}