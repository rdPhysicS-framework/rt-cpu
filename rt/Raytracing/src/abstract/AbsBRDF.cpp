#include "AbsBRDF.h"
#include "..\abstract\Sampler.h"

AbsBRDF::AbsBRDF(Sampler *sampler) :
		 sampler(sampler)
{}

AbsBRDF::AbsBRDF(const AbsBRDF &other) :
		 sampler( (other.sampler) ? 
				   other.sampler
					    ->Clone() : 
				   nullptr)
{
	if(sampler)
		sampler->MapSamplesToHemisphere(1);
}

void AbsBRDF::SetSampler(Sampler *_sampler, const float exp)
{
	sampler = _sampler;
	if (sampler)
		sampler->MapSamplesToHemisphere(exp);
}

Sampler *AbsBRDF::GetSampler() const
{
	return sampler;
}
