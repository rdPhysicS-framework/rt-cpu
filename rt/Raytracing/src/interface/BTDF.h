#ifndef	 __BTDF_H__
#define	 __BTDF_H__

#include <RTmath.h>

class Result;

class BTDF
{
public:
	virtual ~BTDF(){}
	virtual BTDF *Clone() = 0;
	virtual RT::Vec3f F(Result &result, RT::Vec3f &wt, RT::Vec3f &wo) const = 0;
	virtual RT::Vec3f SampleF(Result &result, RT::Vec3f &wt, RT::Vec3f &wo) const = 0;
	virtual bool Tir(Result &result) const = 0;
	virtual RT::Vec3f RHO(const Result &result,
						  const RT::Vec3f &wo) const = 0;
};

#endif //__BTDF_H__