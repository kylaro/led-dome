#include "Fungus.h"

void Fungus::init(LLnode* starting_node) {
	startTime = nowMillis();
	curNode = starting_node;
	prevNode = curNode;
	dir = 1;
	initted = 1;
	
	on = { (rand() % 10) / 10.0, (rand() % 10) / 10.0, (rand() % 10) / 10.0 };
	//on = { (rand()%10)/10.0, (rand() % 10) / 10.0, (rand() % 10) / 10.0 };
	//printf("%f\n", on.g);
	speed = rand() % 6 / 12.0 + 1;
	initted = 1;
}

void Fungus::init() {
	init(mapping->llnodes[rand() % mapping->llnodes.size()]);
	
}

void Fungus::run() {
	if (initted == 0) {
		init();
	}
	if (done) {
		return;
	}
	if (dontdie == 0 && rand() % 20 == 1) {
		///release();
		//return;
	}

	//on.r += rand() % 5/ 500.0;
	//on.b += rand() % 5 / 500.0;
	//on.g += rand() % 5 / 500.0;
	//on.g += rand() % 5 / 500.0;

	gonext += speed;
	if (gonext > 1) {
		curNode = curNode->getNextDir(dir);
		if (curNode == NULL) {
			//this means we hit the end in this direction :)
			
			
			for (LLnode* node : prevNode->neighbors) {
				if (  engine->effects.size() > 100) {
					continue;
				}
				Fungus* new_fungi = new Fungus(LEDs, mapping);
				new_fungi->giveEngine(engine);
				new_fungi->init(node);
				new_fungi->dir = node->getStrutDir();
				//new_fungi->on = ;
				engine->queueApply(new_fungi);
				
			}
			
			//curNode = prevNode->getNeighbor();
			//dir = curNode->getStrutDir();
			//release goers here
			release();
			done = 1;
			return;
		}
		//curNode = curNode->getNextDir(dir);

		
		prevNode = curNode;
		//LEDs->setRGB(curNode->led, on);
		irgb_f led = { curNode->led->index, on };
		lights.push_back(led);
		LEDs->forceRGB(led.i, on);
		gonext = 0;
		//speed *= 0.96;
	}


	
	for (int k = startIndex; k < lights.size(); k++) {
		irgb_f light = lights[k];
		if (lights[k].rgb.r < 0.01) {
			startIndex = k;
			LEDs->setRGB(light.i, { 0,0,0 });
			continue;
		}
		LEDs->setRGB(light.i, light.rgb);
		lights[k].rgb.r *= 0.9;
		lights[k].rgb.g *= 0.86;//
		lights[k].rgb.b *= 0.8;

	}




}

void Fungus::release() {
	done = 1;
	rgb_f off = { 0,0,0 };
	//turn off leds used...

}