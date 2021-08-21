#include "HEXPulse.h"
#include "../helpers.h"
void HEXPulse::init() {
	startTime = nowMillis();
	int node = std::rand() % mapping->dome->nodes.size();
	//printf("XDwow%d\n", node);
	Node* myNode = mapping->dome->nodes[node];
	for (Strut* strut : myNode->struts) {
		double count = 0;
		int i = strut->startLED;
		//if(strut->leds[0])
		while (i != strut->endLED) {
			
			LED* led = strut->leds[i - strut->startLED];
			count++;
			hsv_f hsv = { (startTime % 10) / 10.0 + count / 100.0,0.7,1 };//
			LEDs->setHSV(led->index, hsv);
			ihsv_f newled = { led->index, hsv };
			leds.push_back(newled);
			i++;
		}
		
	}
}
void HEXPulse::run() {
	if (initted == 0) {
		init();
		initted = 1;
	}
	
	int time = nowMillis()-startTime;
	if (time < 0 || time > 1000) {
		done = 1;// oops it wrapped
		for (ihsv_f k : leds) {
			k.hsv.v = 0;
			LEDs->setHSV(k.i, k.hsv);
		}
		return;
	}
	
	
	double timescale = 1- time / 1000.0;// 1 second fade

	for (ihsv_f k : leds) {
		k.hsv.v = timescale;
		k.hsv.h += timescale;
		
		LEDs->setHSV(k.i, k.hsv);
	}

	

}