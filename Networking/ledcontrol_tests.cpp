// Networking.cpp : Defines the entry point for the application.
//
#include "ledcontrol_tests.h"
#include "e131_packet.h"
#include "ledcontrol.h"
using namespace std;


#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
int max(int a, int b) {
    return a > b ? a : b;
}
int min(int a, int b) {
    return a < b ? a : b;
}

void delay(int idk) {
    for (int i = 0; i < idk; i += 2) {
        i--;
    }
}


int testChase()
{

    initLEDController();

    uint8_t r = 10;
    uint8_t g = 5;
    uint8_t b = 0;
    uint8_t cnt = 0;
    setLED(300, 0);
    while (1) {
        r++;
        g++;
        b++;


        
        //pixel chase
        for (int i = 0; i < 90; i++) {

            setLED(i, wheel(i + cnt));
            updateLEDs();
            delay(5000000);
            setLED(i, 0);
            cnt++;
        }

        //pixelchase no reset
        for (int i = 0; i < 90; i++) {

            setLED(i, wheel(i + cnt));
            updateLEDs();
            delay(5000000);
            cnt++;
        }

    }

    return 0;
}
