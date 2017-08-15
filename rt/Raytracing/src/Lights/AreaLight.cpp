#include "AreaLight.h"
#include "..\abstract\EmissiveObject.h"
#include "..\abstract\EmissiveMaterial.h"
#include "..\primitivas\Result.h"
#include "..\raytracer\Ray.h"
#include "..\abstract\Sampler.h"
#include "..\abstract\AbsMaterial.h"
#include "..\Util\Util.h"
#include "..\abstract\AbsScene.h"
#include "..\raytracer\Canvas.h"

AreaLight::AreaLight(EmissiveObject *object) :
	object(object), material(nullptr)
{}

AreaLight::AreaLight(const AreaLight &other) :
	object(other.object),
	samplePoint(other.samplePoint),
	normal(other.normal),
	wi(other.wi)
{}

AbsLight *AreaLight::Clone()
{
	return new AreaLight(*this);
}

RT::Vec3f AreaLight::GetDirection(Result &result)
{
	samplePoint = object->Sample();
	normal = object->GetNormalAt(samplePoint);
	wi = (samplePoint - result.wHitPoint)
			.Normalize();

	return wi;
}

RT::Vec3f AreaLight::L(Result &result)
{
	float dot = (normal * -1).Dot(wi);
	return (dot > 0.0f)? 
		object->GetEmissiveMaterial()
		->GetLe(result) : BLACK;
}

float AreaLight::G(Result & result)
{
	float dot = (normal * -1).Dot(wi);
	float d = (samplePoint -
		result.wHitPoint).SizeSQR();

	return dot / d;
}

float AreaLight::PDF(Result &result)
{
	return object->PDF(result);
}

bool AreaLight::InShadow(Ray &ray, Result &result)
{
	float t = (samplePoint - ray.GetOrigin())
				.Dot(ray.GetDirection());

	return result.scene->ShadowHit(ray, t);
}
