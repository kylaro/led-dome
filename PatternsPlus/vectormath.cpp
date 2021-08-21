#include "vectormath.h"
#include <cmath>

double magnitude(xyz_f xyz) {
	if (xyz.x + xyz.y + xyz.z == 0) {
		return 0;
	}
	return sqrt(xyz.x * xyz.x + xyz.y * xyz.y + xyz.z * xyz.z);
}
void normalize(xyz_f* xyz) {
	double magn = magnitude(*xyz);
	if (magn == 0) {
		return;
	}
	xyz->x = xyz->x / magn;
	xyz->y = xyz->y / magn;
	xyz->z = xyz->z / magn;
}

xyz_f subtract(xyz_f xyz1, xyz_f xyz2) {
	xyz_f result;
	result.x = xyz1.x - xyz2.x;
	result.y = xyz1.y - xyz2.y;
	result.z = xyz1.z - xyz2.z;
	return result;
}



double dot(xyz_f xyz1, xyz_f xyz2) {
	double result = 0;
	result += xyz1.x * xyz2.x;
	result += xyz1.y * xyz2.y;
	result += xyz1.z * xyz2.z;
	return result;
}

void getOrthogVec(xyz_f xyz, xyz_f* ortho, char xyorz) {
	switch (xyorz) {
	case 'x'://solve for X
		ortho->x = ((-xyz.y * ortho->y) - (xyz.z * ortho->z)) / xyz.x;
		break;
	case 'y'://solve for Y
		ortho->y = ((-xyz.x * ortho->x) - (xyz.z * ortho->z)) / xyz.y;
		break;
	case 'z'://solve for Z
		ortho->z = ((-xyz.y * ortho->y) - (xyz.x * ortho->x)) / xyz.z;
		break;
	}
}
double wrappedDist(double x, double y, double wrap) {
	double dx = abs(x - y);
	double dist = dx > wrap / 2 ? 2 * wrap - dx : dx;
	if (dist > dx) {
		return dx;// dx is smaller
	}
	else {
		return dist;// dist is smaller
	}

}

sph_f getSpherical(xyz_f xyz) {
	sph_f ret;
	ret.r = magnitude(xyz);
	ret.theta = atan2(xyz.y, xyz.x);
	ret.phi = acos(xyz.z / ret.r);
	return ret;
}

xyz_f cross(xyz_f a, xyz_f b) {
	xyz_f result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}


double ccw(xy_f A, xy_f  B, xy_f  C) {
	return (C.y - A.y) * (B.x - A.x) > (B.y - A.y) * (C.x - A.x);
}

	//# Return true if line segments ABand CD intersect

bool intersect(xy_f A, xy_f B, xy_f C, xy_f D) {
	return (ccw(A, C, D) != ccw(B, C, D)) && (ccw(A, B, C) != ccw(A, B, D));
}


bool linesIntersect(xy_f A, xy_f B, xy_f C, xy_f D) {
	return intersect(A, B, C, D);
}

xy_f projectPoint(xyz_f center, xyz_f targetP) {
	xyz_f pp = center;
	if (pp.x == 0 && pp.z == 0) {
		//special case for top node
		pp.z = -1;
	}
	xyz_f po = { 0,pp.y - 200,0 };
	xyz_f vn = subtract(pp, po);
	xyz_f voo = { po.x - pp.x, 0, po.z - pp.z };
	normalize(&vn);
	normalize(&voo);
	xyz_f voy = voo;
	//normalize(&oo);
	getOrthogVec(vn, &voy, 'y');
	normalize(&voy);
	xyz_f vey = voy;// subtract(voy, p);
	xyz_f vex = cross(vn, vey);
	normalize(&vey);
	normalize(&vex);

	double x = dot(vex, subtract(targetP, pp));
	double y = dot(vey, subtract(targetP, pp));

	xy_f ret = { x,y };
	return ret;
}