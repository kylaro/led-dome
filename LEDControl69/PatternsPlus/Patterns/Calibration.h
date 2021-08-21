#ifndef CALIBRATION_H
#define CALIBRATION_H
#include "../pattern.h"


class Calibration : public Pattern {
public:
	using Pattern::Pattern;

	

	void bufferLED(int i, uint32_t color);

	void run(bool real);
private:
	void help();
	void handleBuffer();
	uint32_t getBufferLED(int i);
	int previousEdge = 0;
	int selectedEdge = 33;
	int selectedLED = 0;
	int lastConfirmedLED = 0;
	double selectedLED_dbl = 0;
	int strutsLen = 0;
	int orderedEdge_i = 0;
	int edgecalidir = 1;
	
	bool quit = false;
};


#endif
