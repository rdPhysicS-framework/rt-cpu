#include "Primitive.h"
#include "..\abstract\AbsMaterial.h"
#include "..\raytracer\Ray.h"
#include "..\Util\BBox.h"

Primitive::Primitive(AbsMaterial *material) :
	material(material)
{}

Primitive::Primitive(const Primitive &other) :
	material((AbsMaterial*)other.material->Clone())
{
}

Primitive::~Primitive()
{
	if (material)
	{
		delete material;
		material = nullptr;
	}
}

void Primitive::AddObject(Primitive *object)
{
}

BBox Primitive::GetBoundingBox() const
{
	return BBox();
}

