#include "EmissiveMaterial.h"

EmissiveMaterial::EmissiveMaterial() :
	AbsMaterial(RT::Vec3f(), 0.0)
{}

EmissiveMaterial::EmissiveMaterial(const EmissiveMaterial &other) :
	AbsMaterial(*this)
{}
