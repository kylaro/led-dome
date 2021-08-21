#include "LLnode.h"

bool LLnode::isGood() {
	return (this->prevNodes.size() > 0) && (this->nextNodes.size() > 0);
}

LLnode::LLnode(LED* led) {
	//start them all as null
	this->led = led;
}

LLnode::LLnode(LED* led, LLnode* prevNode, LLnode* nextNode)
{
	this->prevNodes.push_back(prevNode);
	this->nextNodes.push_back(nextNode);
	this->led = led;

}

LLnode::LLnode(LED* led, std::vector<LLnode*> prevNodes, LLnode* nextNode)
{
	for (LLnode* ll : prevNodes) {
		this->prevNodes.push_back(ll);
	}
	this->nextNodes.push_back(nextNode);
	this->led = led;
}

LLnode::LLnode(LED* led, LLnode* prevNode, std::vector<LLnode*> nextNodes)
{
	
	this->prevNodes.push_back(prevNode);
	
	for (LLnode* ll : prevNodes) {
		this->nextNodes.push_back(ll);
	}
	this->led = led;
}
int LLnode::nextSize() {
	return nextNodes.size();
}
int LLnode::prevSize() {
	return prevNodes.size();
}
void LLnode::addNeighbor(LLnode* nb) {
	for (LLnode* ll : neighbors) {
		if (ll->led->index == nb->led->index) {
			//it's already added so don't add it again
			return;
		}
	}
	neighbors.push_back(nb);
}
void LLnode::setNext(LLnode* nextNode) {
	for (LLnode* node : nextNodes) {
		if (node->led->index == nextNode->led->index) {
			//this is duplicate
			return;
		}
	}
	for (LLnode* node : prevNodes) {
		if (node->led->index == nextNode->led->index) {
			//this is duplicate
			return;
		}
	}
	this->nextNodes.push_back(nextNode);
}
void LLnode::setPrev(LLnode* prevNode) {
	for (LLnode* node : prevNodes) {
		if (node->led->index == prevNode->led->index) {
			//this is duplicate
			return;
		}
	}
	for (LLnode* node : nextNodes) {
		if (node->led->index == prevNode->led->index) {
			//this is duplicate
			return;
		}
	}
	this->prevNodes.push_back(prevNode);
}
bool LLnode::nodeImpact() {
	return neighbors.size() > 0;// nextNodes.size() > 1 || prevNodes.size() > 1;
}

int LLnode::whatNode() {
	return myNode;
}

LLnode* LLnode::strutPrev() {
	if (myStrutPrev == NULL) {
		for (LLnode* ll : prevNodes) {
			if (ll->myStrut == myStrut) {
				myStrutPrev = ll;
				return ll;
			}
		}
		for (LLnode* ll : nextNodes) {
			if (ll->myStrut == myStrut) {
				myStrutPrev = ll;
				return ll;
			}
		}
		//if we got here we never found one :c
		printf("didn't find prev node\n");
		return NULL;
	}
	else {
		return myStrutPrev;
	}
}
LLnode* LLnode::strutNext() {
	if (myStrutNext == NULL) {
		for (LLnode* ll : nextNodes) {
			if (ll->myStrut == myStrut) {
				myStrutNext = ll;
				return ll;
			}
		}
		for (LLnode* ll : prevNodes) {
			if (ll->myStrut == myStrut) {
				myStrutNext = ll;
				return ll;
			}
		}

		printf("didn't find next node\n");
		return NULL;
	}
	else {
		return myStrutNext;
	}
	
}

void LLnode::setNode(Node * node) {
	myNode = node->index;
	this->node = node;
}

LLnode* LLnode::getNextHighest() {
	if (nextHighestOnStrut != NULL) {
    		return nextHighestOnStrut;
	}
	if (nextHighest.size() > 0) {
		return nextHighest[rand() % nextHighest.size()];
	}
	LLnode* highest = this;
	double highest_y = highest->led->y;
	/*
	if ( nodeImpact()) {
		if (this->led->y < this->node->y) {
			highest_y = this->node->y;
		}
		else {
			highest_y = this->led->y;
		}
		
	}*/
	
	for (LLnode* next : nextNodes) {
		if (next->led->y > highest_y) {
			nextHighest.push_back(next);
			//highest = next;
			//highest_y = next->led->y;
		}
	}
	for (LLnode* next : prevNodes) {
		if (next->led->y > highest_y) {
			nextHighest.push_back(next);
			//highest = next;
			//highest_y = next->led->y;
		}
	}
	for (LLnode* next : neighbors) {
		if (next->led->y > this->node->y) {
			nextHighest.push_back(next);
		}
		if (next->led->y > highest_y) {
			//nextHighest.push_back(next);
			//uncommment this for correctness
		}
	}
	//nextHighest = highest;
	/*
	std::vector<LLnode*>::iterator it = nextHighest.begin();
	while (it != nextHighest.end())
	{
		LLnode* llnode = *it;
		if (llnode->getNext() != NULL) {
			if (llnode->getNext()->led->y < llnode->led->y) {
				//it is rip, this one should be removed
				it = nextHighest.erase(it);
				//free(eff);
				continue;
			}
			else {
				it++;
			}
		}
		else if (llnode->getPrev() != NULL) {
			if (llnode->getPrev()->led->y < llnode->led->y) {
				//it is rip, this one should be removed
				it = nextHighest.erase(it);
				//free(eff);
				continue;
			}
			else {
				it++;
			}
		}
		else {
			printf("We're going to have a problem here..\n");
		}
	}*/

	for (LLnode* llnode : nextHighest) {
		if (llnode->myStrut == myStrut) {
			nextHighestOnStrut = llnode;
			return llnode;
		}
	}
	
       	return nextHighest[rand()%nextHighest.size()];
}

LLnode* LLnode::getNeighbor() {
	if (neighbors.size() > 0) {
		return this->neighbors[rand() % neighbors.size()];
	}
	return NULL;
}

//NEXT is 1
//PREV is -1
//BOTH is 0
int LLnode::getStrutDir() {
	return strutDir;
	if (strutDir > 1) {
		if (nextNodes.size() == 1 && prevNodes.size() == 1) {
			strutDir = 0;
			return 0;
		}
		for (LLnode* ll : nextNodes) {
			if (ll->myStrut == myStrut) {
				//ah ye must be the right way,
				strutDir = 1;
				return 1;
			}
		}
		for (LLnode* ll : prevNodes) {
			if (ll->myStrut == myStrut) {
				//ah ye must be the right way,
				strutDir = -1;
				return -1;
			}
		}
	}
	else {
		return strutDir;
	}

	return 0;
	if (nextNodes.size() > 1 && prevNodes.size() > 1) {
		printf("%d\t%d\n", nextNodes.size(), prevNodes.size());
	}
	if (this->nextNodes.size() == 1 && this->prevNodes.size() == 1) {
		return 0;
	}
	else if (this->nextNodes.size() == 1) {
		return 1;
	}
	else {
		return -1;//previous node is travel along strut
	}
}

LLnode* LLnode::getNextDir(int dir) {
	if (dir == 1) {
		return getNext();
	}
	if (dir == 0) {
		return this;
	}
	if (dir == -1) {
		return getPrev();
	}
	printf("dir=%d\n", dir);
}

LLnode* LLnode::getNext()
{	
	
	if (nextNodes.size() == 0) {
		return NULL;
	}
	return(nextNodes[0]);
	return this->nextNodes[rand()%nextNodes.size()];
}

LLnode* LLnode::getPrev()
{
	if (prevNodes.size() == 0) {
		return NULL;
	}
	return(prevNodes[0]);
	return this->prevNodes[rand() % prevNodes.size()];
}
