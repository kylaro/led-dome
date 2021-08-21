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
	LLnode* getNeighbor();
	LLnode* getNeighborAngle(double angle);
	double magnitude(xyz_f xyz);
	void normalize(xyz_f* xyz);
	xyz_f subtract(xyz_f xyz1, xyz_f xyz2);
	double dot(xyz_f xyz1, xyz_f xyz2);
	xyz_f cross(xyz_f a, xyz_f b);
	void getOrthogVec(xyz_f xyz, xyz_f* ortho, char xyorz);
	double wrappedDist(double x, double y, double wrap);
	sph_f getSpherical(xyz_f xyz);
	std::vector<LLnode*> nextHighest;
	LLnode* nextHighestOnStrut = NULL;
	void addNeighbor(LLnode* nb);
	LLnode* myStrutNext = NULL;
	LLnode* myStrutPrev = NULL;
	bool isGood();
private:
	std::vector<LLnode*> prevNodes;
	std::vector<LLnode*> nextNodes;
	std::vector<LLnode*> neighbors;//only nodes from other struts

	


};




#endif