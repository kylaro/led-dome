
#include "mapping.h"
#include <iostream>

float avg(float x, float y) {
	return (x + y) / 2;
}
float min(float x, float y) {
	if (x <= y) {
		return x;
	}
	else {
		return y;
	}
}

float Mapping::getEdgeY(int e) {
	return avg(dome->struts[e]->startNode->y, dome->struts[e]->endNode->y);//judge edge y based on lowest
}

float Mapping :: getEdgePhi(int e) {
	Strut* edge = dome->struts[e];
	//return atan2(edge->startNode->z, edge->startNode->x);
	return atan2( (edge->startNode->z+edge->endNode->z) , (edge->startNode->x+edge->endNode->x));;

}

float Mapping::getLEDPhi(LED* led) {
	return atan2(led->z, led->x);
}

float Mapping::getLEDPhi(int led) {
	//first need find the led's xyz
	LED* myled = getLEDObj(led);
	if (myled != NULL) {
		return getLEDPhi(myled);
	}
	
	return -420.69;
}

LED* Mapping::getLEDObj(int led) {
	for (LED* L : dome->leds) {
		if (L->index == led) {
			return L;
		}
	}
	return NULL;

}

bool Mapping::isClose(float x, float y) {
	float thresh = 33;
	if (x + y > 1500) {
		//thresh /= 2;
		//when looking at top of dome starting about y 750 the struts are closer together and we need do this.
	}
	bool closeness =  (x - y < thresh ) && ( x - y > -thresh);
	return closeness;
}

Strut * Mapping::LEDtoStrut(LED* led) {
	int ledI = led->index;
	for (Strut* strut : dome->struts) {
		if (ledI >= strut->startLED && ledI <= strut->endLED) {
			return strut;
		}
	}
	return NULL;
}

void Mapping::LLnodeRecursive(LLnode* llnode) {
	if (llnode->isGood()) {
		return;
	}
	else {
		LED* led = llnode->led;
		if (llnode->getNext() == NULL) {

		}
	}
}

void Mapping::generateLLnodes() {
	//2 options:
	//1 - i could loop through every LED and decide whos its neighboring LED and create nodes like this (slow slow)
	//2 - i could start somewhere and trace through the whole thing
	//LLnode* startNode = new LLnode(yLeds[0]);
	//LLnodeRecursive(startNode);
	//new option: loop through the struts and make it from those, they have start and end node all correct:)
	//make a list of nodes that's ordered from top to bottom... :)
	
	bool addedOne = false;
	for (Node* node : dome->nodes) {
		if (addedOne) {
			int size = nodesByY.size();
			int didInsert = 0;
			for (int i = 0; i < size; i++) {

				if (node->y < nodesByY[i]->y) {
					//if our current LED is lower, that means it is now in the right place
					nodesByY.insert(nodesByY.begin() + i, node);
					didInsert = 1;
					break;
				}

			}
			if (didInsert == 0) {
				//We didn't even add it  bc it was so big
				nodesByY.push_back(node);
			}
		}
		else {
			nodesByY.push_back(node);
		}
	}
	std::vector<int> doneStruts;
	for (Node* node : nodesByY) {
		for (Strut* strut : node->struts) {
			if (strut->confirmed == 0) {
				continue;
			}
			//If they have not been added yet
			int doneflag = 0;
			for (int i : doneStruts) {
				if (strut->index == i) {
					doneflag = 1;
					break;
				}
			}
			if (doneflag) {
				continue;
			}
			doneStruts.push_back(strut->index);
			//if (llnodes_map.count(strut->startNode->index) || llnodes_map.count(strut->endNode->index)) {
				//the only way a node is added to the llnodes map is if it has already run before in the loop
				//therefore this is now the case where this strut has definitely already been run before
				//so that means it already has existing llnodes
				//so we need to just connect it to the node that is looping right now
			//	if (llnodes_map.count(strut->startNode->index)) {
					//llnodes_map[strut->startNode->index].push_back()

			//	}
			//	continue;
			//}
			//need to go in correct direction...
			//find closestLED to node, and start from that side
			int reversed = 1;
			for (LED* led : node->closestLEDs) {
				if (led->index == strut->leds[0]->index) {
					reversed = 0;//start led
					break;
				}
				if (led->index == strut->leds[strut->leds.size() - 1]->index) {
					reversed = 1;//end led
					break;
				}
			}
			
			//if not reversed proceed normal
			if (reversed == 0) {
				LLnode* startLLnode = new LLnode(strut->leds[0]);// strut->leds[i]
				startLLnode->myStrut = strut->index;
				startLLnode->myNode = node->index;
				startLLnode->strutDir = 1;
				//this is the first node, it needs to be attached to all the other ones in this node
				
				for (LLnode* ll : llnodes_map[node->index]) {
					//startLLnode->setPrev(ll);
					//ll->setNext(startLLnode);
					startLLnode->addNeighbor(ll);
					ll->addNeighbor(startLLnode);
					
				}
				llnodes_map[node->index].push_back(startLLnode);
				
				llnodes.push_back(startLLnode);
				//the first one has been connected to previous and such
				LLnode* prevLLnode = startLLnode;
				LLnode* newLLnode;
				for (int i = 1; i < strut->leds.size() - 1; i++) {
					LED* led = strut->leds[i];
					newLLnode = new LLnode(led);
					newLLnode->strutDir = 0;
					newLLnode->myNode = node->index;
					newLLnode->myStrut = strut->index;
					newLLnode->setPrev(prevLLnode);
					prevLLnode->setNext(newLLnode);
					
					llnodes.push_back(newLLnode);
					prevLLnode = newLLnode;
				}
				LLnode* lastLLnode = new LLnode(strut->leds[strut->leds.size() - 1]);
				lastLLnode->myStrut = strut->index;
				lastLLnode->strutDir = -1;
				lastLLnode->myNode = node->index;
				lastLLnode->setPrev(newLLnode);
				newLLnode->setNext(lastLLnode);
				if (node->index == strut->startNode->index) {
					//this means the last node is the endnode
					for (LLnode* llnode : llnodes_map[strut->endNode->index]) {
						//llnode->setPrev(lastLLnode);
						//lastLLnode->setNext(llnode);
						llnode->addNeighbor(lastLLnode);
						lastLLnode->addNeighbor(llnode);
					}
					llnodes_map[strut->endNode->index].push_back(lastLLnode);
					//printf("1");
				}
				else {
					for (LLnode* llnode : llnodes_map[strut->startNode->index]) {
						//llnode->setPrev(lastLLnode);
						//lastLLnode->setNext(llnode);
						llnode->addNeighbor(lastLLnode);
						lastLLnode->addNeighbor(llnode);
					}
					llnodes_map[strut->startNode->index].push_back(lastLLnode);
					//printf("2");
				}
				llnodes.push_back(lastLLnode);
				
			}
			else {
				//REVERSED CODE HERE
				//....
				LLnode* startLLnode = new LLnode(strut->leds[strut->leds.size()-1]);// strut->leds[i]
				//this is the first node, it needs to be attached to all the other ones in this node
				startLLnode->myNode = node->index;
				startLLnode->myStrut = strut->index;
				startLLnode->strutDir = 1;
				for (LLnode* ll : llnodes_map[node->index]) {
					//startLLnode->setPrev(ll);
					//ll->setNext(startLLnode);
					startLLnode->addNeighbor(ll);
					ll->addNeighbor(startLLnode);
				}
				llnodes_map[node->index].push_back(startLLnode);

				llnodes.push_back(startLLnode);
				//the first one has been connected to previous and such
				LLnode* prevLLnode = startLLnode;
				LLnode* newLLnode;
				for (int i = strut->leds.size()-2; i >= 1; i--) {
					LED* led = strut->leds[i];
					newLLnode = new LLnode(led);
					newLLnode->myNode = node->index;
					newLLnode->strutDir = 0;
					newLLnode->myStrut = strut->index;
					newLLnode->setPrev(prevLLnode);
					prevLLnode->setNext(newLLnode);

					llnodes.push_back(newLLnode);
					prevLLnode = newLLnode;
				}
				LLnode* lastLLnode = new LLnode(strut->leds[0]);
				lastLLnode->myStrut = strut->index;
				lastLLnode->myNode = node->index;
				lastLLnode->strutDir = -1;
				lastLLnode->setPrev(newLLnode);
				newLLnode->setNext(lastLLnode);
				if (node->index == strut->startNode->index) {
					//this means the last node is the endnode
					for (LLnode* llnode : llnodes_map[strut->endNode->index]) {
						//llnode->setPrev(lastLLnode);
						//lastLLnode->setNext(llnode);
						llnode->addNeighbor(lastLLnode);
						lastLLnode->addNeighbor(llnode);
					}
					llnodes_map[strut->endNode->index].push_back(lastLLnode);
					//printf("3");
				}
				else {
					for (LLnode* llnode : llnodes_map[strut->startNode->index]) {
						//llnode->setPrev(lastLLnode);
						//lastLLnode->setNext(llnode);
						llnode->addNeighbor(lastLLnode);
						lastLLnode->addNeighbor(llnode);
					}
					llnodes_map[strut->startNode->index].push_back(lastLLnode);
					//printf("4");
				}
				llnodes.push_back(lastLLnode);
				
			}
			
			//last one still needs be handled



			
		}
	}
	//
	//for (LLnode * llnode : llnodes) {
		//gonna repair the ones that have no nexts..
		//printf("%d %d\n", llnode->nextSize(), llnode->prevSize());
		/*if (llnode->getNext() == NULL) {

			//printf("no next%d\n",llnode->led->index);
			llnode->setNext(llnode->getPrev());
		}
		if (llnode->getPrev() == NULL) {
			//printf("no prev%d\n", llnode->led->index);
			llnode->setPrev(llnode->getNext());
		}*/
	//}
	printf("LLnodes=%d\n#leds=%d\n", llnodes.size(), dome->leds.size());

}

Mapping::Mapping(Dome* dome) {
	this->dome = dome;
	//Let's create the x y z led arrays
	std::cout << "Initializing Dome mappings..." << std::endl;

	bool addedOne = false;
	for (LED* led : dome->leds) {
		if (addedOne) {
			int size = xLeds.size();
			int didInsert = 0;
			for (int i = 0; i < size; i++) {

				if (led->x < xLeds[i]->x) {
					//if our current LED is lower, that means it is now in the right place
					xLeds.insert(xLeds.begin() + i, led);
					didInsert = 1;
					break;
				}

			}
			if (didInsert == 0) {
				//We didn't even add it  bc it was so big
				xLeds.push_back(led);
			}

			size = yLeds.size();
			didInsert = 0;
			for (int i = 0; i < size; i++) {
				if (led->y < yLeds[i]->y) {
					//if our current LED is lower, that means it is now in the right place
					yLeds.insert(yLeds.begin() + i, led);
					didInsert = 1;
					break;
				}

			}
			if (didInsert == 0) {
				//We didn't even add it  bc it was so big
				yLeds.push_back(led);
			}

			size = zLeds.size();
			didInsert = 0;
			for (int i = 0; i < size; i++) {
				if (led->z < zLeds[i]->z) {
					//if our current LED is lower, that means it is now in the right place
					zLeds.insert(zLeds.begin() + i, led);
					didInsert = 1;
					break;
				}

			}
			if (didInsert == 0) {
				//We didn't even add it  bc it was so big
				zLeds.push_back(led);
			}

			//35 billion dollars. thirty-phi
			size = phiLeds.size();
			didInsert = 0;
			float led_phi = 0;
			float philed_phi = 0;
			for (int i = 0; i < size; i++) {
				led_phi = getLEDPhi(led);//atan2(led->z, led->x);
				philed_phi = getLEDPhi(phiLeds[i]);//atan2(phiLeds[i]->z, phiLeds[i]->x);
				if (led_phi < philed_phi) {
					//if our current LED is lower, that means it is now in the right place
					phiLeds.insert(phiLeds.begin() + i, led);
					didInsert = 1;
					break;
				}

			}
			if (didInsert == 0) {
				//We didn't even add it  bc it was so big
				phiLeds.push_back(led);
			}


			//35 billion dollars
			size = tanLeds.size();
			didInsert = 0;
			led_phi = 0;
			philed_phi = 0;
			for (int i = 0; i < size; i++) {
				led_phi = atan(led->z / led->x);
				philed_phi = atan(tanLeds[i]->z / tanLeds[i]->x);
				if (led_phi < philed_phi) {
					//if our current LED is lower, that means it is now in the right place
					tanLeds.insert(tanLeds.begin() + i, led);
					didInsert = 1;
					break;
				}

			}
			if (didInsert == 0) {
				//We didn't even add it  bc it was so big
				tanLeds.push_back(led);
			}

		}
		else {
			xLeds.push_back(led);
			yLeds.push_back(led);
			zLeds.push_back(led);
			phiLeds.push_back(led);
			tanLeds.push_back(led);
			addedOne = true;

		}
	}
	//Now let's do edges

	orderedEdges.push_back(0);
	for (int e = 1; e < dome->struts.size(); e++) {
		//We are essentially searching for this edges correct place in ordered edges
		//so let's go through orderedEdges
		float e_y = getEdgeY(e);
		float e_phi = getEdgePhi(e);
		//printf("%f phi", e_phi);
		bool didInsert = false;
		for (int oE = 0; oE < orderedEdges.size(); oE++) {
			float oE_y = getEdgeY(orderedEdges[oE]);
			float oE_phi = getEdgePhi(orderedEdges[oE]);//i know this is not needed most of thyme and could be later...

			//well the lowest one should be the first one, so let's say compare by y first
			if (isClose(e_y, oE_y)) {
				//they're like the same height so let's compare with phi
				if (e_phi < oE_phi) {
					orderedEdges.insert(orderedEdges.begin() + oE, e);
					break;
				}
			}else if (e_y < oE_y) {
				//well tht was easy and we are lower, so we need put it inf ront of this current edge.
				orderedEdges.insert(orderedEdges.begin() + oE, e);
				break;
			}
		}
		if (!didInsert) {
			orderedEdges.push_back(e);//it was meant to be here
		}

	}

	generateLLnodes();


	std::cout << "Finished Initializing :)" << std::endl;

}