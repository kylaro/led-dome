
#ifndef LEDINTERFACE_H
#define LEDINTERFACE_H
#include "../../Objects/led.h"
#include "../helpers.h"
#include <cstdint>
#include <unordered_map>
#include "LEDChange.h"

//THE RULES FOR THIS CLASS
//ALL INPUTS MUST BE DOUBLES
//ALL INPUTS WILL BE ABLE TO TAKE ANY VALUE WHETHER ITS NEGATIVE OR OVER 1

class LEDInterface {
public:
	double sanitizeH(double x);
	double sanitizeSV(double x);
	LEDInterface(bool real);

	double getScale();

	std::vector<LEDChange*> changes;
	std::unordered_map<int, std::vector<LEDChange*>*> changes_map;

	bool real = false;
	void setRGB(LED * led, rgb_f rgb);
	void setRGB(int index, rgb_f rgb);
	void setHSV(LED * led, hsv_f hsv);
	void setHSV(int index, hsv_f hsv);

	bool usePowerMonitoring = false;
	void apply();

	rgb_f HSVtoRGB(hsv_f hsv);
	double sanitize(double x);
};





#endif