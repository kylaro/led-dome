#ifndef CALIBRATION_H
#define CALIBRATION_H
#include "../pattern.h"


class Calibration : public Pattern {
public:
	using Pattern::Pattern;

	

	void bufferLED(int i, uint32_t color);

	void run(bool real);
private:
	void handleBuffer();
	int previousEdge = 0;
	int selectedEdge = 0;
	int selectedLED = 0;
	double selectedLED_dbl = 0;
	int strutsLen = 0;
	
	bool quit = false;
};


#endif
