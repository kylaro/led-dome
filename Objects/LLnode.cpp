#include "LLnode.h"
#include "../PatternsPlus/vectormath.h"
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

//return 1 if impact, 0 if not
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



LLnode* LLnode::getNextLowest() {
	if (nextLowestOnStrut != NULL) {
		return nextLowestOnStrut;
	}
	if (nextLowest.size() > 0) {
		return nextLowest[rand() % nextLowest.size()];
	}
	
	LLnode* lowest = this;
	double lowest_y = lowest->led->y;
	

	for (LLnode* next : nextNodes) {
		if (next->led->y < lowest_y) {
			nextLowest.push_back(next);
			//highest = next;
			//highest_y = next->led->y;
		}
	}
	for (LLnode* next : prevNodes) {
		if (next->led->y < lowest_y) {
			nextLowest.push_back(next);
			//highest = next;
			//highest_y = next->led->y;
		}
	}
	for (LLnode* next : neighbors) {
		if (next->led->y < this->node->y) {
			nextLowest.push_back(next);
		}
		if (next->led->y < lowest_y) {//ben
			nextLowest.push_back(next);
			//uncommment this for correctness
		}
	}
	
	for (LLnode* llnode : nextLowest) {
		if (llnode->myStrut == myStrut) {
			nextLowestOnStrut = llnode;
			return llnode;
		}
	}
	if (nextLowest.size() == 0) {
		return NULL;
	}
	return nextLowest[rand() % nextLowest.size()];
}


LLnode* LLnode::getNeighborOrThis() {
	if (neighbors.size() > 0) {
		if (rand() % (neighbors.size() + 1) == 0) {
			return this;
		}
		return this->neighbors[rand() % neighbors.size()];
	}
	return this;
}
LLnode* LLnode::getNeighbor() {
	if (neighbors.size() > 0) {
		return this->neighbors[rand() % neighbors.size()];
	}
	return NULL;
}

LLnode* LLnode::getNeighborOrThisAngle(double angle)
{
	xyz_f targetP = this->led->xyz;
	xy_f xy = projectPoint(this->node->xyz, targetP);

	double smallestDiff2 = 100;
	LLnode* selectedNext = NULL;

	double neighborAngle = atan2(xy.y, xy.x);
	double diff = wrappedDist(angle, neighborAngle, 3.141593);
	if (diff < smallestDiff2) {
		smallestDiff2 = diff;
		selectedNext = this;
	}

	for (LLnode* neighbor : neighbors) {
		targetP = neighbor->led->xyz;
		//double x = dot(vex, subtract(targetP, pp));
		//double y = dot(vey, subtract(targetP, pp));
		xy = projectPoint(this->node->xyz, targetP);
		//can get angle from these
		double neighborAngle = atan2(xy.y, xy.x);
		double diff = wrappedDist(angle, neighborAngle, 3.141593);
		if (diff < smallestDiff2) {
			smallestDiff2 = diff;
			selectedNext = neighbor;
		}
	}

	return selectedNext;
}
LLnode* LLnode::getNeighborAngle(double angle)
{
	
	/*xyz_f pp = this->node->xyz;
	if (pp.x == 0 && pp.z == 0) {
		//special case for top node
		pp.z = -1;
	}
	xyz_f po = { 0,pp.y - 200,0 };
	xyz_f vn = subtract(pp, po);
	xyz_f voo = { po.x - pp.x, 0, po.z - pp.z };
	normalize(&vn);
	normalize(&voo);
	xyz_f voy = voo;
	//normalize(&oo);
	getOrthogVec(vn, &voy, 'y');
	normalize(&voy);
	xyz_f vey = voy;// subtract(voy, p);
	xyz_f vex = cross(vn, vey);
	normalize(&vey);
	normalize(&vex);*/
	double smallestDiff2 = 100;
	LLnode* selectedNext = NULL;

	for (LLnode* neighbor : neighbors) {
		xyz_f targetP = neighbor->led->xyz;
		//double x = dot(vex, subtract(targetP, pp));
		//double y = dot(vey, subtract(targetP, pp));
		xy_f xy = projectPoint(this->node->xyz, targetP);
		//can get angle from these
		double neighborAngle = atan2(xy.y, xy.x);
		double diff = wrappedDist(angle, neighborAngle, 3.141593);
		if (diff < smallestDiff2) {
			smallestDiff2 = diff;
			selectedNext = neighbor;
		}
	}
	
	return selectedNext;
	/*LLnode* selectedNeighbor = getNeighbor();
	//let's do this with spherical coordinates...
	xyz_f myXYZ = this->led->xyz;
	xyz_f origin = { 0,400,0 };
	xyz_f normal = subtract(myXYZ, origin);
	sph_f mySPH = getSpherical(normal);
	double smallestDiff = 100;
	for (LLnode* neighbor : neighbors) {
		sph_f neighSPH = getSpherical(neighbor->led->xyz);
		double thetaAdd = cos(angle);
		double phiAdd = sin(angle);
		double diff = thetaAdd - (mySPH.theta - neighSPH.theta) + phiAdd - (mySPH.phi - neighSPH.theta);
		if (diff < smallestDiff) {
			smallestDiff = diff;
			selectedNeighbor = neighbor;
		}
	}
	return selectedNeighbor;*/
	/*
	xyz_f myXYZ = this->node->xyz;
	xyz_f neighborXYZ;
	double smallestDiff = 1000;
	LLnode* selectedNeighbor = getNeighbor();
	xyz_f origin = { 0,400,0 };
	xyz_f normal = { myXYZ.x - origin.x, myXYZ.y - origin.y, myXYZ.z - origin.z };
	normalize(&normal);
	xyz_f e_1x = { 1,0,0 };
	xyz_f e_1y = { 0,1,0 };
	getOrthogVec(normal, &e_1x, 'z');
	getOrthogVec(normal, &e_1y, 'z');
	normalize(&e_1x);
	normalize(&e_1y);
	for (LLnode* neighbor : neighbors) {*/
		/*xyz_f targetP = neighbor->led->xyz;
		double x = dot(e_1x, subtract(targetP, origin));
		double y = dot(e_1y, subtract(targetP, origin));
		//can get angle from these
		double neighborAngle = atan2(y, x);
		double diff = wrappedDist(angle, neighborAngle, 3.141593);
		if (diff < smallestDiff) {
			smallestDiff = diff;
			selectedNeighbor = neighbor;
		}*/

		/*
		neighborXYZ = neighbor->led->xyz;
		double yDiff = myXYZ.y - neighborXYZ.y;
		double xDiff = myXYZ.x - neighborXYZ.x;
		double zDiff = myXYZ.z - neighborXYZ.z;
		double neighborAngle = atan2(zDiff, xDiff);
		double thisDiff = fabs(angle - neighborAngle);
		if (thisDiff < smallestDiff) {
			selectedNeighbor = neighbor;
			smallestDiff = thisDiff;
		}
		
	}
	return selectedNeighbor;*/
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
