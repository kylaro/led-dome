#include <iostream>
#include "ledcontrol.h"


#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
int max(int a , int b){
    return a > b ? a : b;
}
int min(int a , int b){
    return a < b ? a : b;
}

void delay(int idk){
    for(int i = 0; i < idk; i+=2){
        i--;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    initLEDController();

    uint8_t r = 10;
    uint8_t g = 5;
    uint8_t b = 0;
    uint8_t cnt = 0;
    while(1){
        r++;
        g++;
        b++;



        //pixel chase
        for( int i = 0; i < 300 ;i++){

            setLED(i, wheel(i+cnt));
            updateLEDs();
            delay(5000000);
            setLED(i, 0);
            cnt++;
        }

        //pixelchase no reset
        for( int i = 0; i < 300 ;i++){

            setLED(i, wheel(i+cnt));
            updateLEDs();
            delay(5000000);
            cnt++;
        }

    }


    return 0;
}
