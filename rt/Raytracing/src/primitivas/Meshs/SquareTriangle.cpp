#include "SquareTriangle.h"
#include "..\Triangle.h"

SquareTriangle::SquareTriangle(RT::Vec3f &v0, RT::Vec3f &v1,
							   RT::Vec3f &v2, RT::Vec3f &v3, 
							   AbsMaterial * material) :
	Compound(material)
{
	Create(v0, v1, v2, v3);
}

SquareTriangle::SquareTriangle(RT::Vec3f &v0, RT::Vec3f &v1, 
							   RT::Vec3f &v2, RT::Vec3f &v3, 
							   RT::Vec3f &normal, AbsMaterial *material) :
	Compound(material),
	normal(normal)
{
	Triangle *t1 = new Triangle(v0, v2, v3, normal, (AbsMaterial*)material->Clone());
	Triangle *t2 = new Triangle(v0, v3, v1, normal, (AbsMaterial*)material->Clone());

	AddObject(t1);
	AddObject(t2);
}

void SquareTriangle::ComputeBoundingBox()
{
}

void SquareTriangle::Create(RT::Vec3f &v0, RT::Vec3f &v1, 
							RT::Vec3f &v2, RT::Vec3f &v3)
{
	Triangle *t1 = new Triangle(v0, v2, v3, (AbsMaterial*)material->Clone());
	Triangle *t2 = new Triangle(v0, v3, v1, (AbsMaterial*)material->Clone());

	AddObject(t1);
	AddObject(t2);
}

bool SquareTriangle::Intersect(Ray &ray, float &distance, Result &result)
{
	return Compound::Intersect(ray, distance, result);
}
