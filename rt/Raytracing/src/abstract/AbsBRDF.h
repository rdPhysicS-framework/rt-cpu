#ifndef	 __ABS_BRDF_H__
#define	 __ABS_BRDF_H__

#include "..\interface\BRDF.h"

class Sampler;

class AbsBRDF : public BRDF
{
protected:
	Sampler *sampler;

public:
	AbsBRDF(Sampler *sampler = nullptr);
	AbsBRDF(const AbsBRDF &other);

	void SetSampler(Sampler *_sampler, const float exp = 1);
	Sampler *GetSampler() const;

	virtual AbsBRDF *Clone() = 0;
	virtual RT::Vec3f F(const Result &result, 
						RT::Vec3f &wi,
						RT::Vec3f &wo) const = 0;
	virtual RT::Vec3f SampleF(Result &result,
							  RT::Vec3f &wi,
							  RT::Vec3f &wo,
							  float &pdf) const = 0;
	virtual RT::Vec3f RHO(const Result &result, 
						  const RT::Vec3f &wo) const = 0;
};
#endif //__ABS_BRDF_H__