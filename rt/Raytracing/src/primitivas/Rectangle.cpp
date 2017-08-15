#include "Rectangle.h"
#include "..\raytracer\Ray.h"
#include "Result.h"
#include "..\abstract\Sampler.h"
#include "..\abstract\EmissiveMaterial.h"

Rectangle::Rectangle(RT::Vec3f &p, 
					 RT::Vec3f &a,
					 RT::Vec3f &b, 
					 RT::Vec3f &normal, 
					 AbsMaterial *material,
					 Sampler *sampler) :
	EmissiveObject(material),
	p(p), a(a), b(b),
	normal(RT::vc3::Normalize(normal)),
	sampler(sampler), 
	aLenSquared(a.SizeSQR()),
	bLenSquared(b.SizeSQR()),
	invArea(1.0f / (a.Size() * b.Size()))
{}

Rectangle::Rectangle(RT::Vec3f &p,
					 RT::Vec3f &a, 
					 RT::Vec3f &b, 
					 AbsMaterial *material, 
					 Sampler *sampler) :
	EmissiveObject(material),
	p(p), a(a), b(b),
	normal(RT::vc3::Cross(a,b)
			.Normalize()),
	sampler(sampler),
	aLenSquared(a.SizeSQR()),
	bLenSquared(b.SizeSQR()),
	invArea(1.0f / (a.Size() * b.Size()))
{}

Rectangle::Rectangle(const Rectangle &other) :
	EmissiveObject(other),
	p(other.p),
	a(other.a),
	b(other.b),
	normal(other.normal),
	sampler(other.sampler->Clone()),
	aLenSquared(other.aLenSquared),
	bLenSquared(other.bLenSquared),
	area(other.area),
	invArea(other.invArea)
{}

EmissiveMaterial *Rectangle::GetEmissiveMaterial() const
{
	return dynamic_cast<EmissiveMaterial*>(material);
}

RT::Vec3f Rectangle::Sample()
{
	RT::Vec2f point = sampler->SampleUnitSquare();
	return (p + point.x * a + point.y * b);
}

float Rectangle::PDF(Result &result)
{
	return invArea;
}


RT::Vec3f Rectangle::GetNormalAt(RT::Vec3f &pos)
{
	return normal;
}

bool Rectangle::Intersect(Ray & ray, float &distance, Result & result)
{
	float t = (p - ray.GetOrigin()).Dot(normal) /
		ray.GetDirection().Dot(normal);

	if (t <= 0.1)
		return false;

	RT::Vec3f p2 = ray.IntersectionPoint(t);
	RT::Vec3f d = p2 - p;

	double ddota = d.Dot(a);
	if (ddota < 0.0 || ddota > aLenSquared)
		return false;

	double ddotb = d.Dot(b);
	if (ddotb < 0.0 || ddotb > bLenSquared)
		return false;

	//result.hit = true;
	//distance = t;
	result.lHitPoint = p2;
	result.wHitPoint = p2;
	result.normal = GetNormalAt(p2);
	return true;

	/*float d = normal.Dot(ray.GetDirection());
	bool hit = false;
	float dst = distance;

	if (d != 0)
	{
		dst = (p - ray.GetOrigin()).Dot(normal) / d;

		if (dst > 0 && dst < distance)
		{
			RT::Vec3f auxP = ray.IntersectionPoint(dst);
			RT::Vec3f d = auxP - p;

			double dDotA = d.Dot(a);
			double dDotB = d.Dot(b);
			if (dDotA < 0.0 || dDotA > aLenSquared)
				hit = false;
			else if (dDotB < 0.0 || dDotB > aLenSquared)
				hit = false;
			else
				hit = true;

			distance = dst;

			result.hit = hit;
		}
	}*/

	//return hit;
}
