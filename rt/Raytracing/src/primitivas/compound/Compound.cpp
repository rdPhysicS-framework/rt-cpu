#include "Compound.h"
#include "..\..\Util\Util.h"
#include "..\..\raytracer\Ray.h"
#include "..\..\primitivas\Result.h"
#include "..\..\abstract\AbsMaterial.h"
#include "..\..\Util\BBox.h"

Compound::Compound() :
	Primitive(nullptr)
{}

Compound::Compound(AbsMaterial *material) :
	Primitive(material)
{}

Compound::Compound(const Compound &other) :
	Primitive(other),
	bbox(other.bbox)
{
	for (Primitive *obj : other.objects)
		objects.push_back(obj);
}

Compound::~Compound()
{
	DeleteObjects();
}

Compound *Compound::clone() const
{
	return new Compound(*this);
}

void Compound::SetMaterial(AbsMaterial *_material)
{
	for (Primitive *obj : objects)
		obj->SetMaterial((AbsMaterial*)_material->Clone());
}

RT::Vec3f Compound::GetNormalAt(RT::Vec3f &pos)
{
	return normal;
}

bool Compound::Intersect(Ray &ray, float &distance, Result &result)
{
	//if (!bbox.Intersect(ray))
		//return false;

	bool hit = false;
	distance = INFINITE;
	float t = INFINITE;
	RT::Vec3f lhPoint;
	RT::Vec3f whPoint;

	for (Primitive *obj : objects)
	{
		if (obj->Intersect(ray, t, result) && 
			(t < distance))
		{
			hit = true;
			distance = t;
			material = obj->GetMaterial();
			whPoint = ray.IntersectionPoint(distance);
			lhPoint = ray.IntersectionPoint(distance);
			normal = obj->GetNormalAt(whPoint);
		}
	}

	if (hit)
	{
		result.distance = distance;
		result.normal = normal;
		result.wHitPoint = whPoint;
		result.lHitPoint = lhPoint;
	}

	return hit;
}

BBox Compound::GetBoundingBox() const
{
	return bbox;
}

void Compound::AddObject(Primitive *object)
{
	objects.push_back(object);
}

void Compound::DeleteObjects()
{
	for (Primitive *obj : objects)
	{
		delete obj;
		obj = nullptr;
	}

	objects.clear();
}
