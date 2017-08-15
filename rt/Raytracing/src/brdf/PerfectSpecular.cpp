#include "PerfectSpecular.h"
#include "..\primitivas\Result.h"
#include "..\Util\Util.h"

PerfectSpecular::PerfectSpecular(RT::Vec3f &color, 
					   float kr, 
					   Sampler *sampler) :
	AbsBRDF(sampler),
	color(color),
	kr(kr)
{}

PerfectSpecular::PerfectSpecular(const PerfectSpecular &other) :
	AbsBRDF(other),
	color(other.color),
	kr(other.kr)
{}

AbsBRDF *PerfectSpecular::Clone()
{
	return new PerfectSpecular(*this);
}

RT::Vec3f PerfectSpecular::F(const Result &result, 
						RT::Vec3f &wi, 
						RT::Vec3f &wo) const
{
	//float ndotwo = result.normal.Dot(wo);
	//wi = wo * -1 + 2.0f * result.normal * ndotwo;
	wi = RT::vc3::Reflect(wo, result.normal);

	return (color * kr / fabs(result.normal.Dot(wi)));
}

RT::Vec3f PerfectSpecular::SampleF(Result & result, RT::Vec3f & wi, RT::Vec3f & wo, float & pdf) const
{
	wi = RT::vc3::Reflect(wo, result.normal);
	pdf = fabs(result.normal.Dot(wi));
	return (color * kr);
}

RT::Vec3f PerfectSpecular::RHO(const Result &result, const RT::Vec3f & wo) const
{
	return BLACK;
}
