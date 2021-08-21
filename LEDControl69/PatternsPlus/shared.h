
#ifndef SHARED_H
#define SHARED_H
#define BUFFER_LEN 69
#include "mapping.h"
#include "../Objects/dome.h"
#include "EffectEngine.h"
//Make this have semaphors or some kind of lock ? ? ?
//The reason I'm not doing that is because most of the stuff here is so primitive...
class Shared{
public:
	Shared();

	//outputs from viewer:
	int submitPipe = 0;
	int keyPressedPipe = 0;
	int spacePressedPipe = 0;
	char bufferPipe[BUFFER_LEN];
	int directionPipe = 0; // -1 for back, 0 for none, 1 for forward
	bool viewReal = true;
	int keyHeldPipe = 0;
	Mapping* mapping;
	Dome* dome;
	EffectEngine* effectEngine;
	

	void clearBuffer();
	//inputs to viewer:
	//maybe some kind of filter or something? idk exactly what will be input yet
	int calibratingPipe = 0;
	int selectedEdgePipe = 0;
	//If there are EVER any problems with threads, please just add these 2 functions and put them around all modifications to this object
	//lock()   //compare and add instruction? 
	//unlock() 
};


#endif