#include "BBox.h"
#include "..\raytracer\Ray.h"
#include "Util.h"

BBox::BBox(const RT::Vec3f &p0, 
		   const RT::Vec3f &p1) :
	x0(p0.x), y0(p0.y), z0(p0.z),
	x1(p1.x), y1(p1.y), z1(p1.z)
{}

BBox::BBox(double x0, double y0, double z0,
		   double x1, double y1, double z1) :
	x0(x0), y0(y0), z0(z0),
	x1(x1), y1(y1), z1(z1)
{
	//std::cout << p0 << std::endl;
	//std::cout << p1 << std::endl;
}

BBox::BBox(const BBox &other) :
	x0(other.x0), y0(other.y0), z0(other.z0),
	x1(other.x1), y1(other.y1), z1(other.z1)
{}

bool BBox::Intersect(Ray &ray) const
{
	double ox = ray.GetOrigin().x;
	double oy = ray.GetOrigin().y;
	double oz = ray.GetOrigin().z;

	double dx = ray.GetDirection().x;
	double dy = ray.GetDirection().y;
	double dz = ray.GetDirection().z;

	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;

	double a = 1.0 / dx;
	if (a >= 0)
	{
		tx_min = (x0 - ox) * a;
		tx_max = (x1 - ox) * a;
	}
	else
	{
		tx_min = (x1 - ox) * a;
		tx_max = (x0 - ox) * a;
	}

	double b = 1.0 / dy;
	if (b >= 0)
	{
		ty_min = (y0 - oy) * b;
		ty_max = (y1 - oy) * b;
	}
	else
	{
		ty_min = (y1 - oy) * b;
		ty_max = (y0 - oy) * b;
	}

	double c = 1.0 / dz;
	if (c >= 0)
	{
		tz_min = (z0 - oz) * c;
		tz_max = (z1 - oz) * c;
	}
	else
	{
		tz_min = (z1 - oz) * c;
		tz_max = (z0 - oz) * c;
	}

	double t0, t1;

	//find largest entering t value

	if (tx_min > ty_min)
		t0 = tx_min;
	else
		t0 = ty_min;

	if (tz_min > t0)
		t0 = tz_min;

	//find smallest exiting t value

	if (tx_max < ty_max)
		t1 = tx_max;
	else
		t1 = ty_max;

	if (tz_max < t1)
		t1 = tz_max;

	return (t0 < t1 && t1 > EPSILON);
}

bool BBox::Inside(const RT::Vec3f &p) const
{
	return ((p.x > x0 && p.x < x1) &&
		    (p.y > y0 && p.y < y1) &&
		    (p.z > z0 && p.z < z1));
}
