
#ifndef LEDINTERFACE_H
#define LEDINTERFACE_H
#include "../../Objects/led.h"
#include "../helpers.h"
#include <cstdint>
#include <unordered_map>
#include "LEDChange.h"
#include "../../Networking/ledcontrol.h"

//THE RULES FOR THIS CLASS
//ALL INPUTS MUST BE DOUBLES
//ALL INPUTS WILL BE ABLE TO TAKE ANY VALUE WHETHER ITS NEGATIVE OR OVER 1

class LEDInterface {
public:
	void clearDirtyMap();
	int getDirtyMap(uint32_t univ);
	void setDirtyMap(uint32_t univ);
	double sanitizeH(double x);
	double sanitizeSV(double x);
	LEDInterface(bool real);
	//void flashyPattern();
	double getScale();

	LEDChange* changesArray[MAX_LEDS];
	std::vector<LEDChange*> changes;
	std::unordered_map<int, std::vector<LEDChange*>*> changes_map;

	bool real = false;
	void setRGB(LED * led, rgb_f rgb);
	void setRGB(int index, rgb_f rgb);
	void setHSV(LED * led, hsv_f hsv);
	void setHSV(int index, hsv_f hsv);

	void clear();
	bool usePowerMonitoring = false;
	void apply();

	std::vector<int> dirtyLEDs;
	uint32_t dirtyMap[530];// more than enough to cover maxleds


	rgb_f HSVtoRGB(hsv_f hsv);
	double sanitize(double x);
};





#endif