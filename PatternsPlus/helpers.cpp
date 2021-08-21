#include "helpers.h"
#include <chrono>
#include "../Networking/ledcontrol.h"

uint32_t offset_micros = 0;

uint32_t nowNanos() {
	auto now = std::chrono::high_resolution_clock::now();
	uint32_t nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
	return nanos;
}

//this will wrap every 35 minutes - shouldn't be a problem tho
uint32_t nowMicros() {
	static uint32_t offset_micros = 1;
	if (offset_micros == 1) {
		offset_micros = 0;
		offset_micros = nowMicros();
	}
	auto now = std::chrono::high_resolution_clock::now();
	uint32_t micros = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count() - offset_micros;
	return micros;
}

uint32_t nowMillis() {
	auto now = std::chrono::high_resolution_clock::now();
	uint32_t millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
	return millis;
}

void delay2(int idk) {
	for (int i = 0; i < idk; i += 2) {
		i--;
	}
}
using namespace std::chrono;
//returns 0 to 1 repeating, sawtooth wave
//period is in MILLISECONDS 
//1 second is 1e3 = 1000
double time(uint32_t period) // PERIOD IN MILLIS
{
	period *= 1e3; // promote millis to micros

	auto now = high_resolution_clock::now();
	uint32_t micros = nowMicros();
	//std::cout << (nanos / period) << std::endl;
	return (double(micros % period)) / double(period);
}

int negMod(int x, int mod) {
	if (x >= 0) {
		return x % mod;
	}
	//otherwise it is negative
	return (mod - x) % mod; // 5 % 5 = 0, -1 % 5 = 4, -7 % 5 = 2? idk
}

uint32_t sharpenRGB(uint32_t rgb, uint32_t thresh) {
	uint32_t r = getR(rgb);
	uint32_t g = getG(rgb);
	uint32_t b = getB(rgb);

	r = r > thresh ? r : 0;
	g = g > thresh ? g : 0;
	b = b > thresh ? b : 0;
	if (r + g + b == 0) {
		return 0;
	}
	else {
		return rgb;
	}

	//alternate form that should be broken into 3 functions
	return assembleRGB(r, g, b);
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
	if (scale == 0) {
		//printf("rgbdiv0");
		return rgb;
	}
	uint32_t r = getR(rgb)/scale;
	uint32_t g = getG(rgb)/ scale;
	uint32_t b = getB(rgb)/ scale;
	return assembleRGB(r, g, b);
}

uint32_t rDiv(uint32_t rgb, uint8_t scale) {
	if (scale == 0) {
		//printf("rdiv0");
		return rgb;
	}
	uint32_t r = getR(rgb) / scale;
	uint32_t g = getG(rgb);
	uint32_t b = getB(rgb);
	return assembleRGB(r, g, b);
}
uint32_t gDiv(uint32_t rgb, uint8_t scale) {
	if (scale == 0) {
		//printf("gdiv0");
		return rgb;
	}
	uint32_t r = getR(rgb) ;
	uint32_t g = getG(rgb) / scale;
	uint32_t b = getB(rgb);
	return assembleRGB(r, g, b);
}
uint32_t bDiv(uint32_t rgb, uint8_t scale) {
	if (scale == 0) {
		//printf("bdiv0");
		return rgb;
	}
	uint32_t r = getR(rgb) ;
	uint32_t g = getG(rgb);
	uint32_t b = getB(rgb) / scale;
	return assembleRGB(r, g, b);
}


