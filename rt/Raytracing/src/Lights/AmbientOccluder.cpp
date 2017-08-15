#include "AmbientOccluder.h"
#include "..\abstract\Sampler.h"
#include "..\primitivas\Result.h"
#include "..\raytracer\Ray.h"
#include "..\abstract\AbsScene.h"
#include "..\Util\Util.h"

AmbientOccluder::AmbientOccluder(RT::Vec3f &color, 
								 float ls, 
								 float minAmount, 
								 Sampler *sampler) :
	AbsLight(true),
	color(color),
	ls(ls),
	minAmount(minAmount),
	sampler(sampler)
{
	sampler->MapSamplesToHemisphere(1);
}

AmbientOccluder::AmbientOccluder(AmbientOccluder &other) :
	AbsLight(other),
	ls(other.ls),
	minAmount(other.minAmount),
	sampler(other.sampler->Clone())
{}

AmbientOccluder::~AmbientOccluder()
{
	delete sampler;
}

AbsLight *AmbientOccluder::Clone()
{
	return new AmbientOccluder(*this);
}

RT::Vec3f AmbientOccluder::GetDirection(Result & result)
{
	RT::Vec3f sp = sampler->SampleHemisphere();
	return (sp.x * u + sp.y * v + sp.z * w);
}

RT::Vec3f AmbientOccluder::L(Result &result)
{
	w = result.normal;
	v = RT::vc3::Cross(w, RT::Vec3f(0.0072f, 
								    1.0f, 
									0.0034f))
								 .Normalize();
	u = RT::vc3::Cross(v, w);

	if (InShadow(Ray(result.wHitPoint,
					 GetDirection(result)), 
				 result))
	{
		return (color * (minAmount * ls));
	}

	return color * ls;
}

bool AmbientOccluder::InShadow(Ray &ray, Result &result)
{
	float t = INFINITE;
	return result.scene->ShadowHit(ray, t);
}
