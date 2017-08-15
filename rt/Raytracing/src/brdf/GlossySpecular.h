#ifndef	 __GLOSSY_SPECULAR_H__
#define	 __GLOSSY_SPECULAR_H__

#include "..\abstract\AbsBRDF.h"

class GlossySpecular : public AbsBRDF
{
private:
	float ks;
	RT::Vec3f color;
	float exp;

	RT::Vec3f ConvertUVW(const Result &result,
						 const RT::Vec3f &v1) const;
public:
	GlossySpecular(RT::Vec3f &color = RT::Vec3f(), 
				   float ks = 0.0f, 
				   float exp = 1.0f,
				   Sampler *sampler = nullptr);
	GlossySpecular(const GlossySpecular &other);

	inline void SetKs(const float ks)
	{
		this->ks = ks;
	}

	inline void SetExp(const float exp)
	{
		this->exp = exp;
		SetSampler(sampler, exp);
	}

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

#endif //__GLOSSY_SPECULAR_H__