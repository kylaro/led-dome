#include "Snake.h"
#include "../helpers.h""
#include "../Interface/XBOX.h"

void Snake::init() {
    initted = 1;
    curNode = mapping->llnodes[1000];
    prevNode = curNode;
    nextNode = curNode;
    lookaheadNode = curNode;
    //XBOX.init();
}

void Snake::run(bool real) {
    if (initted == 0) {
        init();
    }
    static int count = 0;
    count++;
    if (count % 2) {
        return;
    }
    rgb_f off = { 0,0,0 };
    ledInterface->setRGB(nextNode->led, off);
    //if (lookaheadSet == 0) {
    lookaheadNode = curNode;
        LLnode* last = lookaheadNode;
        while ((lookaheadNode = lookaheadNode->getNextDir(dir)) != NULL) {
            //lookaheadNode = lookaheadNode->getNextDir(dir);
            last = lookaheadNode;
        }
        lookaheadSet = 1;
        //this is all i need to change..
        double angle = xbox::getLeftThumbAngle(P1);
        if (xbox::getLeftThumbActive(P1)) {
            nextNode = last->getNeighborAngle(angle);
            
        }
        else {
            nextNode = last->getNeighbor();
        }
        
    //}
    
    hsv_f on = { 0.33,1,1 };
    hsv_f rainbow = { time(200), 1, 1 };
    //ledInterface->setRGB(curNode->led, off);
    curNode = curNode->getNextDir(dir);
    if (curNode == NULL) {
        //this means we hit the end in this direction :)
        curNode = nextNode;// prevNode->getNeighbor();
        lookaheadSet = 0;
        lookaheadNode = curNode;
        dir = curNode->getStrutDir();
    }
    ledInterface->forceHSV(curNode->led, on);
    for (int i = trail_k; i < trail.size(); i++) {
        if (trail[i].hsv.v < 0) {
            trail_k = i;
        }
        trail[i].hsv.v -= 0.04;
        ledInterface->forceHSV(trail[i].i, trail[i].hsv);
    }
    ihsv_f trail_hsv = { curNode->led->index, on };
    trail.push_back(trail_hsv);

    if (xbox::getLeftThumbActive(P1)) {
        ledInterface->forceHSV(nextNode->led, rainbow);
    }
    else {
        ledInterface->setRGB(nextNode->led, off);
    }
    
    prevNode = curNode;
    
    

    

}