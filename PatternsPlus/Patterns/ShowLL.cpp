#include "ShowLL.h"
#include "../helpers.h""
#include "../Effects/Firefly.h"

void ShowLL::run(bool real) {
	
	static LLnode* curNode = mapping->llnodes[0];
	static int flipflop = 0;
	static int curNode_i = 0;
	rgb_f rgb_off = { 0,0,0 };
	rgb_f rgb = { 1,1,1 };
	double time = triangle(100);
	int lastflipflop = flipflop;
	if (time > 0.5) {
		flipflop = 1;
	}
	if (time <= 0.5) {
		flipflop = 0;
	}
	int next = flipflop != lastflipflop;


	/*for (LLnode* llnode : mapping->llnodes) {
		if (llnode->nextSize() > 1 || llnode->prevSize() > 1) {
			rgb_f b = { 0,0,1 };
			ledInterface->setRGB(llnode->led, b);
		}
		if (llnode->getNext() == NULL) {
			rgb_f r = { 1,0,0 };
			ledInterface->setRGB(llnode->led, r);
		}
		if (llnode->getPrev() == NULL) {
			rgb_f r = { 0,1,0 };
			ledInterface->setRGB(llnode->led, r);
		}
	}*/
	
	if (next) {
		effectEngine->apply(new Firefly(ledInterface,shared->mapping));
		//printf("next\n");
		/*if (curNode == NULL) {
			curNode = mapping->llnodes[0];
		}
		ledInterface->setRGB(curNode->led, rgb_off);
		LLnode* lastnode = curNode;
		curNode = curNode->getNext();
		if (curNode == NULL) {
			curNode = mapping->llnodes[0];
		}
		ledInterface->setRGB(curNode->led, rgb);
		for (LLnode* llnode : mapping->llnodes) {
			if (llnode->getNext() == NULL) {
				rgb_f r = { 1,0,0 };
				ledInterface->setRGB(llnode->led,r);
			}
			if (llnode->getPrev() == NULL) {
				rgb_f r = { 0,1,0 };
				ledInterface->setRGB(llnode->led, r);
			}
		}*/
	}
	
}