
#include "pattern.h"


void chase() {

}

void Pattern::run() {
	while (1) {
		chase();
	}
}

void Pattern::giveDome(Dome* dome) {
	this->dome = dome;
}