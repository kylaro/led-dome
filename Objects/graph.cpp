#include "graph.h"
#include "strut.h"
#include "node.h"


Node* Graph::createNode(float x, float y, float z) {
	
	Node* newNode = new Node(x, y, z);
	nodes.push_back(newNode);
	
	return newNode;
}


Strut* Graph::createStrut(Node* a, Node* b, int letter, int index) {
	Strut* newStrut = new Strut(a,b,letter, index);
	struts.push_back(newStrut);

	return newStrut;
}