
#ifndef LEDINTERFACE_H
#define LEDINTERFACE_H
#include "../../Objects/led.h"
#include "../helpers.h"
#include <cstdint>
#include "LEDChange.h"

//THE RULES FOR THIS CLASS
//ALL INPUTS MUST BE DOUBLES
//ALL INPUTS WILL BE ABLE TO TAKE ANY VALUE WHETHER ITS NEGATIVE OR OVER 1

class LEDInterface {
public:
	LEDInterface(bool real);

	std::vector<LEDChange*> changes;

	bool real = false;
	void setRGB(LED * led, double r, double g, double b);
	void setR(LED* led, double r);
	void setG(LED* led, double g);
	void setB(LED* led, double b);
	
	void setHSV(LED * led, double h, double s, double v);
	void setH(LED* led, double h);
	void setS(LED* led, double s);
	void setV(LED* led, double v);

	void HSVtoRGB(double H, double S, double V);

	void apply();
	double sanitize(double x);
};





#endif