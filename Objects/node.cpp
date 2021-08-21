#include "node.h"

Node::Node(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}


void Node::addNeighbor(Node* neighbor) {
	neighborNodes.push_back(neighbor);
	//awayStruts.push_back(new Strut());
	//towardStruts.push_back(new Strut());
}