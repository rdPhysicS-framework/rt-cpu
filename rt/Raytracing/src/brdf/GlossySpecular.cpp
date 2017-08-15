#include "GlossySpecular.h"
#include "..\primitivas\Result.h"
#include "..\Util\Util.h"
#include "..\abstract\Sampler.h"


GlossySpecular::GlossySpecular(RT::Vec3f &color,
							   float ks, 
							   float exp, 
							   Sampler *sampler) :
	AbsBRDF(sampler),
	color(color),
	ks(ks),
	exp(exp)
{
	SetSampler(sampler, exp);
}

GlossySpecular::GlossySpecular(const GlossySpecular &other) :
	AbsBRDF(other),
	color(other.color),
	ks(other.ks),
	exp(other.exp)
{
}

AbsBRDF *GlossySpecular::Clone()
{
	return new GlossySpecular(*this);
}

RT::Vec3f GlossySpecular::F(const Result &result, 
						    RT::Vec3f &wi, 
						    RT::Vec3f &wo) const
{
	RT::Vec3f L;
	//float nDotWi = result.normal.Dot(wi);

	RT::Vec3f r = RT::vc3::Reflect(wi, result.normal);//((wi*-1) + 2.0f * result.normal * nDotWi);
	float rDotWo = r.Dot(wo);

	if (rDotWo > 0.0f)
		L = color * (ks * pow(rDotWo, exp));

	return L;
}

RT::Vec3f GlossySpecular::SampleF(Result &result, RT::Vec3f &wi, RT::Vec3f &wo, float &pdf) const
{
	RT::Vec3f r = RT::vc3::Reflect(wo, result.normal);//wo + 2.0f * result.normal * nDotWo;

	RT::Vec3f w = r;
	RT::Vec3f u = RT::vc3::Cross(RT::Vec3f(0.00424, 1, 0.00764), w);
	u.Normalize();
	RT::Vec3f v = RT::vc3::Cross(u, w);

	RT::Vec3f sp = sampler->SampleHemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;

	if (result.normal.Dot(wi) < 0.0f)
	{
		wi = -sp.x * u - sp.y * v + sp.z * w;
	}

	float phongLobe = pow(r.Dot(wi), exp);
	pdf = phongLobe * (result.normal.Dot(wi));

	return (color * (ks * phongLobe));
}

RT::Vec3f GlossySpecular::RHO(const Result &result, const RT::Vec3f & wo) const
{
	return BLACK;
}

RT::Vec3f GlossySpecular::ConvertUVW(const Result &result, 
									 const RT::Vec3f & v1) const
{
	float nDotWo = result.normal.Dot(v1);
	RT::Vec3f r = (v1*-1) + 2.0f * result.normal * nDotWo;

	RT::Vec3f w = r;
	RT::Vec3f u = RT::vc3::Cross(RT::Vec3f(0.00424f, 1.0f, 0.00764f), w).Normalize();
	RT::Vec3f v = RT::vc3::Cross(u, w);

	RT::Vec3f sp = sampler->SampleHemisphere();

	return (sp.x * u + sp.y * v + sp.z * w);
}
