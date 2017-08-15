#ifndef	 __PERFECT_SPECULAR_H__
#define	 __PERFECT_SPECULAR_H__

#include "..\abstract\AbsBRDF.h"

class PerfectSpecular : public AbsBRDF
{
private:
	float kr;
	RT::Vec3f color;

	RT::Vec3f ConvertUVW(const Result &result,
						 const RT::Vec3f &v1) const;
public:
	PerfectSpecular(RT::Vec3f &color = RT::Vec3f(),
			   float ks = 0.0f,
			   Sampler *sampler = nullptr);
	PerfectSpecular(const PerfectSpecular &other);

	inline float GetKr() const { return kr; }

	virtual AbsBRDF *Clone();
	virtual RT::Vec3f F(const Result &result,
						RT::Vec3f &wi,
						RT::Vec3f &wo) const;
	virtual RT::Vec3f SampleF(Result &result,
							  RT::Vec3f &wi,
							  RT::Vec3f &wo,
							  float &pdf) const;
	virtual RT::Vec3f RHO(const Result &result,
						  const RT::Vec3f &wo) const;
};

#endif //__PERFECT_SPECULAR_H__