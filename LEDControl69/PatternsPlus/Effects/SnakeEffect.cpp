#include "SnakeEffect.h"
#include "../Interface/XBOX.h"
void SnakeEffect::init() {
    if (player == P1) {
        color = { 0.66,1,1 };//blue
        hue = 0.66;
    } else if (player == P2) {
        color = { 0.33,1,1 };//green
        hue = 0.33;
    }
    else {
        color = { 0,1,1 };//red
    }
    
	initted = 1;
    if (curNode == NULL) {
        curNode = mapping->llnodes[rand() % (mapping->llnodes.size() - 10)];
    }
	
	prevNode = curNode;
	nextNode = curNode;
	lookaheadNode = curNode;
    pastNodes.push_back(curNode);
}

void SnakeEffect::feed(double val) {
    food += val;
    length += val;
    
}

void SnakeEffect::run() {
    if (initted == 0) {
        init();
    }
    count++;
    hsv_f on = color;
    hsv_f rainbow = { time(200), 1, 1 };
    rgb_f off = { 0,0,0 };
    if (xbox::getAHeld(player)) {
        velocity = 0.75;
    }
    else {
        velocity = 0.45;
    }
    if (count < 80) {
        velocity = 0.45*(count/80.0);
    }
    position += velocity;
    prevNode = curNode;
    while (position > 1) {
        position -= 1;
        curNode = curNode->getNextDir(dir);
        if (curNode == NULL) {
            //this means we hit the end in this direction :)
            curNode = nextNode;// prevNode->getNeighbor();
            lookaheadSet = 0;
            lookaheadNode = curNode;
            dir = curNode->getStrutDir();
        }
        pastNodes.push_back(curNode);
        

       
    }

    //Controls for going to next strut;
    LEDs->setRGB(nextNode->led, off);
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

    while (pastNodes.size() > length) {
        if (pastNodes[0]->nodeImpact()) {
            for (int i = 0; i < nodeTouches.size(); i++) {
                if (pastNodes[0]->myNode == (*(nodeTouches.begin() + i))->myNode) {
                    nodeTouches.erase(nodeTouches.begin() + i);
                }
            }
        }
        LEDs->setRGB(pastNodes[0]->led->index, off);
        pastNodes.erase(pastNodes.begin());
    }
    double k = 1;
    for (int i = 0; i < pastNodes.size(); i++) {//(pastNodes.size() - length)
        LLnode* node = pastNodes[i];
        double v = k / (length + 1);
        
        v *= v;
        double s = 1;
        double whitelength = length > 10 ? 10 : length;
        
        //howwhite = thresh - howwhite;
        if (i > pastNodes.size() - whitelength) {
            
            //whitelength = length > 45 ? pastNodes.size() : length/2;
            s = (pastNodes.size()-i)/whitelength;//0.8*(pastNodes.size()-1 - i) / (whitelength);
            s = 1 -s;
            s *= s;
            s = 1 - s;
        }

        if (v < 0.05) {
            v = 0.05;
        }
        hsv_f hsv = { hue, s, v };
        LEDs->forceHSV(node->led->index, hsv);
        k++;

        
    }


    //LEDs->forceHSV(curNode->led, on);
    /*ihsv_f trail_hsv = { curNode->led->index, on };
    trail.push_back(trail_hsv);
    for (int i = trail_k; i < trail.size(); i++) {
        if (trail[i].hsv.v < 0.05) {
            trail_k = i;
            LEDs->setRGB(trail[i].i, off);
            continue;
        }
        
        LEDs->forceHSV(trail[i].i, trail[i].hsv);
        trail[i].hsv.v *= length;
    }*/
    

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
    for (int i = 0; i < pastNodes.size(); i++) {
        LLnode* node = pastNodes[i];
        LEDs->setRGB(node->led->index, off);
    }
}