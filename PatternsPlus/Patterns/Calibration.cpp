#include "Calibration.h"
#include "../helpers.h""
#include <string>
#include <fstream>

uint32_t ledbuffer[MAX_LEDS]; // just keep track of a color value for each, not anything fancy

using namespace std;
ofstream cal_file;
ifstream cal_file_in;

void Calibration::help() {
	printf("Welcome to calibration\n");
	printf(" * RAINBOW\tis the start LED, Blue along the strut selection, RED is end LED\n");
	printf(" * Solid green\t is an LED that already belongs to an edge and has been confirmed\n");
	printf(" * Purple glow\t are the leds mapped to the selected strut\n");
	printf(" * Faint orange\tis an LED that is mapped to a strut, but has not been confirmed\n");
	printf(" * dim RED\tis an LED that is mappable, but is not yet mapped\n");
	printf("\nYour goal is to match the Blue strut IRL with the blue strut on the screen and then press enter\n");
	printf("Use arrow keys and enter, you can always redo things it is very forgiving\n");
	printf("When you are done please type save, this can be done to save progress along the way too\n");
	printf("If you want to leave you may type quit\n\n\n");
}

void Calibration::handleBuffer() {
	string buf = string(shared->bufferPipe);
	
	printf("calibration->%s\n", shared->bufferPipe);
	if (buf == "load") {
		loadCalibration(dome);
		
		

	}
	else if (buf == "save") {
		printf("\n======CALI START\n");
		for (int e = 0; e < dome->struts.size(); e++) {
			printf("%d %d %d %d\n",e,dome->struts[e]->startLED, dome->struts[e]->confirmed, dome->struts[e]->reversed);
		}
		printf("\n======CALI STOP\m");
		cal_file.open("ledcal69.txt");
		for (int e = 0; e < dome->struts.size(); e++) {
			cal_file << e;
			cal_file << ' ';
			cal_file << dome->struts[e]->startLED;
			cal_file << ' ';
			cal_file << dome->struts[e]->confirmed;
			cal_file << ' ';
			cal_file << dome->struts[e]->reversed;
			cal_file << '\n';
		}
		cal_file.close();
		printf("Saved! ledcal69.txt\n");
	}
	else if (buf == "quit") {
		quit = true; // exit main loop
		
	}
	else if (buf == "") {
		printf("setting edge %d start led %d\n", selectedEdge, selectedLED);
		dome->struts[selectedEdge]->setStartLED(selectedLED);
		
		selectedLED = selectedLED + dome->struts[selectedEdge]->numLEDs;
		lastConfirmedLED = selectedLED;
		dome->struts[selectedEdge]->confirmed = 1;
		
		orderedEdge_i = negMod(orderedEdge_i + edgecalidir, shared->mapping->orderedEdges.size());
		selectedEdge = shared->mapping->orderedEdges[orderedEdge_i];
		//selectedEdge = negMod(selectedEdge + 1, dome->struts.size());
		shared->selectedEdgePipe = selectedEdge;
		printf("now on edge %d start led %d\n", selectedEdge, selectedLED);
		
	} if (buf == "toggle") {
		//toggle to show what viewer looks like not calibrating
		shared->calibratingPipe ^= 1;//toggle it
		shared->viewReal ^= 1;
	}
	else if (buf == "help") {
		help();
	}
	shared->clearBuffer();
}

uint32_t Calibration::getBufferLED(int i) {
	return ledbuffer[i];
}

void Calibration::bufferLED(int i, uint32_t color) {
	ledbuffer[i] = color;
}
void Calibration::run(bool real) {
	help();
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
			//if(ledConfirmed(i))
			bufferLED(i, rgbScale(RED, 0.1)); // red for leds that are not a part of an edge
		}
		for (Strut * strut :  dome->struts) {
			for (LED* led : strut->leds) {
				if (strut->confirmed) {
					bufferLED(led->index, rgbScale(GREEN, 0.12)); //these are the leds part of a strut and confirmed;
				}
				else {
					if (ledConfirmed(led) == false) {
						bufferLED(led->index, rgbScale(ORANGE, t5 / 8.0)); //these are uncomfired with a strut
					}
					
				}
				
			}
			
		}
		Strut* strut = dome->struts[selectedEdge ];
		
		//these leds are currently mapped to strut
		for (LED* led : strut->leds) {
			bufferLED(led->index, rgbScale(PURPLE, t14)); // leds currently mapped to selected strut
		}
			
		//current selection
		
		for (int k = selectedLED + 1; k <= selectedLED + strut->numLEDs - 1; k++) {
			bufferLED(k, rgbScale(BLUE, t7));
		}
		
		if (strut->reversed == 0) {
			bufferLED(selectedLED, wheel(time(250) * 255));//selected led
			bufferLED(selectedLED + strut->numLEDs - 1, RED);//end of edge
		}
		else {
			bufferLED(selectedLED,RED );//selected led
			bufferLED(selectedLED + strut->numLEDs - 1, wheel(time(250) * 255));//end of edge
		}
		
				


		//write buffer to thing
		for (int i = 0; i < MAX_LEDS; i++) {
			//setLED(i, ledbuffer[i],false);
			setLED(i, ledbuffer[i],true);
		}

		updateLEDs(true);
		keyFlag = 0;
		int debugfps = 30;
		while ((nowMicros() - (beginMicros)) < (1 / ((float)debugfps)) * 1e6) {
			//delay2(100000);//make scrolling through numbers a little slower lol
			//handle input while waiting
			if (shared->submitPipe != 0) {
				shared->submitPipe = 0;
				shared->keyPressedPipe = 0;
				handleBuffer();
			}
			if (keyFlag < 3 && (shared->keyPressedPipe || shared->keyHeldPipe)) {
				int key = shared->keyHeldPipe > 0 ? shared->keyHeldPipe : shared->keyPressedPipe;
				switch (key) {
				case 'o':
					
					break;
				case 'R':
				case 'r':
				case '0':
				case '/':
					dome->struts[selectedEdge]->reversed ^= 1;
					/*if (dome->struts[selectedEdge]->reversed == 1) {
						// just became reversed, so add
						selectedLED = negMod(selectedLED + dome->struts[selectedEdge]->numLEDs, MAX_LEDS);
					}
					else {
						selectedLED = negMod(selectedLED-dome->struts[selectedEdge]->numLEDs,MAX_LEDS);
					}*/
					break;
				case 32: //SPACE BAR
					selectedLED = lastConfirmedLED;
					printf("reselected led: %d\n", selectedLED);
					break;

				case 262: // RIGHT ARROW
					
					orderedEdge_i = negMod(orderedEdge_i + 1, shared->mapping->orderedEdges.size());
					selectedEdge = shared->mapping->orderedEdges[orderedEdge_i];
					edgecalidir = 1;
					//selectedEdge = negMod(selectedEdge + 1, strutsLen);
					selectedLED = dome->struts[selectedEdge]->startLED;
					printf("EDGE=%d\tLED=%d\t\n", selectedEdge, selectedLED);
					
					break;
				case 263: // LEFT ARROW
					orderedEdge_i = negMod(orderedEdge_i - 1, shared->mapping->orderedEdges.size());
					selectedEdge = shared->mapping->orderedEdges[orderedEdge_i];
					//selectedEdge = negMod(selectedEdge - 1, strutsLen);
					selectedLED = dome->struts[selectedEdge]->startLED;
					edgecalidir = -1;
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
				LED* selectedLEDObj = shared->mapping->getLEDObj(selectedLED);
				if (selectedLEDObj != NULL) {
					printf("\nselectedLED:%d\nphi=%f\nx:\t%f\ty:\t%f\tz:\t%f\n", selectedLED, shared->mapping->getLEDPhi(selectedLED), selectedLEDObj->x, selectedLEDObj->y, selectedLEDObj->z);
					//printf("Edge->startLED:\nx:\t%f\ty:\t%f\tz:\t%f\n", shared->mapping->getLEDObj(dome->struts[selectedEdge]->startLED)->x, shared->mapping->getLEDObj(dome->struts[selectedEdge]->startLED)->y, shared->mapping->getLEDObj(dome->struts[selectedEdge]->startLED)->z);
					//printf("Edge->endLED:\nx:\t%f\ty:\t%f\tz:\t%f\n", shared->mapping->getLEDObj(dome->struts[selectedEdge]->endLED)->x, shared->mapping->getLEDObj(dome->struts[selectedEdge]->endLED)->y, shared->mapping->getLEDObj(dome->struts[selectedEdge]->endLED)->z);

				}
				
				keyFlag += 1;
				
				shared->keyPressedPipe = 0;
				shared->selectedEdgePipe = selectedEdge;
				
				
			}
		}

	}

}

