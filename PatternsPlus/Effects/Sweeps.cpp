#include "Sweeps.h"

void Sweeps::init() {
	startTime = nowMillis();

	initted = 1;
}

void Sweeps::cleanup() {
	int numLeds = mapping->phiLeds.size();

	rgb_f off = { 0,0,0 };
	for (int i = 0; i < numLeds; i++) {
		int index = mapping->phiLeds[i]->index;
		
		//hsv_f hsv = { t * 2 + 2 * i / (double)numLeds, 1 , 1 };
		if ((mapping->phiLeds[i]->confirmed)) {
			LEDs->setRGB(index, off);
		}
	}
}

void Sweeps::run() {
	if (initted == 0) {
		init();
	}
	if (enabled == 0) {
		if (didfull == 1) {
			cleanup();
			didfull = 0;
		}
		return;
	}
	double duration = 3000;
	int time = nowMillis() - startTime;
	if (mode!=0 &&(time < 0 || time > duration) ){
		release();
		return;
	}


	double timescale = time / duration;// 1 second fade
	double t = timescale;
	int numLeds;
	switch (mode) {
	case 0://full rainbow
		//this is just full rainbow
		numLeds = mapping->phiLeds.size();

		for (int i = 0; i < numLeds; i++) {
			int index = mapping->phiLeds[i]->index;
			hsv_f hsv = { t * 2 + 2 * i / (double)numLeds, 1 , 1 };
			if ((mapping->phiLeds[i]->confirmed)) {
				LEDs->forceHSV(index, hsv);
			}
		}
		didfull = 1;
		break;
	case 1://Left
		numLeds = mapping->phiLeds.size();
		for (int i = 0; i < numLeds; i++) {
			int index = mapping->phiLeds[i]->index;
			uint32_t color = wheel(t * 256 + 256.0 * (i / (double)numLeds));
			color = getB(color);// we now have an intensity 0-255
			color = sharpenRGB(color, 200);
			color = color > 0;
			color = wheel(-t * 256 + i / 8) * color;
			//if (color == 0) {
			//	continue;
			//}
			rgb_f rgb = { getR(color) / 255.0, getG(color) / 255.0, getB(color) / 255.0 };

			if ((mapping->phiLeds[i]->confirmed)) {
				LEDs->forceRGB(index, rgb);
			}
				

		}
		break;
	case 2://Right
		numLeds = mapping->phiLeds.size();
		for (int i = 0; i < numLeds; i++) {
			int index = mapping->phiLeds[i]->index;
			uint32_t color = wheel(t * 256 - 256.0 * (i / (double)numLeds));
			color = getB(color);// we now have an intensity 0-255
			color = sharpenRGB(color, 200);
			color = color > 0;
			color = wheel(t * 256 + i / 8) * color;
			//if (color == 0) {
			//	continue;
			//}
			rgb_f rgb = { getR(color) / 255.0, getG(color) / 255.0, getB(color) / 255.0 };

			if ((mapping->phiLeds[i]->confirmed)) {
				LEDs->forceRGB(index, rgb);
			}
		}

		break;
	case 3: // down
		numLeds = mapping->yLeds.size();
		for (int i = 0; i < numLeds; i++) {
			int index = mapping->yLeds[i]->index;
			uint32_t color = wheel((t-0.40) * 256 + 256.0 * (i / (double)numLeds));
			color = getB(color);// we now have an intensity 0-255
			color = sharpenRGB(color, 200);
			color = color > 0;
			color = wheel(-t * 256 + i / 8) * color;
			rgb_f rgb = { getR(color) / 255.0, getG(color) / 255.0, getB(color) / 255.0 };

			if ((mapping->yLeds[i])->confirmed) {
				LEDs->forceRGB(index, rgb);
			}
				//setLED(index, (color), real);
		}

		break;
	case 4: // up
		numLeds = mapping->yLeds.size();
		for (int i = 0; i < numLeds; i++) {
			int index = mapping->yLeds[i]->index;
			uint32_t color = wheel((t-0.27) * 256 - 256.0 * (i / (double)numLeds));
			color = getB(color);// we now have an intensity 0-255
			color = sharpenRGB(color, 200);
			color = color > 0;
			color = wheel(t * 256 + i / 8) * color;
			rgb_f rgb = { getR(color) / 255.0, getG(color) / 255.0, getB(color) / 255.0 };

			if ((mapping->yLeds[i])->confirmed) {
				LEDs->forceRGB(index, rgb);
			}
			//setLED(index, (color), real);
		}

		break;
	


	}


}

void Sweeps::release() {
	done = 1;
	rgb_f off = { 0,0,0 };
	cleanup();
	//turn off leds used...
}