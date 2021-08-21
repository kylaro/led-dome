#ifndef HELPERS_H
#define HELPERS_H

#include <stdint.h>
#include "../Objects/dome.h"


double triangleD(double d);
void delay2(int idk);
int negMod(int x, int mod);
double time(uint32_t period);//returns 0 to 1 of how far in the period we are.
double triangle(uint32_t period);
uint32_t sharpenRGB(uint32_t rgb, uint32_t thresh);
uint32_t rgbDiv(uint32_t rgb, uint8_t div);
uint32_t rgbScale(uint32_t rgb, double scale);
uint32_t rDiv(uint32_t rgb, uint8_t div);
uint32_t gDiv(uint32_t rgb, uint8_t div);
uint32_t bDiv(uint32_t rgb, uint8_t div);
uint32_t getR(uint32_t rgb);
uint32_t getG(uint32_t rgb);
uint32_t getB(uint32_t rgb);
uint32_t assembleRGB(uint32_t r, uint32_t g, uint32_t b);
uint32_t nowNanos();
uint32_t nowMicros();
uint32_t nowMillis();
float distance3d(float x1, float y1, float z1, float x2, float y2, float z2);

void loadCalibration(Dome* dome);
#endif