#ifndef NODE_H
#define NODE_H

//#include "strut.h"
#include <vector>
class Node; // this was here but not sturt
//class Strut;


class Node {
public:
	Node(float x, float y, float z);
	void addNeighbor(Node* neighbor);
	//std::vector<Strut*> awayStruts;
	//std::vector<Strut*> towardStruts;
	std::vector<Node*> neighborNodes;
	float x;
	float y;
	float z;
	int index;
};



#endif