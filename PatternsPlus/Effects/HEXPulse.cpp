#include "HEXPulse.h"
#include "../helpers.h"
#include "../Interface/XBOX.h"
void HEXPulse::setNode(int n) {
	this->node = n;
	this->nodeSet = 1;
}
void HEXPulse::init() {
	startTime = nowMillis();
	if (nodeSet == 0) {
		node = std::rand() % mapping->dome->nodes.size();
	}
	
	
	Node* myNode = mapping->dome->nodes[node];
	if (myNode->index != node) {
		printf("of course it'snt working\n");
	}
	while (myNode->struts.size() < 5) {
		node = std::rand() % mapping->dome->nodes.size();
		myNode = mapping->dome->nodes[node];
	}
	for (Strut* strut : myNode->struts) {
		double count = 0;
		int i = strut->startLED;
		int reversed = 1;
		for (LED* led : myNode->closestLEDs) {
			if (led->index == strut->leds[0]->index) {
				reversed = 0;//start led
				break;
			}
			if (led->index == strut->leds[strut->leds.size() - 1]->index) {
				reversed = 1;//end led
				break;
			}
		}
		
		//if(strut->leds[0])
		if (reversed) {
			i = strut->endLED;
			while (i != strut->startLED) {

				LED* led = strut->leds[i-strut->startLED];
				count++;
				//hsv_f hsv = { 0,0,0 };//
				//hsv_f hsv = { (startTime % 10) / 10.0 + count / 100.0,0.7,1 };//
				hsv_f hsv = { 0+ count / 100.0,.9,1 };
				LEDs->setHSV(led->index, hsv);
				ihsv_f newled = { led->index, hsv };
				leds.push_back(newled);
				i--;
			}
		}
		else {
			while (i != strut->endLED) {

				LED* led = strut->leds[i - strut->startLED];
				count++;
				//hsv_f hsv = { (startTime % 10) / 10.0 + count / 100.0,0.7,1 };//
				//hsv_f hsv = { count / 100,1,1 };
				hsv_f hsv = { 0 + count / 100.0,.9,1 };
				LEDs->setHSV(led->index, hsv);
				ihsv_f newled = { led->index, hsv };
				leds.push_back(newled);
				i++;
			}
		}
		
		
	}
	initted = 1;
}

void HEXPulse::release() {
	done = 1;// oops it wrapped

	rgb_f off = { 0,0,0 };
	for (ihsv_f k : leds) {
		LEDs->setRGB(k.i, off);
	}
	xbox::vibrate(P1, 0);
	xbox::vibrate(P2, 0);
}
void HEXPulse::run() {
	
	double duration = 1200.0;
	if (initted == 0) {
		init();
	}
	
	int time = nowMillis()-startTime;
	if (time < 0 || time > duration) {
		release();
		return;
	}
	
	
	double timescale = time / duration;// 1 second fade
	xbox::vibrate(P1, 1-timescale);
	xbox::vibrate(P2, 1 - timescale);
	for (ihsv_f k : leds) {
		k.hsv.v = 1-timescale;
		k.hsv.s = timescale*8.0;
		
		k.hsv.h += timescale*timescale*timescale;
		
		LEDs->setHSV(k.i, k.hsv);
	}

	

}