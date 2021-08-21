#ifndef COLORSTRUCTS_H
#define COLORSTRUCTS_H
#include <cstdint>
#include "../Objects/LLnode.h"



typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} rgb_t;

typedef struct {
	int h;
	int s;
	int v;
} hsv_t;

typedef struct {
	double r;
	double g;
	double b;
} rgb_f;

typedef struct {
	double h;
	double s;
	double v;
} hsv_f;

typedef struct {
	uint32_t i;
	rgb_f rgb;
} irgb_f;

typedef struct {
	uint32_t i;
	hsv_f hsv;
} ihsv_f;

#endif