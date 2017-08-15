#include "EmissiveObject.h"
#include "..\abstract\AbsMaterial.h"
#include "..\abstract\EmissiveMaterial.h"

EmissiveObject::EmissiveObject(AbsMaterial *material) :
	Primitive(material)
{}

EmissiveObject::EmissiveObject(const EmissiveObject &other) :
	Primitive((AbsMaterial*)other.material->Clone())
{}
