#include "Effect.h"


Effect::Effect(LEDInterface* myInterface, Mapping* mapping) {
	this->LEDs = myInterface;
	this->mapping = mapping;
}

void Effect::run() {


}
