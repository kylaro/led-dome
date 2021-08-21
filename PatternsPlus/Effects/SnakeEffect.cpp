#include "SnakeEffect.h"
#include "../Interface/XBOX.h"
void SnakeEffect::init() {
    if (player == P1) {
        color = { 0.66,1,1 };//blue
    } else if (player == P2) {
        color = { 0.33,1,1 };//green
    }
    else {
        color = { 0,1,1 };//red
    }
	initted = 1;
	curNode = mapping->llnodes[rand()%(mapping->llnodes.size() -10)];
	prevNode = curNode;
	nextNode = curNode;
	lookaheadNode = curNode;
    length = 0.5;
}

void SnakeEffect::feed(double val) {
    food += val;
    
    length += val;
    if (length >= 0.99) {
        length = 0.99;
    }
}

void SnakeEffect::run() {
    if (initted == 0) {
        init();
    }
    hsv_f on = color;
    hsv_f rainbow = { time(200), 1, 1 };
    rgb_f off = { 0,0,0 };
    if (xbox::getAHeld(player)) {
        velocity = 0.75;
    }
    else {
        velocity = 0.45;
    }
    position += velocity;
    LEDs->setRGB(nextNode->led, off);
    while (position > 1) {
        position -= 1;

        
        
        //if (lookaheadSet == 0) {
        
        lookaheadSet = 1;
        //this is all i need to change..
        

        //}

        
        //ledInterface->setRGB(curNode->led, off);
        curNode = curNode->getNextDir(dir);
        if (curNode == NULL) {
            //this means we hit the end in this direction :)
            curNode = nextNode;// prevNode->getNeighbor();
            lookaheadSet = 0;
            lookaheadNode = curNode;
            dir = curNode->getStrutDir();
        }
        

        prevNode = curNode;
    }

    lookaheadNode = curNode;
    LLnode* last = lookaheadNode;
    while ((lookaheadNode = lookaheadNode->getNextDir(dir)) != NULL) {
        //lookaheadNode = lookaheadNode->getNextDir(dir);
        last = lookaheadNode;
    }
    double angle = xbox::getLeftThumbAngle(player);
    if (xbox::getLeftThumbActive(player)) {
        nextNode = last->getNeighborAngle(angle);

    }
    else {
        nextNode = last->getNeighbor();
    }
    //LEDs->forceHSV(curNode->led, on);
    ihsv_f trail_hsv = { curNode->led->index, on };
    trail.push_back(trail_hsv);
    for (int i = trail_k; i < trail.size(); i++) {
        if (trail[i].hsv.v < 0.05) {
            trail_k = i;
            LEDs->setRGB(trail[i].i, off);
            continue;
        }
        
        LEDs->forceHSV(trail[i].i, trail[i].hsv);
        trail[i].hsv.v *= length;
    }
    

    if (xbox::getLeftThumbActive(player)) {
        LEDs->forceHSV(nextNode->led, rainbow);
    }
    else {
        LEDs->setRGB(nextNode->led, off);
    }




}

void SnakeEffect::release() {
	done = 1;
    rgb_f off = { 0,0,0 };
	//turn off leds used...
    for (int i = trail_k; i < trail.size(); i++) {
        LEDs->setRGB(trail[i].i, off);
    }
}