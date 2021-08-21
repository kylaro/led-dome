#include "SwingingStrut.h"

void SwingingStrut::init() {
	node = mapping->nodesByY[0];
	curStrut = node->struts[rand() % node->struts.size()];
	color = rand() % 100;
	color /= 100.0;
	initted = 1;
}

void SwingingStrut::run() {
	if (initted == 0) {
		init();
	}
	//pick a strut 
	gonext += speed;
	hsv_f on = { color,1,1 };
	hsv_f off = { 0,0,0 };
	if (gonext > 1) {
		for (LED* led : curStrut->leds) {
			LEDs->setHSV(led->index, off);
		}
		//pick node that we are not at yet connected to this strut
		Node* nextNode;
		Strut* nextStrut;
		if (node->index == curStrut->startNode->index) {
			//currently on startnode so go end node
			nextNode = curStrut->endNode;
		}
		else {
			nextNode = curStrut->startNode;
		}
		nextStrut = nextNode->struts[rand() % nextNode->struts.size()];
		double count = 0;
		if (nextStrut->startNode->index == node->index) {
			for (LED* led : nextStrut->leds) {
				//count += 0.01;
				//on.v = 1 - count;
				LEDs->setHSV(led->index, on);
			}
		}
		else {
			for (int i = nextStrut->leds.size() - 1; i >= 0; i--) {
				LED* led = nextStrut->leds[i];
				LEDs->setHSV(led->index, on);
			}
		}

		curStrut = nextStrut;
		gonext = 0;
	}
	
}

void SwingingStrut::release() {
	done = 1;
	//turn off leds used...
}