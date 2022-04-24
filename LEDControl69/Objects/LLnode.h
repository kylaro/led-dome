#ifndef LLNODE_H
#define LLNODE_H

#include <vector>
#include "led.h"
#include "node.h"

class LLnode {
public:
	LLnode(LED* led);
	LLnode(LED* led, LLnode* prevNode, LLnode* nextNode);
	LLnode(LED* led, std::vector<LLnode*> prevNodes, LLnode* nextNode);
	LLnode(LED* led, LLnode* prevNode, std::vector<LLnode*> nextNodes);
	LED* led;
	LLnode* getNext();
	LLnode* getPrev();
	void setPrev(LLnode* prevNode);
	bool nodeImpact();
	int getStrutDir();
	int strutDir = 100;
	LLnode* getNextDir(int dir);
	int nextSize();
	int prevSize();
	void setNext(LLnode* nextNode);
	int myStrut = 0;
	int myNode = 0;
	Node* node;
	void setNode(Node* node);
	int whatNode();
	LLnode* strutPrev();
	LLnode* strutNext();
	LLnode* getNextHighest();
	LLnode* getNextLowest();
	LLnode* getNeighbor();
	LLnode* getNeighborOrThis();
	LLnode* getNeighborAngle(double angle);
	LLnode* getNeighborOrThisAngle(double angle);
	
	std::vector<LLnode*> nextHighest;
	LLnode* nextHighestOnStrut = NULL;
	std::vector<LLnode*> nextLowest;
	LLnode* nextLowestOnStrut = NULL;
	void addNeighbor(LLnode* nb);
	LLnode* myStrutNext = NULL;
	LLnode* myStrutPrev = NULL;
	bool isGood();
	std::vector<LLnode*> neighbors;//only nodes from other struts
private:
	std::vector<LLnode*> prevNodes;
	std::vector<LLnode*> nextNodes;
	

	


};




#endif