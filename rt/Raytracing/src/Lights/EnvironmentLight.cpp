#include "EnvironmentLight.h"
#include "..\abstract\EmissiveObject.h"
#include "..\abstract\EmissiveMaterial.h"
#include "..\raytracer\Ray.h"
#include "..\primitivas\Result.h"
#include "..\abstract\Sampler.h"
#include "..\abstract\AbsScene.h"
#include "..\Util\Util.h"

EnvironmentLight::EnvironmentLight(EmissiveMaterial *material,
								   Sampler *sampler) :
	AbsLight(true),
	material(material),
	sampler(sampler),
	u(), v(), w(), wi()
{
	if (sampler)
		sampler->MapSamplesToHemisphere(1);
}

EnvironmentLight::EnvironmentLight(const EnvironmentLight &other) :
	AbsLight(other),
	material(other.material),
	sampler(other.sampler?
		    other.sampler->Clone() :
			nullptr),
	u(other.u), v(other.v), 
	w(other.w), wi(other.wi)
{
}

EnvironmentLight::~EnvironmentLight()
{
	if (sampler)
		delete sampler;
}

AbsLight *EnvironmentLight::Clone()
{
	return new EnvironmentLight(*this);
}

RT::Vec3f EnvironmentLight::GetDirection(Result &result)
{
	w = result.normal;
	v = RT::vc3::Cross(RT::Vec3f(0.0034f, 1.0000f, 0.0071f), w);
	u = RT::vc3::Cross(v, w);

	RT::Vec3f sp = sampler->SampleHemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;

	return wi;
}

RT::Vec3f EnvironmentLight::L(Result &result)
{
	return material->GetLe(result);
}

float EnvironmentLight::PDF(Result &result)
{
	return result.normal.Dot(wi) * INVPI;
}

bool EnvironmentLight::InShadow(Ray &ray, Result &result)
{
	return result.scene->ShadowHit(ray, INFINITE);
}
