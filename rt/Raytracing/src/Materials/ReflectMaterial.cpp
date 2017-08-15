#include "ReflectMaterial.h"
#include "..\brdf\PerfectSpecular.h"
#include "..\primitivas\Result.h"
#include "..\raytracer\Ray.h"
#include "..\abstract\AbsScene.h"
#include "..\Tracer\Raycasting.h"

ReflectMaterial::ReflectMaterial(RT::Vec3f &color, 
								 float ambient, 
								 float diffuse, 
								 float specular, 
								 float intensity, 
								 float reflect) :
	Phong(color, ambient, diffuse, specular, intensity),
	reflect(new PerfectSpecular(color, reflect))
{
}

ReflectMaterial::ReflectMaterial(const ReflectMaterial &other) :
	Phong(other),
	reflect((PerfectSpecular*)other.reflect->Clone())
{}

ReflectMaterial::~ReflectMaterial()
{
	delete reflect;
}

Material *ReflectMaterial::Clone() const
{
	return new ReflectMaterial(*this);
}

RT::Vec3f ReflectMaterial::Shade(Result &result)
{
	RT::Vec3f L = Phong::Shade(result);
	float t;
	RT::Vec3f wo = result.ray->GetDirection();
	RT::Vec3f wi;
	RT::Vec3f r = reflect->F(result, wi, wo);

	L += r * result.scene->GetTracer()->Raytracer(
				*result.scene, Ray(result.wHitPoint, wi), t, result.depth + 1) * 
		 result.normal.Dot(wi);

	//result.scene->Hit(Ray(result.wHitPoint, wi),result.depth + 1)

	return L;
}

RT::Vec3f ReflectMaterial::AreaLightShade(Result &result)
{
	RT::Vec3f L = Phong::AreaLightShade(result);
	float t;
	RT::Vec3f wo = result.ray->GetDirection();
	RT::Vec3f wi;
	RT::Vec3f r = reflect->F(result, wi, wo);

	L += r * result.scene->GetTracer()->Raytracer(
		*result.scene, Ray(result.wHitPoint, wi), t, result.depth + 1) *
		result.normal.Dot(wi);
	return L;
}

RT::Vec3f ReflectMaterial::PathShade()
{
	return RT::Vec3f();
}
