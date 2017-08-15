#include "Triangle.h"
#include "..\primitivas\Result.h"
#include "..\raytracer\Ray.h"
#include "..\Util\Util.h"
#include "..\Util\BBox.h"

Triangle::Triangle(RT::Vec3f &v1, 
				   RT::Vec3f &v2, 
				   RT::Vec3f &v3, 
				   AbsMaterial *material) :
		   Primitive(material),
		   v1(v1),
		   v2(v2),
		   v3(v3),
			normal(RT::vc3::Cross(
				v2 - v1, v3 - v1).Normalize())
{}

Triangle::Triangle(RT::Vec3f v1,
		           RT::Vec3f v2,
		           RT::Vec3f v3,
				   RT::Vec3f normal,
				   AbsMaterial *material) :
		  Primitive(material),
		  v1(v1),
		  v2(v2),
		  v3(v3),
	      normal(normal)
{}

Triangle::Triangle(Triangle &other) :
	v1(other.v1),
	v2(other.v2),
	v3(other.v3),
	Primitive(other.material)
{}

RT::Vec3f Triangle::GetNormalAt(RT::Vec3f & pos)
{
	return normal;
}

bool Triangle::Intersect(Ray &ray, float &distance, Result &result)
{
	/*
		livro pag 366
	*/
	/*
		B(ax - bx) + Y(ax - cx) + tdx = ax - ox
		B(ay - by) + Y(ay - cy) + tdy = ay - oy
		B(az - bz) + Y(az - cz) + tdz = az - oz
	*/


	double a = v1.x - v2.x;
	double b = v1.x - v3.x;
	double c = ray.GetDirection().x;
	double d = v1.x - ray.GetOrigin().x;

	double e = v1.y - v2.y;
	double f = v1.y - v3.y;
	double g = ray.GetDirection().y;
	double h = v1.y - ray.GetOrigin().y;
	
	double i = v1.z - v2.z;
	double j = v1.z - v3.z;
	double k = ray.GetDirection().z;
	double l = v1.z - ray.GetOrigin().z;

	/*
		|d b c|
		|h f g|
		|l j k|
	*/

	double m = f*k - g*j;
	double n = h*k - g*l;
	double p = f*l - h*j;

	/*
	|a d c|
	|e h g|
	|i l k|
	*/

	double q = g*i - e*k;
	/*
	|a b d|
	|e f h|
	|i j l|
	*/
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
	RT::Vec3f pi = ray.IntersectionPoint(distance);
	result.lHitPoint = pi;
	result.wHitPoint = pi;
	result.normal = GetNormalAt(pi);

	return true;
	/////////////////////////////////////////////////////////////////
	/*bool hit = true;
	RT::Vec3f a = v1 - v2;
	RT::Vec3f b = v1 - v3;
	RT::Vec3f c = ray.GetDirection();
	RT::Vec3f d = v1 - ray.GetOrigin();

	float m = b.y * c.z - c.y * b.z;
	float n = d.y * c.z - c.y * d.z;
	float p = b.y * d.z - d.y * b.z;
	float q = c.y * a.z - a.y * c.z;
	float s = a.y * b.z - b.y * a.z;

	float inv = 1.0f / (a.x * m + b.x * q + c.x * s);

	float e1 = d.x * m - b.x * n - c.x * p;
	float beta = e1 * inv;

	if (beta < 0.0f)
		hit = false;

	float r = a.y * d.z - d.y * a.z;
	float e2 = a.x * n + d.x * q + c.x * r;
	double gama = e2 * inv;

	if (gama < 0.0f)
		hit = false;

	if (beta + gama > 1.0f)
		hit = false;

	float e3 = a.x * p - b.x * r + d.x * s;
	float t = e3 * inv;

	if (t < 0.0f)
	{
		hit = false;
		distance = t;
	}

	if (hit)
	{
		result.hit = hit;
	}

	return hit;*/
}

BBox Triangle::GetBoundingBox() const
{
	double delta = 0.000001;

	return BBox(min(min(v1.x, v2.x), v3.x) - delta, max(max(v1.x, v2.x), v3.x) + delta,
				min(min(v1.y, v2.y), v3.y) - delta, max(max(v1.y, v2.y), v3.y) + delta,
				min(min(v1.z, v2.z), v3.z) - delta, max(max(v1.z, v2.z), v3.z) + delta);
}
