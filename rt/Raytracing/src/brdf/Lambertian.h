#ifndef	 __LABERTIAN_H__
#define	 __LABERTIAN_H__

#include "..\abstract\AbsBRDF.h"

class Lambertian : public AbsBRDF
{
private:
	float kd;
	RT::Vec3f color;

	RT::Vec3f ConvertUVW(const Result &result,
					     const RT::Vec3f &wi) const;
public:
	Lambertian(RT::Vec3f color = RT::Vec3f(), 
			   float kd = 0.0f, 
			   Sampler *sampler = nullptr);
	Lambertian(const Lambertian &other);

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

#endif //__LABERTIAN_H__