#include "Calibration.h"
#include "../helpers.h""
#include <string>


uint32_t ledbuffer[MAX_LEDS]; // just keep track of a color value for each, not anything fancy

using namespace std;
void Calibration::handleBuffer() {
	string buf = string(shared->bufferPipe);
	printf("calibration-> %s\n", shared->bufferPipe);
	if (buf == "load") {

	}
	else if (buf == "save") {

	}
	else if (buf == "quit") {
		quit = true; // exit main loop
		
	}
	else if (buf == "") {
		printf("setting edge %d start led %d\n", selectedEdge, selectedLED);
		dome->struts[selectedEdge]->setStartLED(selectedLED);
		selectedLED = selectedLED + dome->struts[selectedEdge]->numLEDs;
		dome->struts[selectedEdge]->confirmed = 1;
		
		selectedEdge = negMod(selectedEdge + 1, dome->struts.size());
		shared->selectedEdgePipe = selectedEdge;
		printf("now on edge %d start led %d\n", selectedEdge, selectedLED);
		
	} if (buf == "toggle") {
		//toggle to show what viewer looks like not calibrating
		shared->calibratingPipe ^= 1;//toggle it
		shared->viewReal ^= 1;
	}
	shared->clearBuffer();
}

void Calibration::bufferLED(int i, uint32_t color) {
	ledbuffer[i] = color;
}
void Calibration::run(bool real) {
	printf("Welcome to calibration\n");
	printf("RAINBOW is the start LED, Blue along the strut selection, RED is end LED\n");
	printf("Solid green is an LED that already belongs to an edge and has been confirmed\n");
	printf("Faint orange is an LED that is mapped, but has not been confirmed\n");
	printf("dim RED is an LED that is mappable, but is not yet mapped\n");
	//AH yes, here it is, calibration
	//we are above the law in this pattern :) 
	//Mostly because this will not be included in the pattern vector, it will be triggered once and have full control upon proper commands
	
	strutsLen = dome->struts.size();
	uint32_t beginMicros = nowMicros();
	double t5 = 0;
	double t7 = 0;
	double t14 = 0;
	int keyFlag = 0;
	while (1) {
		if (quit) {
			break;
		}
		t5 = triangle(5000);
		t7 = triangle(700);
		t14 = triangle(1400);
		beginMicros = nowMicros();
		//Draw all mapping
		for (int i = 0; i < MAX_LEDS; i++) {
			bufferLED(i, rgbScale(RED, 0.1)); // red for leds that are not a part of an edge
		}
		for (Strut * strut :  dome->struts) {
			for (LED* led : strut->leds) {
				if (strut->confirmed) {
					bufferLED(led->index, rgbScale(GREEN, 0.12)); //these are the leds part of a strut and confirmed;
				}
				else {
					bufferLED(led->index, rgbScale(ORANGE, t5 / 8.0)); //these are uncomfired with a strut
				}
				
			}
			
		}
		Strut* strut = dome->struts[selectedEdge ];
		
		//these leds are currently mapped to strut
		for (LED* led : strut->leds) {
			bufferLED(led->index, rgbScale(PURPLE, t14)); // leds currently mapped to selected strut
		}
			
		//current selection
		for (int k = selectedLED+1; k <= selectedLED+strut->numLEDs - 1; k++) {
			bufferLED(k, rgbScale(BLUE, t7));
		}
		bufferLED(selectedLED, wheel(time(250)*255));
		bufferLED(selectedLED+strut->numLEDs-1, RED);
				


		//write buffer to thing
		for (int i = 0; i < MAX_LEDS; i++) {
			//setLED(i, ledbuffer[i],false);
			setLED(i, ledbuffer[i],true);
		}

		updateLEDs(true);
		keyFlag = 0;
		while ((nowMicros() - (beginMicros)) < (1 / ((float)200)) * 1e6) {
			//delay2(100000);//make scrolling through numbers a little slower lol
			//handle input while waiting
			if (shared->submitPipe != 0) {
				shared->submitPipe = 0;
				shared->keyPressedPipe = 0;
				handleBuffer();
			}
			if (keyFlag < 1 && (shared->keyPressedPipe || shared->keyHeldPipe)) {
				int key = shared->keyHeldPipe > 0 ? shared->keyHeldPipe : shared->keyPressedPipe;
				switch (key) {
				case 262: // RIGHT ARROW
					selectedEdge = negMod(selectedEdge + 1, strutsLen);
					selectedLED = dome->struts[selectedEdge]->startLED;
					printf("EDGE=%d\tLED=%d\t\n", selectedEdge, selectedLED);
					break;
				case 263: // LEFT ARROW
					selectedEdge = negMod(selectedEdge - 1, strutsLen);
					selectedLED = dome->struts[selectedEdge]->startLED;
					printf("EDGE=%d\tLED=%d\t\n", selectedEdge, selectedLED);
					break;
				case 265: // UP ARROW
					selectedLED = negMod(selectedLED + 1, MAX_LEDS);
					printf("EDGE=%d\tLED=%d\t\n", selectedEdge, selectedLED);
					break;
				case 264: // DOWN ARROW
					selectedLED = negMod(selectedLED - 1, MAX_LEDS);
					printf("EDGE=%d\tLED=%d\t\n", selectedEdge, selectedLED);
					break;
					
				}
				keyFlag += 1;
				
				shared->keyPressedPipe = 0;
				shared->selectedEdgePipe = selectedEdge;
				
				
			}
		}

	}

}