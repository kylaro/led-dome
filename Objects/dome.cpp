#include "graph.h"
#include "dome.h"
#include <iostream>
#define NUM_VERTICES 65 // 65
#define NUM_EDGES 171 // 171

float vertices[NUM_VERTICES][3] = { {0.0, 1187.6, 0.0},{100.5, 1133.2, 309.3},{491.1, 982.3, 356.8},{216.4, 901.4, 666.1},{800.9, 700.4, 309.3},{541.6, 700.4, 666.1},{276.4, 634.8, 850.7},{794.7, 375.2, 577.4},{479.5, 375.2, 857.2},{115.9, 375.2, 975.4},{667.1, 0.0, 721.0},{303.5, 0.0, 934.2},{-115.9, 0.0, 975.4},{-263.1, 1133.2, 191.2},{-187.6, 982.3, 577.3},{-566.6, 901.4, 411.6},{-46.7, 700.4, 857.3},{-466.1, 700.4, 720.9},{-723.7, 634.8, 525.8},{-303.6, 375.2, 934.2},{-667.1, 375.2, 720.9},{-891.8, 375.2, 411.6},{-479.6, 0.0, 857.3},{-794.7, 0.0, 577.3},{-963.5, 0.0, 191.2},{0.0, 0.0, 0.0},{-263.1, 1133.2, -191.2},{-607.0, 982.3, 0.0},{-566.6, 901.4, -411.7},{-829.7, 700.4, 220.5},{-829.7, 700.4, -220.5},{-723.6, 634.8, -525.8},{-982.3, 375.2, 0.0},{-891.8, 375.2, -411.6},{-667.1, 375.2, -721.0},{-963.5, 0.0, -191.2},{-794.6, 0.0, -577.4},{-479.6, 0.0, -857.2},{0.0, 0.0, 0.0},{100.5, 1133.2, -309.3},{-187.6, 982.3, -577.3},{216.5, 901.4, -666.1},{-466.1, 700.4, -721.0},{-46.6, 700.4, -857.2},{276.4, 634.8, -850.7},{-303.5, 375.2, -934.2},{115.9, 375.2, -975.3},{479.6, 375.2, -857.2},{-115.9, 0.0, -975.4},{303.6, 0.0, -934.2},{667.1, 0.0, -721.0},{0.0, 0.0, 0.0},{325.2, 1133.2, 0.0},{491.1, 982.3, -356.8},{700.4, 901.4, 0.0},{541.7, 700.4, -666.1},{800.9, 700.4, -309.3},{894.5, 634.8, 0.0},{794.7, 375.2, -577.4},{963.4, 375.2, -191.1},{963.5, 375.2, 191.2},{891.9, 0.0, -411.6},{982.3, 0.0, 0.0},{891.8, 0.0, 411.6},{0.0, 0.0, 0.0} };
int edges[NUM_EDGES][3] = { {0,1,0},{0,13,0},{0,26,0},{0,39,0},{0,52,0},{1,2,2},{1,3,3},{1,13,1},{1,14,2},{1,52,1},{2,3,2},{2,4,2},{2,5,2},{2,52,2},{2,54,2},{3,5,1},{3,6,0},{3,14,2},{3,16,1},{4,5,3},{4,7,2},{4,54,1},{4,57,0},{4,60,1},{5,6,0},{5,7,2},{5,8,1},{6,8,0},{6,9,0},{6,16,0},{7,8,2},{7,10,2},{7,60,2},{7,63,2},{8,9,1},{8,10,3},{8,11,2},{9,11,2},{9,12,3},{9,16,1},{9,19,2},{10,11,2},{10,63,1},{11,12,2},{12,19,2},{12,22,1},{13,14,2},{13,15,3},{13,26,1},{13,27,2},{14,15,2},{14,16,2},{14,17,2},{15,17,1},{15,18,0},{15,27,2},{15,29,1},{16,17,3},{16,19,2},{17,18,0},{17,19,2},{17,20,1},{18,20,0},{18,21,0},{18,29,0},{19,20,2},{19,22,2},{20,21,1},{20,22,3},{20,23,2},{21,23,2},{21,24,3},{21,29,1},{21,32,2},{22,23,2},{23,24,2},{24,32,2},{24,35,1},{25,38,0},{25,51,0},{25,64,0},{26,27,2},{26,28,3},{26,39,1},{26,40,2},{27,28,2},{27,29,2},{27,30,2},{28,30,1},{28,31,0},{28,40,2},{28,42,1},{29,30,3},{29,32,2},{30,31,0},{30,32,2},{30,33,1},{31,33,0},{31,34,0},{31,42,0},{32,33,2},{32,35,2},{33,34,1},{33,35,3},{33,36,2},{34,36,2},{34,37,3},{34,42,1},{34,45,2},{35,36,2},{36,37,2},{37,45,2},{37,48,1},{38,51,0},{38,64,0},{39,40,2},{39,41,3},{39,52,1},{39,53,2},{40,41,2},{40,42,2},{40,43,2},{41,43,1},{41,44,0},{41,53,2},{41,55,1},{42,43,3},{42,45,2},{43,44,0},{43,45,2},{43,46,1},{44,46,0},{44,47,0},{44,55,0},{45,46,2},{45,48,2},{46,47,1},{46,48,3},{46,49,2},{47,49,2},{47,50,3},{47,55,1},{47,58,2},{48,49,2},{49,50,2},{50,58,2},{50,61,1},{51,64,0},{52,53,2},{52,54,3},{53,54,2},{53,55,2},{53,56,2},{54,56,1},{54,57,0},{55,56,3},{55,58,2},{56,57,0},{56,58,2},{56,59,1},{57,59,0},{57,60,0},{58,59,2},{58,61,2},{59,60,1},{59,61,3},{59,62,2},{60,62,2},{60,63,3},{61,62,2},{62,63,2} };

Node* nodes_array[NUM_VERTICES];
Strut* struts_array[NUM_EDGES];

int fake_vertices[4] = { 25,38,51,64 };

//not sure what this was for lol but it works
bool isFake(int num) {
	if (num == 25 || num == 38 || num == 51 || num == 64) {
		return true;
	}
	return false;
}

void Dome::regenLEDs() {
	leds.clear();
	for (Strut* strut : struts) {
		for (LED* led : strut->leds) {
			leds.push_back(led);
		}
	}
}

Dome::Dome() {
	dataPipe = 0;

	for (int i = 0; i < NUM_VERTICES; i++) {
		float x, y, z;
		x = vertices[i][0];
		y = vertices[i][1];
		z = vertices[i][2];
		if (isFake(i)) {
			continue;
		}
		Node* newNode = Graph::createNode(vertices[i][0], vertices[i][1], vertices[i][2]);
		
		//newNode->index = i;//this is wrong
		nodes_array[i] = newNode;
	}

	int startLED = 0;
	int numLEDs = 0;
	for (int e = 0; e < NUM_EDGES; e++) {
		int letter = edges[e][2];
		int index = e;
		int e1 = edges[e][0];
		int e2 = edges[e][1];
		if (isFake(e1) || isFake(e2)) {
			continue;
		}
		Strut* newStrut = Graph::createStrut(nodes_array[e1], nodes_array[e2],letter, index, startLED);
		
		
		struts_array[e] = newStrut;
		startLED += numLEDs;
		for (LED* l : newStrut->leds) {
			this->leds.push_back(l);
		}
	}
	int total = (startLED);
	this->totalLEDs = total;
	std::cout << "TOTAL LEDS = " << total << std::endl;
}

