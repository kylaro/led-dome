//
// Created by kylaro on 1/23/2021.
//
#include "ledcontrol.h"
#include "e131_packet.h"
//#include "udpclient.h"
#include "udpsend_windows.h"
#include <vector>

#define NUM_UNIVERSES 97 // This is the max number of universes for 16384 pixels
#define LEDS_PER_UNIVERSE 170


led_t leds[MAX_LEDS];
led_t leds_sim[MAX_LEDS];
led_t ledbuffer[MAX_LEDS];




uint8_t seqCounter = 0;

std::vector<int> dirtyUnivs;
uint32_t dirtyMap[4];

void clearDirtyMap() {
    dirtyMap[0] = 0;
    dirtyMap[1] = 0;
    dirtyMap[2] = 0;
    dirtyMap[3] = 0;
}
int getDirtyMap(uint32_t univ) {
    return (dirtyMap[univ / 32] >> (univ % 32)) & 1;
}

void setDirtyMap(uint32_t univ) {
    dirtyMap[univ / 32] |= 1 << (univ % 32);
}

void setDirtyMap0(uint32_t univ) {
    dirtyMap[univ / 32] &= ~(1 << (univ % 32));
}





uint32_t rgbToColor(int32_t red, int32_t green, int32_t blue) {
    return ((red) << 16) | ((green) << 8) | (blue);
}

uint32_t wheel(uint8_t pos) {
    if (pos < 85) {
        return rgbToColor((pos * 3) % 256, (255 - pos * 3) % 256, 0);
    }
    else if (pos < 170) {
        pos -= 85;
        return rgbToColor((255 - pos * 3) % 256, 0, (pos * 3) % 256);
    }
    else {
        pos -= 170;
        return rgbToColor(0, (pos * 3) % 256, (255 - pos * 3) % 256);
    }
}

//#todo could make modified_universes track the exact ones so we don't have to loop the entire 97 lol
bool modified_universes[NUM_UNIVERSES]; // 97 universes contain all the pixels, keep track of which ones have been changed

//TODO, make sure this doesn't skip anything pls
uint16_t getUniverse(uint32_t i) {
    //First we wonder what universe we are in
    //the milky way is just a galaxy
    //170 leds in 1 universe, universes start at 1 lol ( so dumb )
    uint16_t universe = i / 170 + 1; // led 0 is in universe 1, check, led 169 is in universe 1, check, led 170 is in universe 2, check, ya probably works
    return universe;
}

uint16_t getChannel(uint32_t i) {
    //Well there's 170 leds in a universe, 510 channels
    //led 0 is channels 1 2 3
    //led 1 is channels 4 5 6
    // led 169 is channels 508 509 510
    i %= 170; // make it 0 to 169 (nice)
    uint16_t channel = i * 3 + 1;
    return channel;
}

led_t* getLED(uint32_t i) {
    return &leds[i];
}

led_t* getLED(uint32_t i, bool real) {
    if (real) {
        return getLED(i);
    }
    else {
        return &leds_sim[i];
    }

}



//everything has already been done, we just gotta update the array and universe modified thing
void setLED(uint32_t i) {
    if (DYNAMIC_PACKETS) {
        uint16_t uni = getUniverse(i);
        if (!getDirtyMap(uni)) {
            dirtyUnivs.push_back(uni);
        }

        setDirtyMap(uni);

        modified_universes[uni] = 1; // mark it as changed so we can send an update packet
    }
   
    
}

void clearLEDs() {
    for (int i = 0; i < MAX_LEDS; i++) {
        setLED(i, 0);
        setLED(i);

    }
    updateLEDs();

}
void clearLEDs(bool real) {
    if (real) {
        clearLEDs();
        return;
    }
    //if simulated
    for (int i = 0; i < MAX_LEDS; i++) {
        setLED(i, 0, false);
    }

}

void setLED(uint32_t i, uint32_t rgb) {
    if (leds[i].rgb != rgb) {
        setLED(i);//only set on change
    }
    leds[i].rgb = rgb;
    //EXPERIMENTAL CODE:
    uint16_t universe = getUniverse(i);
    uint16_t channel = getChannel(i);
    packets[universe].dmp.prop_val[channel] = leds[i].r / BRIGHTNESS_DIVIDE;
    packets[universe].dmp.prop_val[channel + 1] = leds[i].g / BRIGHTNESS_DIVIDE;
    packets[universe].dmp.prop_val[channel + 2] = leds[i].b / BRIGHTNESS_DIVIDE;
    //END EXPERIMENTAL CODE
    
}
void setLED(uint32_t i, uint8_t red, uint8_t green, uint8_t blue) {
    if (leds[i].r != red || leds[i].g != green || leds[i].b != blue) {
        setLED(i);//only set on change
    }
    leds[i].r = red;
    leds[i].g = green;
    leds[i].b = blue;

    //EXPERIMENTAL CODE:
    uint16_t universe = getUniverse(i);
    uint16_t channel = getChannel(i);
    packets[universe].dmp.prop_val[channel] = leds[i].r / BRIGHTNESS_DIVIDE;
    packets[universe].dmp.prop_val[channel + 1] = leds[i].g / BRIGHTNESS_DIVIDE;
    packets[universe].dmp.prop_val[channel + 2] = leds[i].b / BRIGHTNESS_DIVIDE;
    //END EXPERIMENTAL CODE
}

void setLED(uint32_t i, uint32_t rgb, bool real) {
    if (real) {
        setLED(i, rgb);
    }
    else {
        //simulated led;
        leds_sim[i].rgb = rgb;
    }
    
}
void setLED(uint32_t i, uint8_t red, uint8_t green, uint8_t blue, bool real) {
    if (real) {
        setLED(i, red, green, blue);
    }
    else {
        //simulated led;
        leds_sim[i].r = red;
        leds_sim[i].g = green;
        leds_sim[i].b = blue;
    }
   
}

void initLEDController() {
    //Init packet object
    initPacket();
    initPackets();
    updateLEDs();
}

uint32_t ledFromUniChan(uint16_t universe, uint16_t channel) {
    return (universe - 1) * 170 + channel / 3;
}

void updateLEDsEXP() {
    static int i = 0;
    i++;
    i %= 4;
    uint32_t map = dirtyMap[i];
    uint32_t univ = i * 32;
    int k = 0;
    while (k < 32) {
        if (map & 1) {
            setSeq(univ, seqCounter);
            udpSend_windows(packets[univ].raw);
            seqCounter++;
        }
        map >>= 1;
        univ++;
        k++;
    }
    dirtyMap[i] = 0;
}
void updateLEDsLIMIT() {
    std::vector<int>::iterator it = dirtyUnivs.begin();
    int count = 35;
    while (it != dirtyUnivs.end())
    {
        count--;
        if (count == 0) {
            break;
        }
        int univ = *it;
        setSeq(univ, seqCounter);
        udpSend_windows(packets[univ].raw);
        seqCounter++;
        it = dirtyUnivs.erase(it);
        setDirtyMap0(univ);
    }
    //clearDirtyMap();
}
//Sends the packet to any universe that had a modification to it's leds like the dirty little bits they are
void updateLEDs() {
    updateLEDsLIMIT();
    return;
    if (DYNAMIC_PACKETS) {
        

        for (int univ : dirtyUnivs) {
            setSeq(univ, seqCounter);
            udpSend_windows(packets[univ].raw);
            seqCounter++;
            
        }
        dirtyUnivs.clear();
        clearDirtyMap();
    }
    else {
        for (int u = 0; u < 97; u++) {
            setSeq(u, seqCounter);
            udpSend_windows(packets[u].raw);
            seqCounter++;
        }
    }
    
    return;
   


    return;
    for (uint8_t uni = 0; uni < NUM_UNIVERSES; uni++) {
        if (modified_universes[uni]) { // check dirty bit
            //If this universe has a modified LED
            setUniverse(uni);
            //We need to fill the 170 LEDs with the current data... :/, TODO maybe some kinda CASH for each universe would be much faster
            for (uint16_t uni_led = 0; uni_led < LEDS_PER_UNIVERSE; uni_led++) {
                uint16_t channel = getChannel(uni_led);

                uint32_t led = ledFromUniChan(uni, channel); // todo could also just use uni_led lol
                
                packet.dmp.prop_val[channel] = leds[led].r / BRIGHTNESS_DIVIDE;
                packet.dmp.prop_val[channel + 1] = leds[led].g / BRIGHTNESS_DIVIDE;
                packet.dmp.prop_val[channel + 2] = leds[led].b / BRIGHTNESS_DIVIDE;
            }

            incSeq();

            udpSend_windows(packet.raw); // udp likes it raw
            modified_universes[uni] = 0;
        }
    }

}


void updateLEDs(bool real) {
    if (real) {
        updateLEDs();
    }
    //otherwise it is simulated so no need to send data out anywhere.
}