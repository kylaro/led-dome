#include "LEDInterface.h"
#include <cmath>
#include <stdio.h>
#include <map>


void LEDInterface::clearDirtyMap() {

    for (int i = 0; i < 530; i++) {
        dirtyMap[i] = 0;
    }
}
int LEDInterface::getDirtyMap(uint32_t led) {
    return (dirtyMap[led / 32] >> (led % 32)) & 1;
}

void LEDInterface::setDirtyMap(uint32_t led) {
    dirtyMap[led / 32] |= 1 << (led % 32);
}

//LOOP WHEEL
double LEDInterface::sanitizeH(double x) {
    //CONVERT THIS X VALUE TO BE BETWEEN 0 AND 1 PLEASE
    if (x < 0) {
        x *= -1;//ok now it is positive
    }
    if (x > 1) {
        x = fmod(x, 1.0);
    }
    return x;
}

//MAX / MIN
double LEDInterface::sanitizeSV(double x) {
    //CONVERT THIS X VALUE TO BE BETWEEN 0 AND 1 PLEASE
    if (x < 0) {
        return 0;
    }
    if (x > 1) {
        return 1;
    }
    return x;
}

 LEDInterface::LEDInterface(bool real) {
    this->real = real;
    rgb_f off = { 0,0,0 };
    for (int i = 0; i < MAX_LEDS; i++) {
        changesArray[i] = new LEDChange(i, off);
    }
}

 double LEDInterface::getScale() {
     uint32_t rgbTotal = 0;
     for (int i = 0; i < MAX_LEDS; i++) {
         led_t * led = getLED(i);
         rgbTotal += led->r;
         rgbTotal += led->g;
         rgbTotal += led->b;
     }
     double watts = 120+0.02 * (12.0 * rgbTotal) / 255.0;
     
     double max_watts = 1000.0;
     double scale = 1; (max_watts - 120) / watts;
     if (watts < max_watts) {
         scale = 1;
     }
     else {
         scale = (max_watts) / watts;
     }
     
     if (scale > 1) {
         scale = 1.0;
     }
     printf("watts=\t%f\tscale:\t%f\n", watts, scale);
     return scale;
     
}

void LEDInterface::apply() {
    double scale = 1;/// getScale();
    //uses arrray and dirtymap:

    /*for (int i : dirtyLEDs) {
        LEDChange* change = changesArray[i];
        if (change->count != 0) {
            setLED(change->index, (change->rgb.r * 255.0 * scale), (change->rgb.g * 255.0 * scale), (change->rgb.b * 255.0 * scale), real);
            change->count = 0;
        }
    }
    clearDirtyMap();
    dirtyLEDs.clear();
    return;*/
    //this uses the array:
    
    for (int i = 0; i < MAX_LEDS; i++) {
        LEDChange* change = changesArray[i];
        if (change->count != 0) {
            setLED(change->index, (change->rgb.r * 255.0 * scale), (change->rgb.g * 255.0 * scale), (change->rgb.b * 255.0 * scale), real);
            change->count = 0;
            change->locked = 0;
        }
        change->locked = 0;
        
    }
    
    return;
    //this uses the vector:
    for (LEDChange* change : changes) {
        setLED(change->index, (change->rgb.r*255.0*scale), (change->rgb.g * 255.0 * scale), (change->rgb.b * 255.0 * scale), real);
        free(change);
    }
    
    changes.clear();

    return;



    
    double maxWatts = 1800;
    static uint32_t totalRGB = 0;
    double totalWatts = 120+12.0*(totalRGB/255.0)*.025;//seems like just idle watts is 120... lol thats a lot tho
    
    

    for (std::pair<int, std::vector<LEDChange*>*> it : changes_map) {
        rgb_f rgb = { 0,0,0 };
        double size = it.second->size();
        //sum the changes
        for (LEDChange* change : *it.second) {
            rgb.r += change->rgb.r;
            rgb.g += change->rgb.g;
            rgb.b += change->rgb.b;
        }
        //avg the changes together
        rgb.r /= size;
        rgb.g /= size;
        rgb.b /= size;
        //create a final change object, need to do this bc first calculate total watts before setting leds
        
        if (usePowerMonitoring == false) {
            rgb.r *= scale;
            rgb.g *= scale;
            rgb.b *= scale;
            setLED(it.first, (rgb.r * 255), (rgb.g * 255), (rgb.b * 255));
        }
        else {
            LEDChange* combinedChange = new LEDChange(it.first, rgb);
            changes.push_back(combinedChange);
        }
        
        //subtract previous led watts
        
    }
    changes_map.clear();
    if (usePowerMonitoring == false) {
        return;
    }

    /*
    //need this to accumulate
    double scale = (maxWatts / totalWatts) > 1 ? 1 : (maxWatts/totalWatts);
    for (LEDChange* change : changes) {
        led_t* prev_led = getLED(change->index);
        rgb_t prev_rgb = { prev_led->r,prev_led->g,prev_led->b};
        rgb_f new_rgb = { change->rgb.r * scale, change->rgb.g * scale, change->rgb.b * scale };
        rgb_t new_rgb_t = { 255.0*new_rgb.r, 255.0 * new_rgb.g, 255.0 * new_rgb.b };
        
        totalRGB += change->getWattsEXP(new_rgb_t);
        totalRGB -= change->getWattsEXP(prev_rgb);
        setLED(change->index, (new_rgb_t.r), (new_rgb_t.g), (new_rgb_t.b), real);
    }
    changes.clear();
    */
   
}

void LEDInterface::clear() {
    rgb_f off = { 0,0,0 };
    for (int i = 0; i < MAX_LEDS; i++) {
        changesArray[i]->rgb = off;
        changesArray[i]->count = 0;
        changesArray[i]->locked = 0;
    }
}

void LEDInterface::setRGB(int index, rgb_f rgb) {
    rgb.r = sanitizeSV(rgb.r);
    rgb.g = sanitizeSV(rgb.g);
    rgb.b = sanitizeSV(rgb.b);
    
    changesArray[index]->assimilate(rgb);
    

}

void LEDInterface::setRGB(LED* led, rgb_f rgb) {
    setRGB(led->index, rgb);
}

void LEDInterface::setHSV(LED* led, hsv_f hsv) {
    setHSV(led->index, hsv);
 }

void LEDInterface::setHSV(int index, hsv_f hsv) {
    hsv.h = sanitizeH(hsv.h);
    hsv.s = sanitizeSV(hsv.s);
    hsv.v = sanitizeSV(hsv.v);

    setRGB(index, HSVtoRGB(hsv));
}

rgb_f LEDInterface::HSVtoRGB(hsv_f hsv) {
    double H = hsv.h * 360.0;
    double S = hsv.s * 100.0;
    double V = hsv.v * 100.0;

    double s = S / 100;
    double v = V / 100;
    double C = s * v;
    double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
    double m = v - C;
    double r, g, b;
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
    
    double R = (r + m);// *255;
    double G = (g + m);// * 255;
    double B = (b + m);// * 255;
    rgb_f rgb = { R,G,B };
    return rgb;
}







void LEDInterface::forceRGB(int index, rgb_f rgb) {
    rgb.r = sanitizeSV(rgb.r);
    rgb.g = sanitizeSV(rgb.g);
    rgb.b = sanitizeSV(rgb.b);

    changesArray[index]->force(rgb);


}

void LEDInterface::forceRGB(LED* led, rgb_f rgb) {
    forceRGB(led->index, rgb);
}

void LEDInterface::forceHSV(LED* led, hsv_f hsv) {
    forceHSV(led->index, hsv);
}

void LEDInterface::forceHSV(int index, hsv_f hsv) {
    hsv.h = sanitizeH(hsv.h);
    hsv.s = sanitizeSV(hsv.s);
    hsv.v = sanitizeSV(hsv.v);

    forceRGB(index, HSVtoRGB(hsv));
}