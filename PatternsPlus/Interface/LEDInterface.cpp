#include "LEDInterface.h"
#include <cmath>
#include <stdio.h>
#include "../../Networking/ledcontrol.h"

double LEDInterface::sanitize(double x) {
    //CONVERT THIS X VALUE TO BE BETWEEN 0 AND 1 PLEASE
    if (x < 0) {
        x *= -1;//ok now it is positive
    }
    if (x > 1) {
        x = fmod(x, 1.0);
    }
    return x;
}

 LEDInterface::LEDInterface(bool real) {
    this->real = real;
}

void LEDInterface::apply() {
    //need this to accumulate
    for (LEDChange* change : changes) {
        if (change->rgborhsv == 0) { // USE RGB
            setLED(change->index, change->rgb.r, change->rgb.g, change->rgb.b, real);

        }
        else {//USE HSV
            
        }
    }
    changes.clear();
}

 void LEDInterface::setRGB(LED* led, double r, double g, double b) {
     rgb_t rgb;
     rgb.r = r * 255;
     rgb.g = g * 255;
     rgb.b = b * 255;
     changes.push_back(new LEDChange(led->index, rgb));
 }

void LEDInterface::HSVtoRGB(double H, double S, double V) {
    H *= 360;
    S *= 100;
    V *= 100;

    if (H > 360 || H < 0 || S>100 || S < 0 || V>100 || V < 0) {
        printf("The given HSV values are not in valid range\n");
        return;
    }
    float s = S / 100;
    float v = V / 100;
    float C = s * v;
    float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
    float m = v - C;
    float r, g, b;
    if (H >= 0 && H < 60) {
        r = C, g = X, b = 0;
    }
    else if (H >= 60 && H < 120) {
        r = X, g = C, b = 0;
    }
    else if (H >= 120 && H < 180) {
        r = 0, g = C, b = X;
    }
    else if (H >= 180 && H < 240) {
        r = 0, g = X, b = C;
    }
    else if (H >= 240 && H < 300) {
        r = X, g = 0, b = C;
    }
    else {
        r = C, g = 0, b = X;
    }
    int R = (r + m) * 255;
    int G = (g + m) * 255;
    int B = (b + m) * 255;
}