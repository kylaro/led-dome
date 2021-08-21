#ifndef MAPPING_H
#define MAPPING_H
#include "../Objects/dome.h"
#include "../Objects/LLnode.h"
#include <map>

class Mapping {

public:
	Mapping(Dome* theDome);
	Dome* dome;
	std::vector<LED*> xLeds;
	std::vector<LED*> yLeds;
	std::vector<LED*> zLeds;
	std::vector<LED*> phiLeds; // 1 side rotation
	std::vector<LED*> tanLeds; // 2 sided rotation
	std::vector<int> orderedEdges;
	float getEdgeY(int e);
	float getEdgePhi(int e);
	float getLEDPhi(int led);
	float getLEDPhi(LED* led);
	Strut* LEDtoStrut(LED* led);
	LED* getLEDObj(int led);
	std::vector<LLnode*> llnodes;
	std::map<int, std::vector<LLnode*>> llnodes_map;
	std::vector<Node* > nodesByY;

private:
	
	bool isClose(float x, float y);
	void LLnodeRecursive(LLnode* llnode);
	void generateLLnodes();
};

#endif