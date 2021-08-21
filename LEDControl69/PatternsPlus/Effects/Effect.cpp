#include "Effect.h"


Effect::Effect(LEDInterface* myInterface, Mapping* mapping) {
	this->LEDs = myInterface;
	this->mapping = mapping;
}

void Effect::giveEngine(EffectEngine * effE) {
	engine = effE;
}

void Effect::run() {


}
void Effect::init() {


}

void Effect::release() {

}
