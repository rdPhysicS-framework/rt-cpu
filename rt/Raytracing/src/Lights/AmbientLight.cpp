#include "AmbientLight.h"

AmbientLight::AmbientLight(float ls, 
						   RT::Vec3f &color) :
	ls(ls), color(color)
{}

AmbientLight::AmbientLight(const AmbientLight &other) :
	AbsLight(other),
	ls(other.ls),
	color(other.color)
{}

void AmbientLight::SetLs(float ls)
{
	this->ls = ls;
}

void AmbientLight::SetColor(RT::Vec3f &color)
{
	this->color = color;
}

void AmbientLight::SetColor(float r, float g, float b)
{
	color.Set(r, g, b);
}

AbsLight *AmbientLight::Clone()
{
	return new AmbientLight(*this);
}

RT::Vec3f AmbientLight::GetDirection(Result &result)
{
	return RT::Vec3f();
}

RT::Vec3f AmbientLight::L(Result &result)
{
	return (color * ls);
}

bool AmbientLight::InShadow(Ray &ray, Result & result)
{
	return false;
}
