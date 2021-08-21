#ifndef VECTORMATH_H
#define VECTORMATH_H

#include "positioning.h"

double magnitude(xyz_f xyz);
void normalize(xyz_f* xyz);
xyz_f subtract(xyz_f xyz1, xyz_f xyz2);
double dot(xyz_f xyz1, xyz_f xyz2);
xyz_f cross(xyz_f a, xyz_f b);
void getOrthogVec(xyz_f xyz, xyz_f* ortho, char xyorz);
double wrappedDist(double x, double y, double wrap);
sph_f getSpherical(xyz_f xyz);
xy_f projectPoint(xyz_f center, xyz_f targetPoint);
bool linesIntersect(xy_f A, xy_f B, xy_f C, xy_f D);
#endif