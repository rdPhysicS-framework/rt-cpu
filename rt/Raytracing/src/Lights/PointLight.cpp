#include "PointLight.h"
#include "..\primitivas\Result.h"
#include "..\abstract\AbsScene.h"
#include "..\raytracer\Ray.h"

PointLight::PointLight(RT::Vec3f &pos, 
					   RT::Vec3f &color, 
					   float ls) :
	AbsLight(true),
	position(pos), 
	color(color), 
	ls(ls)
{}

PointLight::PointLight(const PointLight &other) :
	AbsLight(other),
	position(other.position),
	color(other.color),
	ls(other.ls)
{}

AbsLight *PointLight::Clone()
{
	return new PointLight(*this);
}

RT::Vec3f PointLight::GetDirection(Result &result)
{
	return (position - result.wHitPoint).Normalize();
}

RT::Vec3f PointLight::L(Result &result)
{
	return (color * ls);
}

bool PointLight::InShadow(Ray &ray, Result &result)
{
	return result.scene->ShadowHit(ray, (position - ray.GetOrigin()).Size());
}
