#ifndef	 __BRDF_H__
#define	 __BRDF_H__

#include <RTmath.h>

class Result;

class BRDF 
{
public:
	virtual ~BRDF() {}
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

#endif //__BRDF_H__