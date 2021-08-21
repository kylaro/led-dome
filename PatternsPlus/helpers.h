#ifndef HELPERS_H
#define HELPERS_H

#include <stdint.h>
void delay2(int idk);
int negMod(int x, int mod);
double time(uint32_t period);

uint32_t rgbDiv(uint32_t rgb, uint8_t div);
uint32_t rDiv(uint32_t rgb, uint8_t div);
uint32_t gDiv(uint32_t rgb, uint8_t div);
uint32_t bDiv(uint32_t rgb, uint8_t div);
#endif