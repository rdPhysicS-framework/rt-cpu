#include "GlossyReflectorMaterial.h"
#include "..\brdf\GlossySpecular.h"
#include "..\primitivas\Result.h"
#include "..\Util\Util.h"
#include "..\raytracer\Ray.h"
#include "..\abstract\AbsScene.h"
#include "..\interface\Tracer.h"

GlossyReflectorMaterial::GlossyReflectorMaterial(RT::Vec3f &color, 
												 float ambient, 
												 float diffuse, 
												 float specular, 
												 float intensity, 
												 float reflect, 
												 Sampler *sampler) :
	Phong(color, ambient, diffuse, specular, intensity),
	glossyEspecular(new GlossySpecular(color, reflect, 1.0f, sampler))
{
}

GlossyReflectorMaterial::GlossyReflectorMaterial(const GlossyReflectorMaterial &other) :
	Phong(other),
	glossyEspecular(dynamic_cast<GlossySpecular*>(
		other.glossyEspecular->Clone()))
{
}

GlossyReflectorMaterial::~GlossyReflectorMaterial()
{
	if (glossyEspecular)
	{
		delete glossyEspecular;
		glossyEspecular = nullptr;
	}
}

void GlossyReflectorMaterial::SetKr(const float kr)
{
	glossyEspecular->SetKs(kr);
}

void GlossyReflectorMaterial::SetExpoent(const float exp)
{
	glossyEspecular->SetExp(exp);
}

Material *GlossyReflectorMaterial::Clone() const
{
	return new GlossyReflectorMaterial(*this);
}

RT::Vec3f GlossyReflectorMaterial::AreaLightShade(Result & result)
{
	RT::Vec3f L = Phong::AreaLightShade(result);
	float t;
	RT::Vec3f wo = result.ray->GetDirection();
	RT::Vec3f wi;
	float pdf;
	RT::Vec3f r = glossyEspecular->SampleF(result, wi, wo, pdf);

	L += r * result.scene->GetTracer()->Raytracer(
		*result.scene, Ray(result.wHitPoint, wi), t, result.depth + 1) *
		(result.normal.Dot(wi) / pdf);
	return L;
}
