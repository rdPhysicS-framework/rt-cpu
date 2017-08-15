#ifndef	 __LIGHT_H__
#define	 __LIGHT_H__

#include <RTmath.h>

class Result;
class Ray;

class Light
{
public:
	virtual ~Light() {}
	virtual RT::Vec3f GetDirection(Result &result) = 0;
	virtual RT::Vec3f L(Result &result) = 0;
	virtual float G(Result &result) = 0;
	virtual float PDF(Result &result) = 0;
	virtual bool InShadow(Ray &ray, Result &result) = 0;
};

#endif //__LIGHT_H__
