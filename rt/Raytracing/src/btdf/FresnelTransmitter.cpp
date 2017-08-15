#include "FresnelTransmitter.h"

float FresnelTransmitter::Fresnel(const Result & result) const
{
	return 0.0f;
}

BTDF * FresnelTransmitter::Clone()
{
	return nullptr;
}

RT::Vec3f FresnelTransmitter::SampleF(Result & result, RT::Vec3f & wt, RT::Vec3f & wo) const
{
	return RT::Vec3f();
}

bool FresnelTransmitter::Tir(Result & result) const
{
	return false;
}
