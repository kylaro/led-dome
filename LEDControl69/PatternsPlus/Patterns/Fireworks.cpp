#include "Fireworks.h"
#include "../helpers.h""
#include "../Interface/XBOX.h"
#include "../Effects/Firework.h"

void Fireworks::init() {
    initted = 1;
    //XBOX.init();
}

void Fireworks::run(bool real) {
    if (initted == 0) {
        init();
    }

    if (xbox::getAPress(P1) || xbox::getBHeld(P1)) {
        //xbox::vibrate(P1, 1);
        Firework* fire = new Firework(ledInterface, shared->mapping);
        fire->giveEngine(effectEngine);
        effectEngine->apply(fire);
        if (rumble > 0) {
            xbox::vibrate(P1, 1);
        }
        else {
            if (rumble > -1)
                xbox::vibrate(P1, 0);
        }

        rumble -= 0.2;
    }
    else {
        if (rumble > 0 && rumble < 1) {
            xbox::vibrate(P1, 1);
            rumble -= 0.2;
        }
        else {
            rumble = 1;
        }
        if (rumble == 1) {
            xbox::vibrate(P1, 0);
            rumble = 1.05;
        }
        //

    }





}