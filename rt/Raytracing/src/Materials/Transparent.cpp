#include "Transparent.h"
#include "..\brdf\PerfectSpecular.h"
#include "..\btdf\PerfectTransmitter.h"
#include "..\raytracer\Ray.h"
#include "..\primitivas\Result.h"
#include "..\Util\Util.h"
#include "..\interface\Tracer.h"
#include "..\abstract\AbsScene.h"

Transparent::Transparent(RT::Vec3f &color, 
						 float ambient, 
						 float diffuse, 
						 float specular,
						 float intensity,
						 float ks, 
						 float kt, 
						 float ior) :
	Phong(color,
		  ambient,
		  diffuse,
		  specular,
		  intensity),
	reflective(new PerfectSpecular(color, ks)),
	specular(new PerfectTransmitter(color, kt, ior))
{}

Transparent::Transparent(const Transparent &other) :
	Phong(other),
	reflective((PerfectSpecular*)
		other.reflective->Clone()),
	specular((PerfectTransmitter*)
		other.specular->Clone())
{}

Material *Transparent::Clone() const
{
	return new Transparent(*this);
}

RT::Vec3f Transparent::Shade(Result &result)
{
	RT::Vec3f L = Phong::Shade(result);

	RT::Vec3f wo = result.ray->GetDirection();
	RT::Vec3f wi;
	/*float pdf;
	RT::Vec3f r = reflective->SampleF(result, wi, wo, pdf);*/
	RT::Vec3f r = reflective->F(result, wi, wo);
	Ray reflectedRay(result.wHitPoint, wi);

	float t;

	if (specular->Tir(result))
	{
		L += result.scene->GetTracer()->Raytracer(
			*result.scene, reflectedRay, t, result.depth + 1);
	}
	else
	{
		RT::Vec3f wt;
		RT::Vec3f f = specular->SampleF(result, wt, wo);
		Ray transmittedRay(result.wHitPoint, wt);

		L += r * result.scene->GetTracer()->Raytracer(
					*result.scene, reflectedRay, t, result.depth + 1) *
			 fabs(result.normal.Dot(wi));

		L += f * result.scene->GetTracer()->Raytracer(
					*result.scene, transmittedRay, t, result.depth + 1) *
			 fabs(result.normal.Dot(wt));
	}

	return L;
}

RT::Vec3f Transparent::AreaLightShade(Result &result)
{
	RT::Vec3f L = Phong::AreaLightShade(result);

	RT::Vec3f wo = result.ray->GetDirection();
	RT::Vec3f wi;
	/*float pdf;
	RT::Vec3f r = reflective->SampleF(result, wi, wo, pdf);*/
	RT::Vec3f r = reflective->F(result, wi, wo);
	Ray reflectedRay(result.wHitPoint, wi);

	float t;

	if (specular->Tir(result))
	{
		L += result.scene->GetTracer()->Raytracer(
				*result.scene, reflectedRay, t, result.depth + 1);
	}
	else
	{
		RT::Vec3f wt;
		RT::Vec3f f = specular->SampleF(result, wt, wo);
		Ray transmittedRay(result.wHitPoint, wt);

		L += r * result.scene->GetTracer()->Raytracer(
					*result.scene, reflectedRay, t, result.depth + 1) *
					fabs(result.normal.Dot(wi));

		L += f * result.scene->GetTracer()->Raytracer(
					*result.scene, transmittedRay, t, result.depth + 1) *
					fabs(result.normal.Dot(wt));
	}

	return L;
}

RT::Vec3f Transparent::PathShade()
{
	return RT::Vec3f();
}
