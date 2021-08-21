//
// Created by kylaro on 1/23/2021.
//

#ifndef LEDCONTROL_LEDCONTROL_H
#define LEDCONTROL_LEDCONTROL_H

#include <cstdint>
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define PURPLE 0x800080
#define ORANGE 0xFFA500
#define MAX_LEDS 16384

#define BRIGHTNESS_DIVIDE 2// divide eache leds max RGB by this, ex. if 3 then (255/3 = 80ish)

void updateLEDs();// Sends the current packet to the leds
void updateLEDs(bool real);// does nothing if real is false
void initLEDController(); // TODO add IP address argument
uint32_t rgbToColor(int32_t red, int32_t green, int32_t blue);
uint32_t wheel(uint8_t pos);
void clearLEDs();
void clearLEDs(bool real);
void setLED(uint32_t i, uint8_t red, uint8_t green, uint8_t blue);
void setLED(uint32_t i, uint32_t rgb);// for ppl who aint got time for 3 rgb colors
void setLED(uint32_t i, uint8_t red, uint8_t green, uint8_t blue, bool real);
void setLED(uint32_t i, uint32_t rgb, bool real);// for ppl who aint got time for 3 rgb colors

typedef union {
#pragma pack(1)
    struct {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t aZ;// brightness control?
    };
    uint32_t rgb;
} led_t;

led_t* getLED(uint32_t i);
led_t* getLED(uint32_t i, bool real);



#endif //LEDCONTROL_LEDCONTROL_H




