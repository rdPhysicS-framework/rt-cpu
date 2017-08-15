#include "PerfectTransmitter.h"
#include "..\raytracer\Ray.h"
#include "..\primitivas\Result.h"
#include "..\Util\Util.h"

PerfectTransmitter::PerfectTransmitter(RT::Vec3f &color, 
									   float kt,
									   float ior) :
	color(color),
	kt(kt),
	ior(ior)
{}

PerfectTransmitter::PerfectTransmitter(const PerfectTransmitter &other) :
	color(other.color),
	kt(other.kt),
	ior(other.ior)
{}

BTDF *PerfectTransmitter::Clone()
{
	return new PerfectTransmitter(*this);
}

RT::Vec3f PerfectTransmitter::SampleF(Result &result, RT::Vec3f &wt, RT::Vec3f &wo) const
{
	RT::Vec3f n = result.normal;
	float cosThetai = n.Dot(wo*-1);
	float eta = ior;

	if (cosThetai < 0.0)
	{
		cosThetai = -cosThetai;
		n *= -1;
		eta = 1.0f / eta;
	}

	float temp = 1.0 - (1.0 - cosThetai * cosThetai) / (eta * eta);
	float cosTheta2 = sqrt(temp);
	//wt =  wo / eta - (cosTheta2 - cosThetai / eta) * n;
	wt = RT::vc3::Refract(wo, n, eta);
	return (kt / (eta * eta) * WHITE / fabs(result.normal.Dot(wt)));
}

bool PerfectTransmitter::Tir(Result &result) const
{
	RT::Vec3f wo = result.ray->GetDirection();
	float cosThetai = result.normal.Dot(wo);
	float eta = ior;

	if (ior < 0.0f)
		eta = 1.0f / eta;

	return (1.0 - (1.0 - cosThetai * cosThetai) / (eta * eta) < 0.0);
}
