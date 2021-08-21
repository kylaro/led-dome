#include "helpers.h"
#include <chrono>
#include "../Networking/ledcontrol.h"
void delay2(int idk) {
	for (int i = 0; i < idk; i += 2) {
		i--;
	}
}
using namespace std::chrono;
//returns 0 to 1 repeating, sawtooth wave
//period is in MILLISECONDS 
//1 second is 1e3 = 1000
double time(uint32_t period) {
	auto now = high_resolution_clock::now();
	uint32_t millis = duration_cast<milliseconds>(now.time_since_epoch()).count();
	//std::cout << (nanos / period) << std::endl;
	return (double(millis % period)) / double(period);
}

int negMod(int x, int mod) {
	if (x >= 0) {
		return x % mod;
	}
	//otherwise it is negative
	return (mod - x) % mod; // 5 % 5 = 0, -1 % 5 = 4, -7 % 5 = 2? idk
}

uint32_t getR(uint32_t rgb) {
	return (rgb & RED) >> 16;
}
uint32_t getG(uint32_t rgb) {
	return (rgb & GREEN) >> 8;
}
uint32_t getB(uint32_t rgb) {
	return rgb & BLUE;
}

uint32_t assembleRGB(uint32_t r, uint32_t g, uint32_t b) {
	return (r << 16) | (g << 8) | b;
}

uint32_t rgbDiv(uint32_t rgb, uint8_t scale) {
	uint32_t r = getR(rgb)/scale;
	uint32_t g = getG(rgb)/ scale;
	uint32_t b = getB(rgb)/ scale;
	return assembleRGB(r, g, b);
}

uint32_t rDiv(uint32_t rgb, uint8_t scale) {
	uint32_t r = getR(rgb) / scale;
	uint32_t g = getG(rgb);
	uint32_t b = getB(rgb);
	return assembleRGB(r, g, b);
}
uint32_t gDiv(uint32_t rgb, uint8_t scale) {
	uint32_t r = getR(rgb) ;
	uint32_t g = getG(rgb) / scale;
	uint32_t b = getB(rgb);
	return assembleRGB(r, g, b);
}
uint32_t bDiv(uint32_t rgb, uint8_t scale) {
	uint32_t r = getR(rgb) ;
	uint32_t g = getG(rgb);
	uint32_t b = getB(rgb) / scale;
	return assembleRGB(r, g, b);
}
