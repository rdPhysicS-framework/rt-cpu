#include "Lambertian.h"
#include "..\Util\Util.h"
#include "..\abstract\Sampler.h"
#include "..\primitivas\Result.h"

Lambertian::Lambertian(RT::Vec3f color,
					   float kd,
					   Sampler *sampler) :
	AbsBRDF(sampler), 
	kd(kd), 
	color(color)
{}

Lambertian::Lambertian(const Lambertian &other) :
	AbsBRDF(other),
	kd(other.kd),
	color(other.color)
{}

AbsBRDF *Lambertian::Clone()
{
	return new Lambertian(*this);
}

RT::Vec3f Lambertian::F(const Result &result,
					    RT::Vec3f & wi, 
						RT::Vec3f &wo) const
{
	return (color * (kd * INVPI));
}

RT::Vec3f Lambertian::SampleF(Result &result,
							  RT::Vec3f &wi,
							  RT::Vec3f &wo, 
							  float &pdf) const
{
	wi = ConvertUVW(result, wi);
	pdf = result.normal.Dot(wi * INVPI);
	return (color * (kd * INVPI));
}

RT::Vec3f Lambertian::RHO(const Result &result, 
						  const RT::Vec3f &wo) const
{
	return (color * kd);
}

RT::Vec3f Lambertian::ConvertUVW(const Result &result,
							     const RT::Vec3f &wi) const
{
	RT::Vec3f w = result.normal;
	RT::Vec3f v = RT::vc3::Cross(RT::Vec3f(0.0034f, 1.0f, 0.0071f), w).Normalize();
	RT::Vec3f u = RT::vc3::Cross(v, w);

	RT::Vec3f sp = sampler->SampleHemisphere();
	
	return (sp.x * u + sp.y * v + sp.z * w).Normalize();
}
