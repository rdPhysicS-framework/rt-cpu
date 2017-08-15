#ifndef	 __BBOX_H__
#define	 __BBOX_H__

#include <RTmath.h>
class Ray;

class BBox
{
public:
	double x0, y0, z0;
	double x1, y1, z1;

public:
	BBox(const RT::Vec3f &p0, const RT::Vec3f &p1);
	BBox(double x0 = -1.0, double y0 = -1.0, double z0 = -1.0,
		 double x1 =  1.0, double y1 =  1.0, double z1 =  1.0);
	BBox(const BBox &other);

	bool Intersect(Ray &ray) const;
	bool Inside(const RT::Vec3f &p) const;
};

#endif //__BBOX_H__