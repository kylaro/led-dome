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

