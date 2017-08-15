#include "SmoothTriangle.h"
#include "..\..\Util\Util.h"
#include "..\..\Util\BBox.h"
#include "..\..\raytracer\Ray.h"
#include "..\..\primitivas\Result.h"

SmoothTriangle::SmoothTriangle() :
	Primitive(nullptr),
	v0(),
	v1(0, 0, 1),
	v2(1, 0, 0),
	n0(0, 1, 0),
	n1(0, 1, 0),
	n2(0, 1, 0)
{}

SmoothTriangle::SmoothTriangle(RT::Vec3f &v0, 
							   RT::Vec3f &v1, 
							   RT::Vec3f &v2) :
	Primitive(nullptr),
	v0(v0),
	v1(v1),
	v2(v2),
	n0(0, 1, 0),
	n1(0, 1, 0),
	n2(0, 1, 0)
{}

SmoothTriangle::SmoothTriangle(RT::Vec3f &v0, 
							   RT::Vec3f &v1, 
							   RT::Vec3f &v2, 
							   RT::Vec3f &n0, 
							   RT::Vec3f &n1, 
							   RT::Vec3f &n2) :
	Primitive(nullptr),
	v0(v0),
	v1(v1),
	v2(v2),
	n0(n0),
	n1(n1),
	n2(n2)
{}

SmoothTriangle::SmoothTriangle(RT::Vec3f &v0, 
							   RT::Vec3f &v1,
							   RT::Vec3f &v2, 
							   RT::Vec3f &n0, 
							   RT::Vec3f &n1, 
							   RT::Vec3f &n2, 
							   AbsMaterial *material) :
	Primitive(material),
	v0(v0),
	v1(v1),
	v2(v2),
	n0(n0),
	n1(n1),
	n2(n2)
{}

SmoothTriangle::SmoothTriangle(const SmoothTriangle &other) :
	Primitive(other),
	v0(other.v0),
	v1(other.v1),
	v2(other.v2),
	n0(other.n0),
	n1(other.n1),
	n2(other.n2)
{}

RT::Vec3f SmoothTriangle::GetNormalAt(RT::Vec3f & pos)
{
	return normal;
}

bool SmoothTriangle::Intersect(Ray & ray, float & distance, Result & result)
{
	double a = v0.x - v1.x;
	double b = v0.x - v2.x;
	double c = ray.GetDirection().x;
	double d = v0.x - ray.GetOrigin().x;

	double e = v0.y - v1.y;
	double f = v0.y - v2.y;
	double g = ray.GetDirection().y;
	double h = v0.y - ray.GetOrigin().y;

	double i = v0.z - v1.z;
	double j = v0.z - v2.z;
	double k = ray.GetDirection().z;
	double l = v0.z - ray.GetOrigin().z;

	double m = f*k - g*j;
	double n = h*k - g*l;
	double p = f*l - h*j;

	double q = g*i - e*k;
	double s = e*j - f*i;

	double invDenom = 1.0 / (a*m + b*q + c*s);
	double e1 = d*m - b*n - c*p;
	double beta = e1 * invDenom;

	if (beta < 0.0)
		return false;

	double r = e*l - h*i;
	double e2 = a*n + d*q + c*r;
	double gamma = e2 * invDenom;

	if (gamma < 0.0)
		return false;

	if (beta + gamma > 1.0)
		return false;

	double e3 = a * p - b * r + d * s;
	double t = e3 * invDenom;

	if (t < EPSILON)
		return false;

	distance = t;
	normal = InterpolateNormal(beta, gamma);

	return true;
}

BBox SmoothTriangle::GetBoundingBox() const
{
	double delta = 0.000001;

	return BBox(min(min(v0.x, v1.x), v2.x) - delta, max(max(v0.x, v1.x), v2.x) + delta,
				min(min(v0.y, v1.y), v2.y) - delta, max(max(v0.y, v1.y), v2.y) + delta,
				min(min(v0.z, v1.z), v2.z) - delta, max(max(v0.z, v1.z), v2.z) + delta);
}



RT::Vec3f SmoothTriangle::InterpolateNormal(const float beta, const float gamma)
{
	RT::Vec3f n((1 - beta - gamma) * n0 + beta * n1 + gamma * n2);
	return n.Normalize();
}

