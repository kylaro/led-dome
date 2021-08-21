#ifndef COLORSTRUCTS_H
#define COLORSTRUCTS_H

typedef struct {
	int r;
	int g;
	int b;
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

#endif