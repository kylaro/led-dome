#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "strut.h"
#include <vector>
class Strut;
class Node;

class Graph {

	public:
		std::vector<Node*> nodes;
		std::vector<Strut*> struts;
		Node* createNode(float x, float y, float z);
		Strut* createStrut(Node* a, Node* b, int letter, int index);
};


#endif